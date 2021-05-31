#include"headers.h"
#include"declarations.h"
int trimdev(DEV* ldev)
{
	Qset *lqset,*shqset;//lqset=local_qset,shqset=shadow_qset
	int i;
#ifdef DEBUG
	printk(KERN_INFO"Begin: %s\n",__func__);
#endif
	//_______________Checking if Device is present or not______________
	if(!ldev)
	{
#ifdef DEBUG
	printk(KERN_ERR"No Device present\n");
#endif
	goto OUT;
	}
	//________________Semaphore Before accessing____________________
	//if(down_interruptible(&ldev->s1))
           //      return -ERESTARTSYS;

	//_______________Checking if SCULL is present in Device__________
	if(!ldev->first)
	{
#ifdef DEBUG
	printk(KERN_INFO"Nothing to trim\n");
#endif
	goto RET;
	}
	//________________________Deleteing SCULL________________________
	while(ldev->first)
	{
		shqset=lqset=ldev->first;
		while(lqset->next)
		{
			shqset=lqset;
			lqset=lqset->next;
		}
		//_____________For freeing memory of **data_____________
		if(lqset->data)
		{
			//___________For freeing memory of data[i]_____
			for(i=ldev->noofreg-1;i>=0;i--)
			{
				if(lqset->data[i])
				{
					printk(KERN_INFO"i=%d\n",i);
					kfree(lqset->data[i]);
					lqset->data[i]=NULL;
				}
			}
			kfree(lqset->data);
			lqset->data=NULL;
		}
		if(lqset==shqset)
		{
			kfree(shqset);
			ldev->first=NULL;
		}
		else
		{
			kfree(shqset->next);
			shqset->next=NULL;
		}
	}
RET:
	//up(&ldev->s1);
	return 0;
OUT:
	return -1;
#ifdef DEBUG
	printk(KERN_INFO"End: %s\n",__func__);
#endif
}
