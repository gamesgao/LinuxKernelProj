obj-m:= procKernel2.o simpleKernel.o procKernel.o paramKernel.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers