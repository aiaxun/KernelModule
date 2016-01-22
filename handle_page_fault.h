/*************************************************************************
	> File Name: handle_page_fault.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 09时14分24秒
 ************************************************************************/

#ifndef _HANDLE_PAGE_FAULT_H
#define _HANDLE_PAGE_FAULT_H
extern int register_new_page_fault(void);
extern void unregister_new_page_fault(void);
#endif
