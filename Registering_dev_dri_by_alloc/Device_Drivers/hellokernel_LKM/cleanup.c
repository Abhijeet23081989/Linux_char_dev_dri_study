#include"headers.h"
void __exit cleanupFunc(void)
{
	printk(KERN_INFO"I fare the well breathen....for thou art have taken your first step towards kernel build\n");
}
module_exit(cleanupFunc);
