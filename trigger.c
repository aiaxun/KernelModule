/*************************************************************************
	> File Name: trigger.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月22日 星期五 18时44分55秒
 ************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

#include "mark_page_nx.h"

static int __init my_init(void)
{
    static struct task_struct *task = NULL;
    struct task_struct *p;
    printk("init module\n");
    for_each_process(p) {
        if (strcmp(p->comm,"nginx") == 0) {
            task = p;
            break;
        }
    }
    if (task) {
        mark_all_page_nx(task);
    }
    return 0;
}

static void __exit my_exit(void)
{
    printk("module trigger exit\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
