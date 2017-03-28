#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static int param_int = 0;
static char* param_str = "no parameter input.\n            ";
static int param_array[200] = {0};
static int param_array_num = 0;
module_param(param_int, int, 0644);
module_param(param_str, charp, 0644);
module_param_array(param_array, int, &param_array_num, 0644);

static int __init hello_init(void){
    int i=0;
    printk(KERN_INFO "Hello world\n");
    printk(KERN_INFO "Param:param_int:%d;\n", param_int);
    printk(KERN_INFO "Param:param_str:%s;\n", param_str);
    printk(KERN_INFO "Param:param_array:");
    for(i =0;i<param_array_num;i++){
        printk("%d ", param_array[i]);
    }
    printk(";\n");
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