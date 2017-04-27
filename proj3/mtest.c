#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h> 
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

int MAXMSG = 50;
int len = 0, temp;
char *msg;
struct proc_dir_entry *entry;

static void listvma(void)
{
    struct task_struct *proc = current;
    struct mm_struct *mm = proc->mm;
    struct vm_area_struct *vma;
    printk(KERN_INFO "The current process is %s\n", proc->comm);
    printk(KERN_INFO "start addr\tend addr\t permission\n");
    down_read(&mm->mmap_sem);
    for (vma = mm->mmap; vma; vma = vma->vm_next)
    {
        printk(KERN_INFO "0x%lx\t\t0x%lx\t\t", vma->vm_start, vma->vm_end);
        if (vma->vm_flags & VM_READ)
            printk(KERN_CONT "r");
        else
            printk(KERN_CONT "-");
        if (vma->vm_flags & VM_WRITE)
            printk(KERN_CONT "w");
        else
            printk(KERN_CONT "-");
        if (vma->vm_flags & VM_EXEC)
            printk(KERN_CONT "x");
        else
            printk(KERN_CONT "-");
        printk(KERN_CONT "\n");
    }
    up_read(&mm->mmap_sem);
}

static struct page *my_follow_page(struct vm_area_struct *vma, unsigned long addr)
{
    pud_t *pud; //页上级若不存在pgd，则跳到out目录项
    pmd_t *pmd; //页中间目录项
    pgd_t *pgd; //页全局目录项
    pte_t *pte; //页表项
    spinlock_t *ptl;
    struct page *page = NULL; //若不存在pgd，则跳到out = NULL;
    struct mm_struct *mm = vma->vm_mm; //将当前进程的虚拟地址空间赋值给mm
    pgd = pgd_offset(mm, addr);        //offset函数找到pgd即页全局目录
    if (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
    { //若不存在pgd，则跳到out
        goto out;
    }
    pud = pud_offset(pgd, addr); //offset函数找到pud即页上级目录
    if (pud_none(*pud) || unlikely(pud_bad(*pud)))
    { //若不存在pud，则跳到out
        goto out;
    }
    pmd = pmd_offset(pud, addr); //offset函数找到pmd即页中间目录
    if (pmd_none(*pmd) || unlikely(pmd_bad(*pmd)))
    { //若不存在pmd，则跳到out
        goto out;
    }
    pte = pte_offset_map_lock(mm, pmd, addr, &ptl); //通过offset_map找到页表项
    if (!pte)                                       //如果不存在满足条件的页表项，则跳到out
        goto out;
    if (!pte_present(*pte)) //如果该页表不在内存中，跳到unlock
        goto unlock;
    page = pfn_to_page(pte_pfn(*pte)); //找到相应的页框，并找到页框对应的描述符
    if (!page)
        //page 返回为空，跳到unlock
            goto unlock;
    get_page(page); // 为page赋值
unlock:
    pte_unmap_unlock(pte, ptl); 
out:
    return page;
}

static void findpage(unsigned long addr)
{
    struct vm_area_struct *vma;
    struct mm_struct *mm = current->mm;
    unsigned long kernel_addr; //表示物理地址
    struct page *page;
    down_read(&mm->mmap_sem);         //对信号量进行P操作
    vma = find_vma(mm, addr);         //定位到虚拟存储区的某一段
    page = my_follow_page(vma, addr); //找到物理页面
    if (!page)
    {
        printk(KERN_INFO "page not found for 0x%lx\n", addr);
        goto out;
    }
    printk(KERN_INFO "page found for 0x%lx\n", addr);
    kernel_addr = (unsigned long) page_address(page); //将物理页框号赋值给物理地址
    kernel_addr += (addr & ~PAGE_MASK);              //物理地址+页大小得到所求
    printk(KERN_INFO "find 0x%lx to kernel address 0x%lx\n", addr, kernel_addr);
out:
    up_read(&mm->mmap_sem); //对信号量进行V操作
}

static void writeval(unsigned long addr, unsigned long val)
{
    struct vm_area_struct *vma;
    struct mm_struct *mm = current->mm;
    struct page *page;
    unsigned long kernel_addr;
    down_read(&mm->mmap_sem);
    vma = find_vma(mm, addr);
    if (vma && addr >= vma->vm_start && (addr + sizeof(val)) < vma->vm_end)
    {
        if (!(vma->vm_flags & VM_WRITE))
        {
            printk(KERN_INFO "vma is not writeable for 0x%lx\n", addr);
            goto out;
        }
        page = my_follow_page(vma, addr);
        if (!page)
        {
            printk(KERN_INFO "page not found for 0x%lx\n", addr);
            goto out;
        }
        kernel_addr = (unsigned long)page_address(page);
        kernel_addr += (addr & ~PAGE_MASK);
        printk(KERN_INFO "write 0x%lx to address 0x%lx\n", val, kernel_addr);
        *(unsigned long *)kernel_addr = val; //将val的值赋给物理地址
        put_page(page);
    }
    else
    {
        printk("no vma found for %lx\n", addr);
    }
out:
    up_read(&mm->mmap_sem);
}

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
    unsigned long val, val2;
    copy_from_user(msg, buf, count);
    msg[count - 1] = '\0';
    printk(KERN_INFO "write to msg %s\n", msg);
    if (memcmp(msg, "listvma", 7) == 0)
    {
        printk(KERN_INFO "Print the vma list\n");
        listvma();
    }
    else if (memcmp(msg, "findpage", 8) == 0)
    {
        if (sscanf(msg + 8, "%lx", &val) == 1)
        {
            findpage(val);
        }
    }
    else if (memcmp(msg, "writeval", 8) == 0)
    {
        if (sscanf(msg + 8, "%lx %lx", &val, &val2) == 2)
        {
            printk(KERN_INFO "write val\n");
            writeval(val, val2);
        }
    }
    len = count;
    temp = len;
    return count;
}

static const struct file_operations proc_fops = {
    .read = read_proc,
    .write = write_proc,
};

static int __init mtest_init(void)
{

    entry = proc_create("mtest", 0777, NULL, &proc_fops);
    msg = kmalloc(MAXMSG * sizeof(char), GFP_KERNEL);
    len = 0;
    if (!entry)
        return -1;
    else
    {
        printk(KERN_INFO "Proc_read_entry created successfully.\n");
        return 0;
    }
}

static void __exit mtest_exit(void)
{
    remove_proc_entry("mtest", NULL);
    kfree(msg);
    printk(KERN_INFO "Proc_read_entry deleted successfully.\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mtest");
MODULE_AUTHOR("Guyao");

module_init(mtest_init);
module_exit(mtest_exit);