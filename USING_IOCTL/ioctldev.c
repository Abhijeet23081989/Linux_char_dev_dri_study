#include"headers.h"
#include"declarations.h"
#include"ioctl.h"
long unlocked_ioctldev (struct file *myfile, unsigned int cmnd, unsigned long arg)
{
	DEV *ldev;
	int qstsz;
	printk(KERN_INFO"Begin:%s\n",__func__);
	ldev=myfile->private_data;
	if(!ldev)
	{
#ifdef DEBUG
		printk(KERN_ERR"No device info present!!\n");
#endif
		goto OUT;
	}
	qstsz=(ldev->regsize)*(ldev->noofreg);
		printk(KERN_INFO"before access!!\n");
	//if(access_ok(VERIFY_WRITE,ldev,sizeof(DEV))==-1)
	//{
		printk(KERN_INFO"after access!!\n");
	switch(cmnd)
	{
		case RESETSYS://1
			ldev->noofreg=NOOFREG;
			ldev->regsize=REGSIZE;
			ldev->devsize=DEVSIZE;
			atomic_set(&ldev->datasize,datasize);
			printk(KERN_INFO"Inside RESETSYS\n");
			break;
		case GETQUANSIZE://2
			put_user(ldev->regsize,(int __user*)arg);
			printk(KERN_INFO"Inside GETQUANSIZE\n");
			break;
		case SETQUANSIZE://3
			get_user(ldev->regsize,(int __user*)arg);
			printk(KERN_INFO"Inside SETQUANSIZE\n");
			break;
		case GETQSETSIZE://4
			qstsz=(ldev->regsize)*(ldev->noofreg);
			put_user(qstsz,(int __user*)arg);
			printk(KERN_INFO"Inside GETQSETSIZE\n");
			break;
		case SETQSETSIZE://5
			get_user(qstsz,(int __user*)arg);
			ldev->noofreg=qstsz/(ldev->regsize);
			printk(KERN_INFO"Inside SETQSETSIZE\n");
			break;
		case GETDEVSIZE://6
			put_user(ldev->devsize,(int __user*)arg);
			printk(KERN_INFO"Inside GETDEVSIZE\n");
			break;
		case SETDEVSIZE://7
			get_user(ldev->devsize,(int __user*)arg);
			printk(KERN_INFO"Inside SETDEVSIZE\n");
			break;
		case GETBAUDRATE://8
			//put_user();
			printk(KERN_INFO"Inside GETBAUDRATE\n");
			break;
		case SETBAUDRATE://9
			//get_user();
			printk(KERN_INFO"Inside SETBAUDRATE\n");
			break;
	}
	//}
	return arg;
OUT:
	return -1;
	printk(KERN_INFO"End:%s\n",__func__);
}
