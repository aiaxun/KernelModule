/*************************************************************************
	> File Name: slide.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月16日 星期六 11时06分26秒
 ************************************************************************/
#include "slide.h"

#include <linux/mm.h>
#include <linux/mman.h>
int modify_vma_prot(unsigned long addr, unsigned long prot,struct task_struct *task)
{
    //unsigned long start,end;
    unsigned long newflags;
    struct vm_area_struct *vma;
    struct vm_area_struct *pprev;
    int error = -EINVAL;
    down_write(&task->mm->mmap_sem);
    vma = find_vma(task->mm,addr);
    if (!vma) {
        printk("DO NOT FIND VMA");
        error = -EINVAL;
        goto out;
    }
    pprev = vma->vm_prev;
    //newflags = calc_vm_prot_bits(prot);
    newflags = prot;
    newflags |= (vma->vm_flags & ~(VM_READ | VM_WRITE | VM_EXEC));

    error = mprotect_fixup(vma,&pprev,vma->vm_start,vma->vm_end,newflags);
out:
    up_write(&task->mm->mmap_sem);
    return error;
}

/*
 * task_struct task->mm->mmap->vm_start,vm_end,vm_flags
 * mm_struct->mmap_rb read black tree
 * mm_struct->pgd -> pmd_t -> pte_t
 */

int init_task_vma(struct task_struct *task)
{
    int start_code = task->mm->start_code;
    int end_code = task->mm->end_code;
    int start_data = task->mm->start_data;
    int end_data = task->mm->end_data;
    int start_brk = task->mm->start_brk;
    //int brk = task->mm->brk;
    int start_stack = task->mm->start_stack;
    int i;
    unsigned long  vm_start,vm_end, vm_flags;

    printk("code start addr: 0x%lu\t,end addr: 0x%lu\n",start_code,end_code);
    static struct vm_area_struct *vma;
    static struct vm_area_struct *p;
    struct vm_area_struct *q;
    vma = task->mm->mmap;
    p = vma;
    for (i=0;i<VMACACHE_SIZE;i++) {
        q = task->vmacache[i];
        printk("task caching 0x%lu->0x%lu\n",q->vm_start,q->vm_end);
    }
    while (p->vm_prev) {
        p = p->vm_prev;
    }
    while (p->vm_next) {
        printk("vm_start:0x%lu, vm_end:0x%lu\t",p->vm_start,p->vm_end);
        if (p->vm_flags & VM_READ) {
            printk("R");
        } else {
            printk("-");
        }
        if (p->vm_flags & VM_WRITE) {
            printk("W");
        } else { printk("-"); }
        if (p->vm_flags & VM_EXEC) {
            printk("X");
            vm_start = p->vm_start;
            vm_end = p->vm_end;
            vm_flags = p->vm_flags;
            vm_flags &= !(VM_EXEC);
            modify_vma_prot(vm_start,VM_READ,task);
            //changeProt(vm_start, vm_end-vm_start,vm_flags,task);
        } else{ printk("-"); }
        printk("\t");
        if (p->vm_end < end_code && p->vm_start >start_code ) {
            printk("code page");
        } else if (p->vm_end < end_data && p->vm_start > start_data) {
            printk("data page");
        } else if (p->vm_start > start_brk) {
            printk("heap page");
        } else if (p->vm_start > start_stack) {
            printk("stack page");
        }
        printk("\n");
        p = p->vm_next;
    }
    printk("task %s total mapped vm %lu, total %lu vmas can exec\n",task->comm,task->mm->total_vm,task->mm->exec_vm);
    printk("pgd:0x%lu\n",task->mm->pgd);
    
    return 0;
}


