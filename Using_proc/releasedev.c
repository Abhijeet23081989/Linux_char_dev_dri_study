#include"headers.h"
#include"declarations.h"
int releasedev(struct inode *appinode,struct file *apfile)
{
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
	//kfree(apfile);
	//appinode=(void*)0;
	//apfile=(void*)0;
	printk(KERN_INFO"END=>%s\n",__func__);
	return 0;
}
