KERNEL_VER=$(shell uname -r)
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
obj-m += page_handler.o

page_handler-objs=mark_page_nx.o trigger.o

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
