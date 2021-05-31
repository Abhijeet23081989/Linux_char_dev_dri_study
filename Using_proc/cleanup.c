#include"headers.h"
#include"declarations.h"
int lc;
void __exit cleanupFunc(void)
{
#ifdef DEBUG
	printk(KERN_INFO"Abhijeet_mod driver is removed now.Have a nice day!!:)\n");
#endif
	///////////////////////////////Unregister device driver///////////////////////////////////
	for(lc=0;lc<nod;lc++)//1
		cdev_del(&dev[lc].mycdev);
	kfree(dev);//2
	unregister_chrdev_region(devno,nod);//3
	remove_proc_entry("MyNodeinfo",NULL);
}
module_exit(cleanupFunc);
