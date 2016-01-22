/*************************************************************************
	> File Name: trigger_page_fault.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 09时34分41秒
 ************************************************************************/

#ifndef _TRIGGER_PAGE_FAULT_H
#define _TRIGGER_PAGE_FAULT_H

extern int mark_page_not_executable(unsigned long address);
extern int mark_page_executable(unsigned long address, unsigned long pagenum);
extern int mark_all_page_non_executable(struct task_struct *task);
#endif
