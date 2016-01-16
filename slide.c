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
    printk("start addr: 0x%p\t,end addr: 0x%p\n",start_code,end_code);
    return 0;
}
