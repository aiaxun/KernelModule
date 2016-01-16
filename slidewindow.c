/*************************************************************************
	> File Name: slidewindow.c
	> Author: 
	> Mail: 
	> Created Time: 2016年01月12日 星期二 16时11分09秒
 ************************************************************************/

#include <linux/init.h> 
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shenqintao");
MODULE_DESCRIPTION("");

// when elf load and going to start, 
// mark all pages non-executable
// return number of executable pages;
int mark_all_page_nonexecutable(struct task_struct *task) {
    //int total_pages = 0;
    struct mm_struct *mm = task->mm;
    int start_code = mm->start_code;
    int end_code = mm->end_code;
    struct vm_area_struct *mmap = mm->mmap;
    int total_vm = mm->total_vm;
    struct vm_area_struct *first = mmap;
    int code_pages = 0;
    int exe_pages = 0;
    printk("start code :0x%x\tendo code: 0x%x\ttotal tm:%d\n",start_code,end_code,total_vm);
    //down_read(&mm->mmap_sem);
    /*while (first) {
        first = first->vm_prev;
    }*/
    while (first) {
        //if (first->vm_end <= end_code ){
            code_pages++;
            if (first->vm_flags & VM_WRITE) {
                printk("page %d is writable, addr from 0x%x to 0x%x\n",code_pages,first->vm_start,first->vm_end);
            }
            if (first->vm_flags & VM_EXEC) {
                exe_pages ++;
                printk("Page %d is executable,addr from 0x%x to 0x%x\n",code_pages,first->vm_start,first->vm_end);
            }
            if (first->vm_flags & VM_READ) {
                printk("Page %d is readable \n",code_pages);
            }
            
        //}
        first = first->vm_next;
    }
    printk("mm->exec_vm:%d , %d\n",mm->exec_vm,exe_pages);
    //up_read(&mm->mmap_sem);
    return code_pages;
}
struct task_struct *find_task_by_name(char *pname)
{
    struct task_struct *p;
    for_each_process(p) {
        if (strcmp(p->comm,pname)==0){
            return p;
        }
    }
    return NULL;
}

struct mm_struct *get_mm_from_task(struct task_struct *task)
{
    if (task)
        return task->mm;
    return NULL;
}

void visit_all_pages(struct vm_area_struct *mmap)
{
    unsigned long vm_start,vm_end;
    struct vm_area_struct *pre,*next;
    unsigned long pgprot;
    printk("will visit vma \n");
    pre = next = mmap;
    while(pre) {
        printk("pre\t");
        vm_start = pre->vm_start;
        vm_end = pre->vm_end;
        pgprot = pre->vm_page_prot.pgprot;
        printk("from %x to %x access: %x\n",vm_start,vm_end,pgprot);
        pre = pre->vm_prev;
    }
    while(next) {
        printk("next\t");
        printk("from %x to %x access: %x\n",next->vm_start,next->vm_end,next->vm_page_prot.pgprot);
        next = next->vm_next;
    }
}
int function_test(void)
{
    char *nginx = "nginx";
    struct task_struct *task = find_task_by_name(nginx);
    if (task) {
        struct mm_struct *mm = get_mm_from_task(task);
        struct vm_area_struct *mmap = mm->mmap;
        printk("Has found the mmap of pid: %d\n",task->pid);
        //visit_all_pages(mmap);
        mark_all_page_nonexecutable(task);
    }
    else printk("not found\n");
    
    return 0;
}

static int __init hello_init(void)
{
    printk("Entering This module \n");
    function_test();
    return 0;
}

static void __exit hello_exit(void)
{
    printk("Module exit");
}

module_init(hello_init);
module_exit(hello_exit);

