/*************************************************************************
	> File Name: new.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 19时21分41秒
 ************************************************************************/

#ifndef _NEW_H
#define _NEW_H
#include <linux/sched.h>

int register_new_page_fault_handler(void);
void unregister_new_page_fault_handler(void);

int mark_the_page_nx(struct task_struct *task, unsigned long addr);
int mark_the_page_x(struct task_struct *task, unsigned long addr);
int mark_all_pages_nx(struct task_struct *task);
int make_nx(unsigned long addr);
int make_x(unsigned long addr);

#endif
