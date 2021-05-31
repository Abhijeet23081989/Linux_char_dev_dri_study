#include"headers.h"
#include"declarations.h"
ssize_t readdev(struct file *myfile, char __user *ubuff, size_t size, loff_t *offset)
{
	//_______________Declaration______________________________________________
	DEV* ldev;
	Qset* lqsetr;
	int noctr,nocsr,lsize,i,ret;
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
	if(size > ldev->datasize)	
	noctr=lsize=ldev->datasize;
	else
	noctr=lsize=size;
	//___________Copying head node of SCULL to local Qset ptr_________________
	lqsetr=ldev->first;
	if(!ldev->first)
	{
#ifdef DEBUG
		printk(KERN_ERR"Error: return address\n");
#endif
		goto OUT;
	}
	i=nocsr=0;
	//________________Reading from kernel space SCULL to user buffer___________
	while(noctr)
	{
		if(noctr>ldev->regsize)
			noctr=ldev->regsize;
		ret=copy_to_user(ubuff+nocsr,lqsetr->data[i],regsize);
			if(ret)
			{
#ifdef DEBUG
				printk(KERN_INFO"Partial write\n");
#endif
				goto RET;
			}
		nocsr=nocsr+(nocsr-ret);
		noctr=lsize-nocsr;
		if(i<ldev->regsize)
			i++;
		else
		{
			lqsetr=lqsetr->next;
			i=0;
		}
	}
#ifdef DEBUG
	printk(KERN_INFO"END=>%s\n",__func__);
#endif	
RET:return nocsr;
OUT: return -1;
}
