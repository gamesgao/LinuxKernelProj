#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
// (struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
// (char *page, char **start, off_t off, int count, int *eof, void *data)
// ssize_t hello_call(char *buf, char **start, off_t off, int count, int *eof, void *data)
ssize_t hello_call(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    char* myString = "Message from a Linux kernel module.\n";
    int ret = 0;
    ret = copy_to_user(buf, myString, count);
    if(!ret) return -1;
    printk(KERN_INFO "This is a test for proc file.\n");
    return count;
}

static int __init hello_init(void){
    struct proc_dir_entry *entry;
    struct file_operations proc_fops= {
        .read= hello_call,
    };
    entry = proc_create("hello", 0444, NULL, &proc_fops);
    if(!entry)
        return -1;
    else{
        printk (KERN_INFO "Proc_read_entry created successfully.\n");
        return 0;
    }
}

static void __exit hello_exit(void){
    remove_proc_entry("hello", NULL);
    printk(KERN_INFO "Goodbye world\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print-param");
MODULE_AUTHOR("Guyao");

module_init(hello_init);
module_exit(hello_exit);

// struct proc_dir_entry *create_proc_read_entry
// (
//     const char *name,
//     mode_t mode,
//     struct proc_dir_entry *base,
//     read_proc_t *read_proc,
//     void *data
// );