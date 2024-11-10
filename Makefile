obj-m := bootkern.o
KDIR := /lib/modules/6.11.2-amd64/build
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
