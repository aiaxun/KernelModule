/*************************************************************************
	> File Name: mark_page_nx.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 15时47分29秒
 ************************************************************************/

#ifndef _MARK_PAGE_NX_H
#define _MARK_PAGE_NX_H
extern int mark_address_page_nx(struct task_struct *task, unsigned long addr);
extern int mark_address_page_x(struct task_struct *task, unsigned long addr);
extern int mark_all_page_nx(struct task_struct *task);

#endif
