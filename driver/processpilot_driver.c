#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init processpilot_init(void)
{
    printk(KERN_INFO "ProcessPilot: kernel driver loaded\n");
    return 0;
}

static void __exit processpilot_exit(void)
{
    printk(KERN_INFO "ProcessPilot: kernel driver unloaded\n");
}

module_init(processpilot_init);
module_exit(processpilot_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ProcessPilot Team");
MODULE_DESCRIPTION("ProcessPilot Linux Kernel Driver");
