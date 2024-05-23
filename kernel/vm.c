#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "elf.h"
#include "riscv.h"
#include "defs.h"
#include "fs.h"
// 更改了kvmpa，需要用上进程内容（下面两个头文件的包含顺序不能改）
#include "spinlock.h" 
#include "proc.h" 

/*
 * the kernel's page table.
 */
pagetable_t kernel_pagetable;

extern char etext[];  // kernel.ld sets this to end of kernel code.

extern char trampoline[]; // trampoline.S

/*
 * create a direct-map page table for the kernel.
 * 创建全局的内核页表：设置内核的映射（直接映射）
 */
void kvminit()
{
  kernel_pagetable = (pagetable_t) kalloc(); // 给内核的最高级页表目录分配物理页
  memset(kernel_pagetable, 0, PGSIZE);

  // uart registers
  // 采用直接映射，所以虚拟内存和物理内存地址都是UART0，然后后两个参数分别是页大小和标志位
  kvmmap(UART0, UART0, PGSIZE, PTE_R | PTE_W);

  // virtio mmio disk interface
  kvmmap(VIRTIO0, VIRTIO0, PGSIZE, PTE_R | PTE_W);

  // CLINT
  kvmmap(CLINT, CLINT, 0x10000, PTE_R | PTE_W);

  // PLIC
  kvmmap(PLIC, PLIC, 0x400000, PTE_R | PTE_W);

  // map kernel text executable and read-only.
  kvmmap(KERNBASE, KERNBASE, (uint64)etext-KERNBASE, PTE_R | PTE_X);

  // map kernel data and the physical RAM we'll make use of.
  kvmmap((uint64)etext, (uint64)etext, PHYSTOP-(uint64)etext, PTE_R | PTE_W);

  // map the trampoline for trap entry/exit to
  // the highest virtual address in the kernel.
  kvmmap(TRAMPOLINE, (uint64)trampoline, PGSIZE, PTE_R | PTE_X);
}

// 封装uvmmap来为用户内核页表的条目添加映射关系
void uvmmap(pagetable_t pagetable, uint64 va, uint64 pa, uint64 sz, int perm)
{
  if (mappages(pagetable, va, sz, pa, perm) != 0)
    panic("uvmmap");
}
// 为每个进程创建内核页表，和kvminit差不多
pagetable_t pkvminit()
{
  pagetable_t pagetable = uvmcreate();
  memset(pagetable, 0, PGSIZE);
  uvmmap(pagetable, UART0, UART0, PGSIZE, PTE_R | PTE_W);
  uvmmap(pagetable, VIRTIO0, VIRTIO0, PGSIZE, PTE_R | PTE_W);
  uvmmap(pagetable, CLINT, CLINT, 0x10000, PTE_R | PTE_W);
  uvmmap(pagetable, PLIC, PLIC, 0x400000, PTE_R | PTE_W);
  uvmmap(pagetable, KERNBASE, KERNBASE, (uint64)etext - KERNBASE, PTE_R | PTE_X);
  uvmmap(pagetable, (uint64)etext, (uint64)etext, PHYSTOP - (uint64)etext, PTE_R | PTE_W);
  uvmmap(pagetable, TRAMPOLINE, (uint64)trampoline, PGSIZE, PTE_R | PTE_X);
  return pagetable;
}

// Switch h/w page table register to the kernel's page table,
// and enable paging.
// 设置SATP寄存器，告诉MMU内核最高级页表的地址
void
kvminithart()
{
  w_satp(MAKE_SATP(kernel_pagetable)); 
  // 从上面指令开始，之后的所有代码访问的地址都是虚拟地址，会被MMU转换成物理地址
  // 尽管之后的地址都是虚拟地址，但内核访问的虚拟地址与物理地址的值是相等的，所以依然能操作物理地址
  sfence_vma();
}

// 设置SATP寄存器，设置为进程的内核页表
void ukvminithart(pagetable_t pagetable)
{
  w_satp(MAKE_SATP(pagetable));
  sfence_vma();
}

// Return the address of the PTE in page table pagetable
// that corresponds to virtual address va.  If alloc!=0,
// create any required page-table pages.
//
// The risc-v Sv39 scheme has three levels of page-table
// pages. A page-table page contains 512 64-bit PTEs.
// A 64-bit virtual address is split into five fields:
//   39..63 -- must be zero.
//   30..38 -- 9 bits of level-2 index.
//   21..29 -- 9 bits of level-1 index.
//   12..20 -- 9 bits of level-0 index.
//    0..11 -- 12 bits of byte offset within the page.

// 1、当alloc为0，walk函数根据va地址来查找其对应的最低级页表项，找到后会返回该PTE指针，否则返回0。
// 2、当alloc为1，函数会为该虚拟地址创建前两级的页表，并返回最低级页表中该地址的的页表项指针但不添加
//    映射。而是调用该walk()的函数会在调用walk之后自己为该PTE填充映射关系。

/* alloc为1时的全流程：第一次for循环level为2，在二级页表获取对应的页表项。判断这个页表项是否有效，
  如果无效就为该页表分配内存页，然后把该页的物理地址添加到pte中。经过第一次循环，此时这个pagetable就是
  被创建的一级页表。然后同样对一级页表重复上面的操作，退出for循环后，此时pagetable就是0级页表，返回对应的pte
 */
pte_t * walk(pagetable_t pagetable, uint64 va, int alloc)
{
  if(va >= MAXVA)
    panic("walk");
  for(int level = 2; level > 0; level--)
  {
    // PX(level, va)：从虚拟地址中获取该级页表对应的页表项索引（0~255）
    pte_t *pte = &pagetable[PX(level, va)]; 
    if(*pte & PTE_V) // 判断页表项是否有映射信息
      pagetable = (pagetable_t)PTE2PA(*pte); // 根据得到的pte将pagetable更新为下一级的页表
    else // 如果该级页表的页表项为空，说明虚拟地址没有被映射，根据alloc来决定是否进行映射
    {  // 如果不允许分配就返回0，表示没有找到映射关系。页表项分配失败也返回0表示错误
      if(!alloc || (pagetable = (pde_t*)kalloc()) == 0)
        return 0; // 使用kalloc创建了新页表后，此时pagetable就是下一级页表了（即更新为下级页表）
      memset(pagetable, 0, PGSIZE);
      *pte = PA2PTE(pagetable) | PTE_V; // 填写页表项pte
    }
  }
  // for循环结束，到了最低级页表，返回该虚拟地址对应的pte指针（如果alloc为1，由调用者自己填写PTE内容）
  return &pagetable[PX(0, va)];
}

// Look up a virtual address, return the physical address,
// or 0 if not mapped.
// Can only be used to look up user pages.
uint64
walkaddr(pagetable_t pagetable, uint64 va)
{
  pte_t *pte;
  uint64 pa;

  if(va >= MAXVA)
    return 0;

  pte = walk(pagetable, va, 0);
  if(pte == 0)
    return 0;
  if((*pte & PTE_V) == 0)
    return 0;
  if((*pte & PTE_U) == 0)
    return 0;
  pa = PTE2PA(*pte);
  return pa;
}

// add a mapping to the kernel page table.
// only used when booting.
// does not flush TLB or enable paging.
// 为内核页表的条目添加映射关系
void 
kvmmap(uint64 va, uint64 pa, uint64 sz, int perm)
{
  if(mappages(kernel_pagetable, va, sz, pa, perm) != 0)
    panic("kvmmap");
}

// translate a kernel virtual address to a physical address.
// only needed for addresses on the stack.
// assumes va is page aligned.
uint64 
kvmpa(uint64 va)
{
  uint64 off = va % PGSIZE;
  pte_t *pte;
  uint64 pa;

  pte = walk(myproc()->kpagetable, va, 0);
  if(pte == 0)
    panic("kvmpa");
  if((*pte & PTE_V) == 0)
    panic("kvmpa");
  pa = PTE2PA(*pte);
  return pa+off;
}

// Create PTEs for virtual addresses starting at va that refer to
// physical addresses starting at pa. va and size might not
// be page-aligned. Returns 0 on success, -1 if walk() couldn't
// allocate a needed page-table page.
// 使用walk函数创建前两级页表和映射关系，然后填写最低级页表的页表项
int mappages(pagetable_t pagetable, uint64 va, uint64 size, uint64 pa, int perm)
{
  uint64 a, last;
  pte_t *pte;

  a = PGROUNDDOWN(va);
  last = PGROUNDDOWN(va + size - 1);
  for(;;){
    if((pte = walk(pagetable, a, 1)) == 0) // 创建前两级页表，返回最低级页表的页表项
      return -1;
    if(*pte & PTE_V) // 检查页表项是否已被设置
      panic("remap");
    *pte = PA2PTE(pa) | perm | PTE_V; // 填写页表项（添加映射关系）
    if(a == last)
      break;
    a += PGSIZE;
    pa += PGSIZE;
  }
  return 0;
}

// Remove npages of mappings starting from va. va must be
// page-aligned. The mappings must exist.
// Optionally free the physical memory.
// 从va开始释放n页的内存，并且可以选择是否释放物理内存页
void 
uvmunmap(pagetable_t pagetable, uint64 va, uint64 npages, int do_free)
{
  uint64 a;
  pte_t *pte;

  if((va % PGSIZE) != 0)
    panic("uvmunmap: not aligned");

  for(a = va; a < va + npages*PGSIZE; a += PGSIZE){
    if((pte = walk(pagetable, a, 0)) == 0)
      panic("uvmunmap: walk");
    if((*pte & PTE_V) == 0)
      panic("uvmunmap: not mapped");
    if(PTE_FLAGS(*pte) == PTE_V)
      panic("uvmunmap: not a leaf");
    if(do_free){
      uint64 pa = PTE2PA(*pte);
      kfree((void*)pa);
    }
    *pte = 0;
  }
}

// create an empty user page table.
// returns 0 if out of memory.
// 为用户态创建页表，主要就是给页表分配一块内存
pagetable_t 
uvmcreate()
{
  pagetable_t pagetable;
  pagetable = (pagetable_t) kalloc();
  if(pagetable == 0)
    return 0;
  memset(pagetable, 0, PGSIZE);
  return pagetable;
}

// Load the user initcode into address 0 of pagetable,
// for the very first process.
// sz must be less than a page.
void uvminit(pagetable_t pagetable, uchar *src, uint sz)
{
  char *mem;

  if(sz >= PGSIZE)
    panic("inituvm: more than a page");
  mem = kalloc();
  memset(mem, 0, PGSIZE);
  mappages(pagetable, 0, PGSIZE, (uint64)mem, PTE_W|PTE_R|PTE_X|PTE_U);
  memmove(mem, src, sz);
}

// Allocate PTEs and physical memory to grow process from oldsz to
// newsz, which need not be page aligned.  Returns new size or 0 on error.
uint64
uvmalloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz)
{
  char *mem;
  uint64 a;

  if(newsz < oldsz)
    return oldsz;

  oldsz = PGROUNDUP(oldsz);
  for(a = oldsz; a < newsz; a += PGSIZE){
    mem = kalloc();
    if(mem == 0){
      uvmdealloc(pagetable, a, oldsz);
      return 0;
    }
    memset(mem, 0, PGSIZE);
    if(mappages(pagetable, a, PGSIZE, (uint64)mem, PTE_W|PTE_X|PTE_R|PTE_U) != 0){
      kfree(mem);
      uvmdealloc(pagetable, a, oldsz);
      return 0;
    }
  }
  return newsz;
}

// Deallocate user pages to bring the process size from oldsz to
// newsz.  oldsz and newsz need not be page-aligned, nor does newsz
// need to be less than oldsz.  oldsz can be larger than the actual
// process size.  Returns the new process size.
uint64
uvmdealloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz)
{
  if(newsz >= oldsz)
    return oldsz;

  if(PGROUNDUP(newsz) < PGROUNDUP(oldsz)){
    int npages = (PGROUNDUP(oldsz) - PGROUNDUP(newsz)) / PGSIZE;
    uvmunmap(pagetable, PGROUNDUP(newsz), npages, 1);
  }

  return newsz;
}

// Recursively free page-table pages.
// All leaf mappings must already have been removed.
// 递归地释放页表及其子页表的页面内存（要保证子页表的映射关系都被移除，即RWX都为0）
void freewalk(pagetable_t pagetable)
{
  // there are 2^9 = 512 PTEs in a page table.
  for(int i = 0; i < 512; i++)
  {
    pte_t pte = pagetable[i]; // 获取页表目录项
    // pte & PTE_V用于判断PTE_V是否有效，如果无效就不用做处理。
    // 如果RWX标志位都为0，说明这是第一或第二级页表，可以递归地调用freewalk来释放页表
    if((pte & PTE_V) && (pte & (PTE_R|PTE_W|PTE_X)) == 0)
    { 
      // this PTE points to a lower-level page table.
      uint64 child = PTE2PA(pte); // 获取PTE中的PPN地址
      freewalk((pagetable_t)child); // 将64位整数地址转换成指针，调用函数来释放
      pagetable[i] = 0; // 将条目置0
    } 
    else if(pte & PTE_V) // 走到这里说明PTE有效且RWX其中一个被设置了，说明遇到了叶子映射，即第三级页表的映射没被移除
      panic("freewalk: leaf"); // 遇到叶子映射是错的
    // 如果PTE_V为0，则不用处理
  }
  kfree((void*)pagetable); // 释放页表页内存，把内存页加入空闲链表
}

// 移除进程内核页表的映射关系并释放页表，和freewalk差不多，但不需要保证子页表的映射关系被移除
void freeukp(pagetable_t pagetable)
{
  for (int i = 0; i < 512; i++)
  {
    pte_t pte = pagetable[i]; // 获取页表目录项
    if (pte & PTE_V)
    {
      pagetable[i] = 0; // 将条目置0
      if ((pte & (PTE_R | PTE_W | PTE_X)) == 0)
      {
        uint64 child = PTE2PA(pte);  // 获取PTE中的PPN地址
        freeukp((pagetable_t)child); // 将64位整数地址转换成指针，调用函数来释放
      }
    }
  }
  kfree((void *)pagetable); // 释放页表页内存，把内存页加入空闲链表
}

// Free user memory pages,
// then free page-table pages.
void
uvmfree(pagetable_t pagetable, uint64 sz)
{
  if(sz > 0)
    uvmunmap(pagetable, 0, PGROUNDUP(sz)/PGSIZE, 1);
  freewalk(pagetable);
}

// Given a parent process's page table, copy
// its memory into a child's page table.
// Copies both the page table and the physical memory.
// returns 0 on success, -1 on failure.
// frees any allocated pages on failure.
// 将父进程的页表拷贝给子进程的页表，并且还会拷贝一份内存给子进程
int
uvmcopy(pagetable_t old, pagetable_t new, uint64 sz) // sz是父进程的整个进程空间大小，即要映射的地址大小
{
  pte_t *pte;
  uint64 pa, i;
  uint flags;
  char *mem;
  
  /* 过程说明
  进程的地址空间从0开始，以页为大小的首地址会映射到页表中。所以这里是从0开始以页的大小遍历地址。
  对于每次循环的地址，使用walk函数找到该地址对应的最低级pte。然后就可以得到父进程的页表内容了，
  然后给子进程分配内存，并为子进程的页表添加映射关系  */
  for(i = 0; i < sz; i += PGSIZE){
    if((pte = walk(old, i, 0)) == 0) // 检查pte是否存在
      panic("uvmcopy: pte should exist");
    if((*pte & PTE_V) == 0) // 
      panic("uvmcopy: page not present");
    pa = PTE2PA(*pte);
    flags = PTE_FLAGS(*pte);
    // 给子进程分配内存，然后给子进程的页表添加映射关系
    if((mem = kalloc()) == 0)
      goto err;
    memmove(mem, (char*)pa, PGSIZE); // 拷贝内存给子进程
    if(mappages(new, i, PGSIZE, (uint64)mem, flags) != 0){ // 添加映射关系
      kfree(mem);
      goto err;
    }
  }
  return 0;

 err:
  uvmunmap(new, 0, i / PGSIZE, 1);
  return -1;
}

// mark a PTE invalid for user access.
// used by exec for the user stack guard page.
void
uvmclear(pagetable_t pagetable, uint64 va)
{
  pte_t *pte;
  
  pte = walk(pagetable, va, 0);
  if(pte == 0)
    panic("uvmclear");
  *pte &= ~PTE_U;
}

// Copy from kernel to user.
// Copy len bytes from src to virtual address dstva in a given page table.
// Return 0 on success, -1 on error.
int
copyout(pagetable_t pagetable, uint64 dstva, char *src, uint64 len)
{
  uint64 n, va0, pa0;

  while(len > 0){
    va0 = PGROUNDDOWN(dstva);
    pa0 = walkaddr(pagetable, va0);
    if(pa0 == 0)
      return -1;
    n = PGSIZE - (dstva - va0);
    if(n > len)
      n = len;
    memmove((void *)(pa0 + (dstva - va0)), src, n);

    len -= n;
    src += n;
    dstva = va0 + PGSIZE;
  }
  return 0;
}

// 将进程页表拷贝到进程的内核页表中，参考uvmcopy函数。这里接收两个页表，以及要拷贝(映射)的起始地址和终止地址
int copypg(pagetable_t pagetable, pagetable_t kpagetable, uint64 start, uint64 end)
{
  pte_t *pte, *kpte;
  uint64 i;
  start = PGROUNDUP(start); // 向上取页的整数倍（不能向下，因为会导致内容被覆盖）
  for (i = start; i < end; i += PGSIZE)
  {
    if ((pte = walk(pagetable, i, 0)) == 0) // 获取进程页表pte
      panic("copypg: src pte does not exist");
    uint64 pa = PTE2PA(*pte); // 获取物理地址
    uint flags = (PTE_FLAGS(*pte)) & (~PTE_U); // 获取标志位（要将PTE_U置0）
    
    if ((kpte = walk(kpagetable, i, 1)) == 0) // 创建进程内核页表的PTE
      panic("copypg: pte walk failed");
    
    // 添加映射关系
    *kpte = PA2PTE(pa) | flags;
  }
  return 0;
}

// Copy from user to kernel.
// Copy len bytes to dst from virtual address srcva in a given page table.
// Return 0 on success, -1 on error.
// 把用户空间的数据复制到内核
int
copyin(pagetable_t pagetable, char *dst, uint64 srcva, uint64 len)
{
  return copyin_new(pagetable, dst, srcva, len);

  /*       原代码     */
  // uint64 n, va0, pa0;
  // while(len > 0){
  //   va0 = PGROUNDDOWN(srcva);
  //   pa0 = walkaddr(pagetable, va0);
  //   if(pa0 == 0)
  //     return -1;
  //   n = PGSIZE - (srcva - va0);
  //   if(n > len)
  //     n = len;
  //   memmove(dst, (void *)(pa0 + (srcva - va0)), n);

  //   len -= n;
  //   dst += n;
  //   srcva = va0 + PGSIZE;
  // }
  // return 0;
}

// Copy a null-terminated string from user to kernel.
// Copy bytes to dst from virtual address srcva in a given page table,
// until a '\0', or max.
// Return 0 on success, -1 on error.
int
copyinstr(pagetable_t pagetable, char *dst, uint64 srcva, uint64 max)
{
  return copyinstr_new(pagetable, dst, srcva, max);

  /*       原代码     */
  // uint64 n, va0, pa0;
  // int got_null = 0;

  // while(got_null == 0 && max > 0){
  //   va0 = PGROUNDDOWN(srcva);
  //   pa0 = walkaddr(pagetable, va0);
  //   if(pa0 == 0)
  //     return -1;
  //   n = PGSIZE - (srcva - va0);
  //   if(n > max)
  //     n = max;

  //   char *p = (char *) (pa0 + (srcva - va0));
  //   while(n > 0){
  //     if(*p == '\0'){
  //       *dst = '\0';
  //       got_null = 1;
  //       break;
  //     } else {
  //       *dst = *p;
  //     }
  //     --n;
  //     --max;
  //     p++;
  //     dst++;
  //   }

  //   srcva = va0 + PGSIZE;
  // }
  // if(got_null){
  //   return 0;
  // } else {
  //   return -1;
  // }
}

// Lab3的任务1，递归打印页表的pte
void _vmprint(pagetable_t pagetable, int level) // level用于判断当前的页表等级
{
  for (int i = 0; i < 512; i++)
  {
    pte_t pte = pagetable[i]; // 获取pte
    if ((pte & PTE_V) == 0) // 如果pte或PTE_V为0就不用递归调用，直接遍历下一个pte
      continue;
    
    // 打印pte条目，然后对条目中的页表地址递归调用
    if (level == 1)
      printf("..");
    else if (level == 2)
      printf(".. ..");
    else
      printf(".. .. ..");
    printf("%d: pte %p pa %p\n", i, pte, PTE2PA(pte)); // %p是按照16进制来打印内容，所以可用来打印pte比特位
    
    // 如果不是最低级目录就递归调用打印函数
    if ((pte & (PTE_R | PTE_W | PTE_X)) == 0)
    {
      uint64 child = PTE2PA(pte); // 获取PTE中的物理页表地址
      _vmprint((pagetable_t)child, level + 1);
    }
  }
}
void vmprint(pagetable_t pagetable)
{
  printf("page table %p\n", pagetable); // 打印参数
  _vmprint(pagetable, 1);
}
