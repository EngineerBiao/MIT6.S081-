// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

/* 引用计数块 */
typedef struct
{
  struct spinlock lock;
  int count;
} memref;
/* 每个内存页都需要计数 */
memref memrefs[PHYSTOP / PGSIZE];

void
kinit()
{
  initlock(&kmem.lock, "kmem");
  // 为每个内存页初始化自旋锁
  for (int i = 0; i < PHYSTOP / PGSIZE; i++)
    initlock(&(memrefs[i].lock), "memref");
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // 减少内存块的引用
  uint64 i = (uint64)pa / PGSIZE;
  acquire(&(memrefs[i].lock));
  memrefs[i].count--;
  if (memrefs[i].count > 0) // 如果还有引用，就不删除内存
  {
    release(&(memrefs[i].lock));
    return;
  }
  
  release(&(memrefs[i].lock));
  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;
  
  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
  {
    kmem.freelist = r->next;
    // 设置引用次数
    uint64 i = (uint64)r / PGSIZE;
    acquire(&(memrefs[i].lock));
    memrefs[i].count = 1;
    release(&(memrefs[i].lock));
  }
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
// 增加内存页pa的引用计数
void ref_incre(uint64 pa)
{
  uint64 i = pa / PGSIZE;
  acquire(&(memrefs[i].lock));
  memrefs[i].count++;
  release(&(memrefs[i].lock));
}

int iscow(pagetable_t pagetable, uint64 va)
{
  if (va > MAXVA)
    return 0;

  pte_t *pte = walk(pagetable, va, 0);
  if (pte == 0 || (*pte & PTE_V) == 0)
    return 0;

  return (*pte & PTE_F);
}

// 将给定的虚拟内存页进行拷贝，映射到新的物理页并返回
uint64 cowcopy(pagetable_t pagetable, uint64 va)
{
  // 使用walk函数找到对应的物理地址
  va = PGROUNDDOWN(va);
  pte_t *pte = walk(pagetable, va, 0); 
  uint64 pa = PTE2PA(*pte); 
  uint32 i = pa / PGSIZE;
  
  // 判断引用计数是否为1，如果为1就直接加上写权限即可
  acquire(&(memrefs[i].lock));
  if (memrefs[i].count == 1)
  {
    *pte |= PTE_W;
    *pte &= (~PTE_F);
    release(&(memrefs[i].lock));
    return pa;
  }
  release(&(memrefs[i].lock));
  
  // 分配内存并进行拷贝
  void *mem = kalloc();
  if (mem == 0)
    return 0;
  memmove(mem, (void *)pa, PGSIZE);
  // 给新的pte设置写权限，去掉COW标记
  uint64 flag = PTE_FLAGS(*pte);
  flag |= PTE_W;
  flag &= (~PTE_F);
  *pte &= ~PTE_V; // 要清除PTE_V，否则在mappagges中会判定为remap
  if (mappages(pagetable, va, PGSIZE, (uint64)mem, flag) != 0)
  {
    kfree(mem);
    return 0;
  }
  kfree((void *)PGROUNDDOWN(pa)); // 将原来的物理内存引用计数减1
  return (uint64)mem;
}
