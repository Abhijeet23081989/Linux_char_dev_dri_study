#include"headers.h"
#include"declarations.h"
#include"file_opr.h"
DEV *dev;
int new_majorno;
int majorno;
static int __init initializationFunc(void)
{
	printk(KERN_INFO"Hello Kernel\n");
///////////////////////////Register Device Driver with Kernel device/////////////////////////
	majorno=MAJR;
	new_majorno=register_chrdev(majorno,DEVNAME,&fops);
	if(new_majorno==-1)
	{
		printk(KERN_ERR"register_chrdev failure\n");
		goto OUT;
	}
/////////////////////////////Allocate space for device///////////////////////////////////////
	dev=kmalloc(sizeof(DEV),GFP_KERNEL);
	if(!dev)
	{
		printk(KERN_ERR"kmalloc failure\n");
		goto OUT;
	}
	memset(dev,'\0',sizeof(DEV));
	//Initialize device for device
	//Add device entry into device table
	return 0;
OUT:printk(KERN_INFO"ERROR OUT\n");
    return 1;
}module_init(initializationFunc);
