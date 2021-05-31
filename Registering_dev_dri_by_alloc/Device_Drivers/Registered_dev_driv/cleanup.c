#include"headers.h"
#include"declarations.h"
void __exit cleanupFunc(void)
{
	printk(KERN_INFO"I fare the well breathen....for thou art have taken your first step towards kernel build\n");
	////////////////////////////////Unregister device driver/////////////////////////////////
	kfree(dev);
	unregister_chrdev(new_majorno,DEVNAME);
}
module_exit(cleanupFunc);
