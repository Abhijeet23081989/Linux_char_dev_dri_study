#include"headers.h"
#include"declarations.h"
Qset* createscull(int len)
{
int noi;//no. of items
int noq;//no. of quantums
int i;//counter variable for noi
int l;//Total no. of quantums
int k;//No. of quantums per item
Qset *first=(void*)0;//First Item
Qset *lqset;
#ifdef DEBUG
	printk(KERN_INFO"Begin: %s\n",__func__);
#endif
	//____________________________________For calculating noi___________________________
	noi=len/(noofreg*regsize);
	//___________________________________For incrementing noi___________________________
	if(len%(noofreg*regsize))
		noi++;
	printk(KERN_INFO"noi=%d\n",noi);
	//____________________________________Allocating Memory_____________________________
	for(i=0;i<noi;i++)
	{
		printk(KERN_INFO"i=%d\n",i);
		/*For Head Item*/
		if(i==0)
		{
			first=lqset=(Qset*)kmalloc(sizeof(Qset),GFP_KERNEL);
			//printk(KERN_INFO"lqsetfirst=%p\n",lqset);
			if(!lqset)
			{
#ifdef DEBUG
				printk(KERN_ERR"Error:qset\n");
#endif
				goto OUT;
			}
			//printk(KERN_INFO"@headnode\n");
			memset(lqset,'\0',sizeof(Qset));
			lqset->data=kmalloc(sizeof(void*)*noofreg,GFP_KERNEL);
			if(!lqset->data)
			{
#ifdef DEBUG
				printk(KERN_ERR"Error:qset->next\n");
#endif
				goto OUT;
			}
			memset(lqset->data,'\0',sizeof(void*)*noofreg);
		}
		/*For Items from Ist Item onwards uptill (noi-1)*/
		else
		{			
			lqset->next=(Qset*)kmalloc(sizeof(Qset),GFP_KERNEL);
			if(!lqset->next)
			{
#ifdef DEBUG
				printk(KERN_ERR"Error:qset->next\n");
#endif
				goto OUT;
			}
			//printk(KERN_INFO"@ %d node\n",i);
			lqset=lqset->next;
			//printk(KERN_INFO"lqset->next=%p\n",lqset->next);
			/*Allocate Memory for  Number of registers(array of pointers for **data)*/
			lqset->data=kmalloc(sizeof(void*)*noofreg,GFP_KERNEL);
			if(!lqset->data)
			{
#ifdef DEBUG
				printk(KERN_ERR"Error:qset->next\n");
#endif
				goto OUT;
			}
			memset(lqset->data,'\0',sizeof(void*)*noofreg);
			//lqset->next=NULL;
			//printk(KERN_INFO"lqsetlast=%p\n",lqset);
		}
	}
	//printk(KERN_INFO"first->next=%p\n",first->next);
	/*Bringing control back to item 1*/
	lqset=first;
	/////////////////////Quantum Creation/////////////////////////////
	/*Calculating noq*/
	noq=len/regsize;
	if(len%regsize)
		noq++;
	/*printk(KERN_INFO"noq=%d\n",noq);
	printk(KERN_INFO"len=%d\n",len);*/
	for(l=0,k=0;l<=noq;l++)
	{
		if(k<noofreg)
		{
			lqset->data[k]=kmalloc(regsize,GFP_KERNEL);
			if(!lqset->data[k])
			{
#ifdef DEBUG
				printk(KERN_ERR"Error:qset->next\n");
#endif
				goto OUT;
			}
			memset(lqset->data[k],'\0',regsize);
			k++;
		}
		else
		{
			lqset=lqset->next;
			k=0;
		}
		//printk(KERN_INFO"l=%d\n",l);
	}
	#ifdef DEBUG
	printk(KERN_INFO"End: %s\n",__func__);
	#endif
	return first;
OUT:printk(KERN_ERR"Error:COREDUMP\n");
    return (void*)0;
}
