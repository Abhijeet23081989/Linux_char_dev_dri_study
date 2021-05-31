#include"headers.h"
#include"declarations.h"
int releasedev(struct inode *appinode,struct file *apfile)
{
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
	printk(KERN_INFO"END=>%s\n",__func__);
	return 0;
}
