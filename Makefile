KERNEL_VER=$(shell uname -r)
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
obj-m += page_handler.o

page_handler-objs=new_page_fault.o

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
