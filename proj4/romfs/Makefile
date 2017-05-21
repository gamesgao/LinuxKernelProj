#
# Makefile for the linux RomFS filesystem routines.
#
# obj-m:= mtest.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-$(CONFIG_ROMFS_FS) += romfs.o

romfs-y := storage.o super.o

ifneq ($(CONFIG_MMU),y)
romfs-$(CONFIG_ROMFS_ON_MTD) += mmap-nommu.o
endif

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers

