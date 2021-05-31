#include"headers.h"
#include"declarations.h"
ssize_t writedev(struct file *myfile, const char __user *ubuff, size_t size, loff_t *offset)
{
	//_______________Declaration______________________________________________
	DEV* ldev;
	Qset* lqsetw;
	int noctw,nocsw,lsize,i,ret;
#ifdef DEBUG
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
#endif
	//_____________Saving device name saved in myfile's private_data__________
	ldev=(DEV*)myfile->private_data;
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_ERR"Error: unable to return address\n");
#endif
		goto OUT;
	}
	//______________Checking user buffer size_________________________________
	if(size < ldev->devsize)	
	noctw=lsize=size;
	else
	noctw=lsize=ldev->devsize;
	//_________________Calling createSCULL____________________________________
	lqsetw=ldev->first=createscull(noctw);
	if(!ldev->first)
	{
#ifdef DEBUG
		printk(KERN_ERR"Error: return address\n");
#endif
		goto OUT;
	}
	i=nocsw=0;
	//________________Writing from user buffer to kernel space SCULL___________
	while(noctw)
	{
		if(noctw>ldev->regsize)
			noctw=ldev->regsize;
		ret=copy_from_user(lqsetw->data[i],ubuff+nocsw,regsize);
			if(ret)
			{
#ifdef DEBUG
				printk(KERN_INFO"Partial write\n");
#endif
			}
		nocsw=nocsw+(nocsw-ret);
		noctw=lsize-nocsw;
		if(i<ldev->regsize)
			i++;
		else
		{
			lqsetw=lqsetw->next;
			i=0;
		}
	}
	ldev->datasize=nocsw;
#ifdef DEBUG
	printk(KERN_INFO"END=>%s\n",__func__);
#endif
	return nocsw;
OUT: return -1;
}
