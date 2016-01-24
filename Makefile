KERNEL_VER=$(shell uname -r)
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
obj-m += trigger.o

trigger-objs=mark_page_nx.o trigger.o handle_page_fault.o

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
