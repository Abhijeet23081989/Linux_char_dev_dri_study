#include"headers.h"
/*__init means:
 *-> This is the initialization function for initialising devices
 *->It will run only once in the lifetime of devices
 *->It cannot be invoked from within the device
 *->It releases all its resources after it is over
 *->The initialization function will be responsible for:
   1.Registering the device driver with the kernel
   2.Initialization the default device parameter*/
/*MODULE_AUTHOR("Abhijeet Srivastava");
MODULE_DESCRIPTION("Abhijeet 1st LKM","Please don't mind!!");
MODULE_LICENSE("GPL");*/
static int __init initializationFunc(void)
{
	printk(KERN_INFO"Hello Kernel\n");
	return 0;
}module_init(initializationFunc);
