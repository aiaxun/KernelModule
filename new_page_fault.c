/*************************************************************************
	> File Name: new_page_fault.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月20日 星期三 09时24分57秒
 ************************************************************************/

#include "new_page_fault.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/elf.h>
#include <linux/init.h>
#include <linux/binfmts.h>

static char new_elf_load[NAME_MAX] = "load_elf_binary";
static char new_elf_map[NAME_MAX] = "elf_map";
static char new_do_page_fault[NAME_MAX] = "do_page_fault";

static unsigned long jdo_elf_map(struct file *filep, unsigned long addr,
                                struct elf_phdr *eppnt, int prot, int type,
                                unsigned long total_size);
static struct jprobe my_jprobe = {
    .entry  = jdo_elf_map,
    .kp = {
        .symbol_name = "elf_map"
    },
};
/*
static struct kprobe new_do_page_fault = {
    .symbol_name = "do_page_fault";
}*/

static unsigned long jdo_elf_map(struct file *filep, unsigned long addr,
        struct elf_phdr *eppnt, int prot, int type,
        unsigned long total_size)
{
    printk("mapping file file, %s\n",current->comm);
    if (prot & VM_EXEC) {
        if (0==strcmp(current->comm,"nginx")) {
            printk("find nginx ");
            prot &= !(VM_EXEC);
            if (prot & VM_EXEC) {
                printk("modify error\n");
            }
        }
    } else {
        if (prot & VM_WRITE) {
            printk("%s writable\n",current->comm);
        }
    }
    jprobe_return();
    return 0;
}

static int __init my_init(void) 
{
    int ret;
    ret = register_jprobe(&my_jprobe);
    if (ret < 0){
        printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
        return -1;
    }
    printk(KERN_INFO "Planted jprobe at %p, handler addr is %p\n",
            my_jprobe.kp.addr, my_jprobe.entry);
    return 0;
}

static void __exit my_exit(void) 
{
    printk("module exit\n");
    unregister_jprobe(&my_jprobe);
    printk(KERN_INFO "unregister_jprobe");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
