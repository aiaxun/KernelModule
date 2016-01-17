#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>

int init_task_vma(struct task_struct *task);
int changeProt(unsigned long start, size_t len, unsigned long prot,struct task_struct *task);
