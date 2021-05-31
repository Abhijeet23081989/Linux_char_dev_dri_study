#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/completion.h>

MODULE_AUTHOR("ABHIJEET");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ABHIJEET_CHARACTER_DEVICE");
