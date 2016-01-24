/*************************************************************************
	> File Name: mark_page.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 19时28分55秒
 ************************************************************************/

#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/cacheflush.h>
#include <asm/pgtable_types.h>
#include <asm/pgtable.h>
#include <asm/cacheflush.h>
#include "new.h"
#include "lbr.h"

int make_nx(unsigned long address) {
    /*
    unsigned int level;
    pte_t *pte = lookup_address(address, &level);
    if (pte->pte & ~_PAGE_NX) {
        pte->pte |= _PAGE_NX;
        printk("this page is marked nx\n");
    } else {
        printk("do not find user page\n");
    }*/
    int pagenums = 1;
    set_memory_nx(address, pagenums);
    printk("change %lx page nx\n",address);
    return 0;
}
int make_x(unsigned long address) {
    /*
    unsigned int level;
    pte_t *pte = lookup_address(address,&level);
    if (pte->pte & _PAGE_NX) {
        pte->pte |= !_PAGE_NX;
        printk("this page is marked x\n");
    } else {
        printk("don't find user page\n");
    }*/
    int pagenums = 1;
    set_memory_x(address, pagenums);
    printk("chagne %lx page exec\n",address);
    return 0;
}
int mark_the_page_nx(struct task_struct *task, unsigned long addr)
{
    make_nx(addr);
    return 0;
}

int mark_the_page_x(struct task_struct *task, unsigned long addr)
{
    make_x(addr);
    return 0;
}

int mark_all_pages_nx(struct task_struct *task) 
{
    //struct vm_area_struct *vma = task->mm->mmap;
    unsigned long start_code = task->mm->start_code;
    unsigned long end_code   = task->mm->end_code;
    unsigned long addr = start_code;
    //unsigned long pages = (end_code - start_code) >> PAGE_SHIFT;
    if (!tst_task_lbr(current)) { 
        goto out;
    }
    down_read(&task->mm->mmap_sem);
    for (addr = start_code; addr <= end_code;)
    {
        make_nx(addr);
        addr += 8;
    }
    printk("make all pages nx, %s\n", task->comm);
    up_read(&task->mm->mmap_sem);
out:
    return 0;
}
