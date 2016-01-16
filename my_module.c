/*************************************************************************
	> File Name: module.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月16日 星期六 14时01分28秒
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include "slide.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("sqt");
MODULE_VERSION("1.0");
static int __init my_init(void)
{
    static struct task_struct *task;
    struct task_struct *p;
    printk("Module initing\n");
    
    for_each_process(p) {
        if (strcmp(p->comm,"nginx")==0) {
            task = p;
            break;
        }
    }
    
    if (task ) init_task_vma(task);

    return 0;
}

static int __exit my_exit(void) 
{
    printk("Module exiting \n");
    
    return 0;
}
module_init(my_init);
module_exit(my_exit);
