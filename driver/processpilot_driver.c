#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "processpilot"

static dev_t device_number;
static struct cdev processpilot_cdev;
static struct class *processpilot_class;

static const char kernel_status[] =
    "ProcessPilot kernel component is active\n";

static int processpilot_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "ProcessPilot: device opened\n");
    return 0;
}

static int processpilot_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "ProcessPilot: device closed\n");
    return 0;
}

static ssize_t processpilot_read(
    struct file *file,
    char __user *buffer,
    size_t length,
    loff_t *offset)
{
    return simple_read_from_buffer(
        buffer,
        length,
        offset,
        kernel_status,
        sizeof(kernel_status) - 1
    );
}

static const struct file_operations processpilot_fops =
{
    .owner = THIS_MODULE,
    .open = processpilot_open,
    .release = processpilot_release,
    .read = processpilot_read
};

static int __init processpilot_init(void)
{
    int result;

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DEVICE_NAME
    );

    if (result < 0)
    {
        printk(KERN_ERR
               "ProcessPilot: failed to allocate device number\n");
        return result;
    }

    cdev_init(&processpilot_cdev, &processpilot_fops);

    result = cdev_add(
        &processpilot_cdev,
        device_number,
        1
    );

    if (result < 0)
    {
        unregister_chrdev_region(device_number, 1);
        return result;
    }

    processpilot_class = class_create(DEVICE_NAME);

    if (IS_ERR(processpilot_class))
    {
        cdev_del(&processpilot_cdev);
        unregister_chrdev_region(device_number, 1);
        return PTR_ERR(processpilot_class);
    }

    if (IS_ERR(device_create(
        processpilot_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME)))
    {
        class_destroy(processpilot_class);
        cdev_del(&processpilot_cdev);
        unregister_chrdev_region(device_number, 1);
        return -ENOMEM;
    }

    printk(KERN_INFO
           "ProcessPilot: kernel device initialized\n");

    return 0;
}

static void __exit processpilot_exit(void)
{
    device_destroy(
        processpilot_class,
        device_number
    );

    class_destroy(processpilot_class);

    cdev_del(&processpilot_cdev);

    unregister_chrdev_region(
        device_number,
        1
    );

    printk(KERN_INFO
           "ProcessPilot: kernel device removed\n");
}

module_init(processpilot_init);
module_exit(processpilot_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ProcessPilot Project");
MODULE_DESCRIPTION(
    "ProcessPilot Linux character device driver"
);
MODULE_VERSION("1.0");
