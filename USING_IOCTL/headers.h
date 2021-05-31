#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/spinlock.h>
#include<asm-generic/ioctl.h>
#include<linux/kd.h>
#include<asm/atomic.h>

MODULE_AUTHOR("ABHIJEET");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ABHIJEET_CHARACTER_DEVICE");
