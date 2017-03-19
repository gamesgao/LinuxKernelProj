#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static int kernel_number;
module_param(kernel_number, int, 0644);

static int __init hello_init(void){
    printk(KERN_INFO "Hello world\n");
    printk(KERN_INFO "Param:kernel_number:%d;\n", kernel_number);
    return 0;
}




static void __exit hello_exit(void){
    printk(KERN_INFO "Goodbye world\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print-param");
MODULE_AUTHOR("Guyao");

module_init(hello_init);
module_exit(hello_exit);