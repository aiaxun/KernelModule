/*************************************************************************
	> File Name: mark_page_nx.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 15时56分18秒
 ************************************************************************/

#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/cacheflush.h>
#include "mark_page_nx.h"

static int window_size=1;

static struct page *my_follow_page(struct vm_area_struct *vma,
        unsigned long addr)
{
    unsigned int unused_page_mask;
    unsigned long func;
    struct page *(*fpm)(struct vm_area_struct *,
            unsigned long , unsigned int, unsigned int *);
    func = kallsyms_lookup_name("follow_page_mask");
    fpm = func;
    return (*fpm)(vma,addr, FOLL_GET, &unused_page_mask);
}


int mark_address_page_x(struct task_struct *task, unsigned long addr) {
    struct vm_area_struct *vma;
    struct page *p;
    int ret = 0;
    down_read(&task->mm->mmap_sem);
    vma = find_vma(task->mm,addr);
    p = my_follow_page(vma,addr);
    if (!p) {
        ret = -1;
        goto out;
    }
    set_pages_x(p,window_size);
out:
    up_read(&task->mm->mmap_sem);
    return ret;
}

int mark_address_page_nx(struct task_struct *task, unsigned long addr) 
{
    struct vm_area_struct *vma;
    struct page *target_page;
    int ret = 0;
    down_read(&task->mm->mmap_sem);
    vma = find_vma(task->mm,addr);
    target_page = my_follow_page(vma,addr);
    if (!target_page) {
        ret = -1;
        goto out;
    }
    set_pages_nx(target_page,window_size);
out:
    up_read(&task->mm->mmap_sem);
    return ret;
}

int mark_all_page_nx(struct task_struct *task)
{
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *vma = mm->mmap;
    struct vm_area_struct *first = vma;
    unsigned long start_code = mm->start_code;
    unsigned long   end_code = mm->end_code;
    unsigned addr;
    struct page *old,*now;
    //unsigned long pagenums = (end_code - start_code)<<;
    down_read(&task->mm->mmap_sem);
    old = my_follow_page(vma, start_code);
    addr = (unsigned long)page_address(old);
    for (addr; addr <= end_code; ) {
        now = my_follow_page(vma,addr);
        set_pages_nx(now,1);
        addr += PAGE_SIZE;
    }
out:
    up_read(&task->mm->mmap_sem);
    return 0;
}

MODULE_LICENSE("GPL");
