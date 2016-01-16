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
    printk("code start addr: 0x%p\t,end addr: 0x%p\n",start_code,end_code);
    static struct vm_area_struct *vma;
    static struct vm_area_struct *p;
    vma = task->mm->mmap;
    p = vma;
    while (p->vm_prev) {
        p = p->vm_prev;
    }
    while (p->vm_next) {
        printk("vm_start:0x%p, vm_end:0x%p\n",p->vm_start,p->vm_end);
        p = p->vm_next;
    }
    return 0;
}
