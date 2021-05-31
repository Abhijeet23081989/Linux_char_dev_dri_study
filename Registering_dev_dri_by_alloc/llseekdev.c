#include"headers.h"
#include"declarations.h"
loff_t llseekdev(struct file *myfile, loff_t ofst, int origin)
{
	//____________________________Declaration_______________________
	DEV *ldev;
	Qset* lqset;
	ldev=NULL;
	lqset=NULL;
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
	//______________Extracting DEV variable from private_data________
	ldev=(DEV*)myfile->private_data;
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_ERR"no address to seek\n");
#endif
	}
	//______________Checking if OFFSET is greater than datasize_______
	if(ofst>ldev->datasize)
	{
#ifdef DEBUG
		printk(KERN_ERR"Offset to big!!\n");
#endif
	} 
	//_____________Making a local local copy of head node_____________
	lqset=ldev->first;
	//_________Semaphore down before llseek______________________
	//if(down_interruptible(&ldev->s1))
           //   return -ERESTARTSYS;
	//______Choosing origin point from SEEK_SET,SEEK_CUR or SEEK_END__
	switch(origin)
	{

		case SEEK_SET://0
			{
#ifdef DEBUG
				printk(KERN_INFO"Inside SEEK_SET\n");
#endif
				myfile->f_pos=0;
				if(ofst<ldev->datasize && ofst>0)
				myfile->f_pos=myfile->f_pos+ofst;
			}
			break;
		case SEEK_CUR://1
			{
#ifdef DEBUG
				printk(KERN_INFO"Inside SEEK_CUR\n");
#endif
				if(ofst>=0)
				{
					if((myfile->f_pos+ofst) <= ldev->datasize)
						myfile->f_pos=myfile->f_pos+ofst;
				}
				else
				{
					if((myfile->f_pos+ofst)<0)
					{
						printk(KERN_ERR"offset not possible\n");
						return (loff_t)-1;
					}
					else
						myfile->f_pos=myfile->f_pos+ofst;
				}
			}
			break;
		case SEEK_END://2
			{
				myfile->f_pos=ldev->datasize;//Assiging datasize to f_pos to signiify SEEK_END
			printk(KERN_INFO"Inside SEEK_END\n");
			if(ofst<0 && (-1)*ofst<=ldev->datasize)
			myfile->f_pos=myfile->f_pos+ofst;
			else if(ofst>0)
			{
				if((myfile->f_pos+ofst)>ldev->datasize)
				{
#ifdef DEBUG
					printk(KERN_ERR"offset to big\n");
#endif
				goto OUT;
				}
			}
			}
			break;
	}
	up(&ldev->s1);
	printk(KERN_INFO"END=>%s\n",__func__);
	return myfile->f_pos;
OUT: return -1;
}
