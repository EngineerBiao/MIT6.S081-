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

// 在每个空闲页的内存开头处存放run，那么run的值就是该页内存的地址。
// 而run存储着下一张空闲内存页的地址
struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist; // 分配器的数据结构是一个空闲链表
} kmem;

// 初始化空闲链表（把内核结束到PHYSTOP之间的每一页都初始化到链表中，供分配器的使用）
void kinit() 
{
  initlock(&kmem.lock, "kmem");
  freerange(end, (void*)PHYSTOP);
}
void freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p); // 对每一页都释放内存来将内存添加到空闲链表
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
// 释放内存（给页面填充垃圾值然后插入空闲链表）
void kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);
  
  // 把虚拟地址赋值给run结构体，然后使用头插法把run插到空闲链表中
  r = (struct run *)pa; 
  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
// 分配内存（删除并返回空闲内存链表中的第一块内存地址）
void * kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next; // 将空闲页的run从空闲链表中删除
  release(&kmem.lock);

  // 对分配的内存填充垃圾值然后返回
  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
