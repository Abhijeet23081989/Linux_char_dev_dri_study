#include"headers.h"
#include"declarations.h"
ssize_t readdev(struct file *myfile, char __user *ubuff, size_t size, loff_t *offset)
{
	//_______________Declaration______________________________________________
	DEV* ldev;
	Qset* lqsetr;
	int noctr,nocsr,lsize,i,j,ret,qui,remq;
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
	//___________Using Wait_for_competion____________________________________
	wait_for_completion(&ldev->c1);
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
	j=i=nocsr=0;
	qui=(*offset)/regsize;
	remq=(*offset)%regsize;
	lsize=noctr=noctr-(qui*regsize+remq);
	//___________________________Semaphore for read____________________________
//	if(down_interruptible(&ldev->s1))
  //                return -ERESTARTSYS;
	//________________Reading from kernel space SCULL to user buffer___________
	while(noctr)
	{
		if(noctr>regsize)
			noctr=regsize;
		printk(KERN_INFO"i=%d\n",i);
		ret=copy_to_user(ubuff+nocsr,(lqsetr->data[i+qui]+remq),regsize-remq);
			if(ret)
			{
#ifdef DEBUG
				printk(KERN_INFO"Partial write\n");
#endif
			}
		nocsr=nocsr+(noctr-(ret+remq));
		noctr=lsize-nocsr;
		if((i+qui)==noofreg-1)
		{
			lqsetr=lqsetr->next;
			i=0;
			qui=0;
		}
		else
		{
			remq=0;
			i++;
		}
	}
	// up(&ldev->s1);
//complete(&ldev->c1);	
#ifdef DEBUG
	printk(KERN_INFO"END=>%s\n",__func__);
#endif	
return nocsr;
OUT: return -1;
}
