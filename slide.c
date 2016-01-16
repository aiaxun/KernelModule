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
    unsigned int personality = task->personality;
    //down_write(&mm->mmap_sem);
    while (first) {
        if (is_code_page(first,start_code,end_code)!=1) {
            continue;
        }
        printk("Page prot: %p\n",first->vm_flags);
        set_vma_non_exec(first,personality);
        first = first->vm_next;
    }
    //up_write(&mm->mmap_sem);
    return 0;
}

int set_vma_exec(struct vm_area_struct *vma,unsigned int personality)
{ 
    unsigned long flags = vma->vm_flags;
    /*if ((prot & PROT_READ) && (personality & READ_IMPLIES_EXEC)) {

    }*/
    if (flags & VM_EXEC) {
        flags &= (!VM_EXEC);
    }
    //vma->vm_flags = flags;
    printk("set exec at code %p->%p\n",vma->vm_start,vma->vm_end);
    return 0;
}

int set_vma_non_exec(struct vm_area_struct *vma, unsigned int personality)
{
    unsigned long flags = vma->vm_flags;
    if (!(flags & VM_EXEC)) {
        flags |= VM_EXEC;
    }
    //vma->vm_flags = flags;
    printk("set non-exec at %p->%p\n",vma->vm_start,vma->vm_end);
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
    if (vma->vm_start >= start_code && vma->vm_end <= end_code) {
        return 1;
    }
    return 0;
}
