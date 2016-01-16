#include <linux/shed.h>
#include <linux/mm_types.h>
#include <linux/mm.h>


int set_vma_exec(struct vm_area_struct *vma);
int set_vma_non_exec(struct vm_area_struct *vma);
int handle_page_fault();

