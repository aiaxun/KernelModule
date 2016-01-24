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
#include <linux/kallsyms.h>
#include <linux/kprobes.h>

//#include "mark_page_nx.h"
//#include "handle_page_fault.h"

static void j_signal_setup_done(int failed, struct ksignal *ksig, int stepping) 
{
    printk("signal_setup_done %s\n", current->comm);
    jprobe_return();
    return ;
}
static struct jprobe my_jprobe = {
    .entry = j_signal_setup_done,
    .kp = {
        .symbol_name = "signal_setup_done",
    },
};

int make_nx(unsigned long address) {
        unsigned int level;
        pte_t *pte = lookup_address(address, &level);
    if (pte->pte & ~_PAGE_NX) {
                pte->pte |= _PAGE_NX;
                printk("this page is marked nx\n");
            
    } else {
                printk("do not find user page\n");
            
    }
        return 0;

}
int make_x(unsigned long address) {
        unsigned int level;
        pte_t *pte = lookup_address(address,&level);
    if (pte->pte & _PAGE_NX) {
                pte->pte |= !_PAGE_NX;
                printk("this page is marked x\n");
            
    } else {
                printk("don't find user page\n");
            
    }
        return 0;

}

static int __init my_init(void)
{
    static struct task_struct *task = NULL;
    struct task_struct *p;
    printk("init module\n");
    //register_jprobe(&my_jprobe);

    //register_new_page_fault();
    unsigned long start_code ;
    unsigned long end_code;
    for_each_process(p) {
        if (strcmp(p->comm,"nginx") == 0) {
            task = p;
            break;
        }
    }
    if (task) {
        printk("find target task nginx\n");
        start_code = task->mm->start_code;
        end_code = task->mm->end_code;
        make_nx(start_code);
        make_nx(end_code);
        make_x(start_code);
        make_x(end_code);
    }else {
        printk("do not find nginx\n");
    }
    //mark_all_page_nx(current);
    
    return 0;
}

static void __exit my_exit(void)
{
    //unregister_new_page_fault();
    //unregister_jprobe(&my_jprobe);
    printk("module trigger exit\n");
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
