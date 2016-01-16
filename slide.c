/*************************************************************************
	> File Name: slide.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月16日 星期六 11时06分26秒
 ************************************************************************/
#include "slide.h"

/*
 * task_struct task->mm->mmap->vm_start,vm_end,vm_flags
 * 
 */

int init_task_vma(struct task_struct *task)
{
    int start_code = task->mm->start_code;
    int end_code = task->mm->end_code;
    int start_data = task->mm->start_data;
    int end_data = task->mm->end_data;
    int start_brk = task->mm->start_brk;
    int brk = task->mm->brk;
    int start_stack = task->mm->start_stack;
    int i;
    printk("code start addr: 0x%p\t,end addr: 0x%p\n",start_code,end_code);
    static struct vm_area_struct *vma;
    static struct vm_area_struct *p;
    struct vm_area_struct *q;
    vma = task->mm->mmap;
    p = vma;
    for (i=0;i<VMACACHE_SIZE;i++) {
        q = task->vmacache[i];
        printk("current caching 0x%p->0x%p\n",q->vm_start,q->vm_end);
    }
    while (p->vm_prev) {
        p = p->vm_prev;
    }
    while (p->vm_next) {
        printk("vm_start:0x%p, vm_end:0x%p\t",p->vm_start,p->vm_end);
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
    printk("task %s total mapped vm %d, total %d vmas can exec\n",task->comm,task->mm->total_vm,task->mm->exec_vm);

    
    return 0;
}
