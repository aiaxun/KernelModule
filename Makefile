KERNEL_VER=$(shell uname -r)
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
obj-m += slides.o
slides-objs=slide.o my_module.o

all:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules
clean:
	make -C $(KERNEL_DIR) M=$(shell pwd) modules clean
