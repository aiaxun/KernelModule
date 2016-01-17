#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>

int init_task_vma(struct task_struct *task);
int modify_vma_prot(unsigned long addr, unsigned long prot, struct task_struct *task);
