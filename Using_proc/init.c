#include"headers.h"
#include"declarations.h"
#include"file_opr.h"
#include"file_proc_opr.h"
DEV *dev;
dev_t devno,devid;
int minorno;
int majorno;
int retin,ret1;
int nod,noofreg,regsize,devsize,datasize;
/////////////////////////////For initiating module parameter/////////////////////////////////
module_param(nod,int,S_IRUGO);
module_param(noofreg,int,S_IRUGO);
module_param(regsize,int,S_IRUGO);
module_param(devsize,int,S_IRUGO);
module_param(datasize,int,S_IRUGO);
static int __init initializationFunc(void)
{
	int l;
#ifdef DEBUG
	printk(KERN_INFO"Abhijeet_mod driver is inserted\n");
///////////////////////////Register Device Driver with Kernel device/////////////////////////
	printk(KERN_INFO"nod1=%d\n",nod);
#endif
	minorno=MINR;
	retin=alloc_chrdev_region(&devno,minorno,nod,DEVNAME);
	if(retin==-1)
	{
#ifdef DEBUG
		printk(KERN_ERR"alloc_chrdev_region failure\n");
#endif
		goto OUT;
	}
	majorno=MAJOR(devno);
	minorno=MINOR(devno);
#ifdef DEBUG
	printk(KERN_INFO"Major Number=%d\n",majorno);
	printk(KERN_INFO"Minor Number=%d\n",minorno);
	printk(KERN_INFO"nod2=%d\n",nod);
#endif
/////////////////////////////Allocate space for device///////////////////////////////////////
	dev=kmalloc(sizeof(DEV)*nod,GFP_KERNEL);/*GFP_KERNEL-->Get From Page of Kernel*/
	if(!dev)
	{
		printk(KERN_ERR"kmalloc failure\n");
		goto OUT;
	}
	memset(dev,'\0',sizeof(DEV));
	dev->first=(void*)0;
////////////////////////Initialize device for device//////////////////////////////////////////
for(l=0;l<nod;l++)
{
	cdev_init(&dev[l].mycdev,&fops);
	/*For Initialising struct file_operations fops*/
	dev[l].noofreg=noofreg;//no of devices
	dev[l].regsize=regsize;//register size
	dev[l].devsize=devsize;//device size
	dev[l].datasize=datasize;//data size
	//___________Semaphore Initialisation_____________________
	//sema_init(&dev[l].s1,1);
	//__________Completion Initialisation____________________
	init_completion(&dev[l].c1);
	devid=MKDEV(majorno,l);//for joining major and minor number
////////////////////////Add device to device table////////////////////////////////////////////
	ret1=cdev_add(&dev[l].mycdev,devid,1);
	if(ret1==-1)
	{
#ifdef DEBUG
		printk(KERN_INFO"cdev_add()fail\n");
#endif
		goto OUT;
	}
}
proc_create_data("MyNodeinfo",0,NULL,&proc_fops,NULL);
	return 0;
OUT:return -1;
}module_init(initializationFunc);
