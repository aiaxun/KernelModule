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
#include <linux/kallsyms.h>
#include <linux/signal.h>

#include "slide.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("sqt");
MODULE_VERSION("1.0");
static int  my_init(void)
{
    static struct task_struct *task;
    struct task_struct *p;
    printk("Module initing\n");
    
    //const char *sym_name = "mprotect_fixup";
    //unsigned long addr = kallsyms_lookup_name(sym_name);
    //printk("address: %lx\n",addr);
    for_each_process(p) {
        if (strcmp(p->comm,"nginx")==0) {
            task = p;
            break;
        }
    }
    
    //if (task ) init_task_vma(task);
    unsigned long addr = 0x00;
    addr = kallsyms_lookup_name("signal_delivered");
        printk("0x%lu\t",addr);
        printk("not found");
    return 0;
}

static void  my_exit(void) 
{
    printk("Module exiting \n");
    
}
module_init(my_init);
module_exit(my_exit);
