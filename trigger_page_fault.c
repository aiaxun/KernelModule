/*************************************************************************
	> File Name: trigger_page_fault.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 09时51分46秒
 ************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <asm/traps.h>
#include <asm/desc_defs.h>
#include <linux/sched.h>
#include <linux/kprobes.h>
#include <asm/cacheflush.h>
#include <linux/kallsyms.h>
#include "trigger_page_fault.h"

static task_struct *task;

struct page *my_follow_page(struct vm_area_struct *vma,
                           unsigned long address, unsigned int foll_pages)
{
    struct page *(*follow_page)(struct vm_area_struct *, unsigned long ,unsigned int);
    unsigned long addr = kallsyms_lookup_name("follow_page");
    return (*follow_page)(vma,address,foll_pages);
}
void set_monitor_task(struct task_struct *p)
{
    task = p;
}


int mark_page_not_executable(unsigned long address)
{
    struct vm_area_struct *vma = task->mm->mmap;
    //struct vm_area_struct *first = vma;
    down_read(&task->mm->mmap_sem);
    struct page *this_page = my_follow_page(vma,address,)
    

    up_read(&task->mm->mmap_sem);
    return 0;
}

int mark_page_executable(unsigned long address, unsigned long pagenum)
{
    
}

int mark_all_page_non_executable(unsigned long address, unsigned long pagenum)
{
    struct vm_area_struct *vma = task->mm->mmap;
    struct vm_area_struct *first = vma;
    unsigned long start,end, count;
    int val = 0;

    while (first->vm_prev) {
        first = first->vm_prev;
    }
    count = 0;
    while (first) {
        if (first->vm_flags & VM_EXEC) {
            start = first->vm_start;
            end = first->vm_end;
            printk("mark nx from 0x%lu to 0x%lu\n",start,end);
            val = set_memory_nx(start,(end->start)>>PAGE_SHIFT);
            if (val == 0) {
                printk("not support nx\n");
            }
            count ++;
        }
    }
    return count;
}
