PWD := $(shell pwd)

ccflags-y += -I$(src)/include/

RStest-objs := main.o rs.o
obj-m += RStest.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	sudo insmod RStest.ko
	sudo rmmod RStest.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
