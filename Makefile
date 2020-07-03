obj-m := dev_null_segv.o

RM := rm
CP := cp
CHMOD := chmod
MKNOD := mknod
INSMOD := insmod
RMMOD := rmmod

default:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

load:
	$(INSMOD) dev_null_segv.ko
	$(MKNOD) /dev/null_segv c 62 1
	$(CHMOD) 666 /dev/null_segv
unload:
	$(RMMOD) dev_null_segv.ko
	$(RM) -f /dev/null_segv
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
