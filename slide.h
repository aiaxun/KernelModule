#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>

int init_task_vmas(struct task_struct *task);
int set_vma_exec(struct vm_area_struct *vma,unsigned int personality);
int set_vma_non_exec(struct vm_area_struct *vma, unsigned int personality);

//int my_handle_page_fault(void);

int *(fault)(struct vm_area_struct *vma, struct vm_fault *vmf);

struct vm_area_struct *get_first_vma(struct vm_area_struct *mmap);
int is_code_page(struct vm_area_struct *vma,unsigned long start_code, unsigned long end_code);
