#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

int MAXMSG = 10;
int len, temp;
char* msg;
struct proc_dir_entry *entry;
struct proc_dir_entry *my_dir;

ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp)
{
    // cat will read this file repeatly until 0 is returned!
    if (count > temp)
    {
        count = temp;
    }
    temp = temp - count;
    copy_to_user(buf, msg, count);
    if (count == 0)
        temp = len;
    return count;
}

ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
    if(count >= MAXMSG){
        kfree(msg);
        msg = kmalloc((count+1)*sizeof(char),GFP_KERNEL);
    }
    copy_from_user(msg, buf, count);
    // printk(KERN_INFO "In write %ld\n", count);
    len = count;
    temp = len;
    return count;
}

static const struct file_operations proc_fops = {
    .read = read_proc,
    .write = write_proc,
};

static int __init hello_init(void)
{
    my_dir = proc_mkdir("mydir", NULL);
    entry = proc_create("hello", 0777, my_dir, &proc_fops);
    msg = kmalloc(MAXMSG*sizeof(char),GFP_KERNEL);
    if (!entry)
        return -1;
    else
    {
        printk(KERN_INFO "Proc_read_entry created successfully.\n");
        return 0;
    }
}

static void __exit hello_exit(void)
{
    remove_proc_entry("hello", my_dir);
    remove_proc_entry("mydir", NULL);
    kfree(msg);
    printk(KERN_INFO "Proc_read_entry deleted successfully.\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Print-proc");
MODULE_AUTHOR("Guyao");

module_init(hello_init);
module_exit(hello_exit);