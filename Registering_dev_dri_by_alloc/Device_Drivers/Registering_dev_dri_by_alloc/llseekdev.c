#include"headers.h"
#include"declarations.h"
loff_t llseekdev(struct file *myfile, loff_t ofst, int skpr)
{
	printk(KERN_INFO"BEGIN==>%s\n",__func__);
	printk(KERN_INFO"END=>%s\n",__func__);
	return 0;
}
