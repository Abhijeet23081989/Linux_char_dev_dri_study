#include"headers.h"
#include"declarations.h"
int opendev(struct inode *appnode,struct file *apfile)
{
	int ret;
	DEV *ldev;
//#ifdef DEBUG
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
//#endif
	ldev = container_of(appnode->i_cdev,DEV,mycdev);
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_ERR"container_of:unable to cast address-type\n");
#endif
		goto OUT;
	}
	apfile->private_data=ldev;
	if((apfile->f_flags & O_ACCMODE)== O_WRONLY)
	{
		ret=trimdev(ldev);
	if(ret==-1)
	{
#ifdef DEBUG
		printk(KERN_ERR"Unable to trim\n");
#endif
		goto OUT;
	}
	}
//#ifdef DEBUG
	printk(KERN_INFO"END=>%s\n",__func__);
//#endif
	return 0;
OUT:return -1;
}
