/*************************************************************************
	> File Name: slide.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月16日 星期六 11时06分26秒
 ************************************************************************/

#include "slide.h"

static struct vm_operations_struct *vm_ops;

int init_task_vmas(struct task_struct *task)
{
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *mmap = mm->mmap;
    int start_code = mm->start_code;
    int end_code = mm->end_code;
    struct vm_area_struct *first = get_first_vma(mmap);
    while (first) {
        if (is_code_page(first,start_code,end_code)!=1) {
            continue;
        }
        printk("Page prot: %p\n",first->vm_flags);
        set_vma_exec(firt);
        first = first->vm_next;
    }
    return 0;
}

int set_vma_exec(struct vm_area_struct *vma)
{
    
    return 0;
}

int set_vma_non_exec(struct vm_area_struct *vma)
{
    return 0;
}

struct vm_area_struct *get_first_vma(struct vm_area_struct *mmap) 
{
    struct vm_area_struct *first = mmap;
    while (first->vm_prev) {
        first = first->vm_prev;
    }
    return first;
}

int is_code_page(struct vm_area_struct *vma, unsigned long start_code, unsigned long end_code) 
{
    if (start_code < end_code) return -1;
    if (vma->vm_start >= start_code && vma->end_code <= end_code) {
        return 1;
    }
    return 0;
}
