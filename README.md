# BootKern

Bootkern is a module developed by me to pull boot logs in a simple, easy and direct way

Use "sudo make" to create the build file

"insmod bootkern.ko"

"dmesg"

and there you will have the message: [+] Boot logs captured to /tmp/djfbksbfwf.txt

then after a "cat /tmp/djfbksbfwf.txt"

And there the boot logs will appear, and to remove the module use "rmmod bootkern" and remember to use all commands in root mode or with sudo

If the Makefile doesn't work, check your kernel version, and if it's outdated, update it by downloading your kernel headers.
