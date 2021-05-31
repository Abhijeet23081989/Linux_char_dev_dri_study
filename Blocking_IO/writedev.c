#include"headers.h"
#include"declarations.h"
ssize_t writedev(struct file *myfile, const char __user *ubuff, size_t size, loff_t *offset)
{
	//_______________Declaration______________________________________________
	DEV* ldev;
	Qset* lqsetw;
	int noctw,nocsw,lsize,i,ret;
	printk(KERN_INFO"Begin:%s\n",__func__);
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
	if(size < devsize)	
	noctw=lsize=size;
	else
	noctw=lsize=devsize;
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
		if(noctw>regsize)
			noctw=regsize;
		ret=copy_from_user(lqsetw->data[i],ubuff+nocsw,regsize);
		printk(KERN_INFO"ret=%d\n",ret);
			if(ret)
			{
#ifdef DEBUG
				printk(KERN_INFO"Partial write\n");
#endif
			}
		nocsw=nocsw+(noctw-ret);
		noctw=lsize-nocsw;
			printk(KERN_INFO"noctw=%d\n",noctw);
			printk(KERN_INFO"nocsw=%d\n",nocsw);
			printk(KERN_INFO"data[%d]=%s\n",i,(char*)lqsetw->data[i]);
		if(i==noofreg-1)
		{
			lqsetw=lqsetw->next;
			i=0;
		}
		else
			i++;
	}
	ldev->datasize=nocsw;
	//_______________________Waking-up applications in waiting queue______________
	wake_up_interruptible(&ldev->wqu);
#ifdef DEBUG
	printk(KERN_INFO"END=>%s\n",__func__);
#endif
	return nocsw;
OUT: return -1;
}
