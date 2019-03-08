PWD := $(shell pwd)

ccflags-y += -I$(src)/include/ -O3

RStest-objs := main.o rs.o
obj-m += RStest.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	sudo insmod RStest.ko
	sleep 3
	sudo rmmod RStest.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
