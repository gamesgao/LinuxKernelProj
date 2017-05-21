#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xcd5d4559, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x4e648f00, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xf230eb78, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x8c2faa6d, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x58c7224c, __VMLINUX_SYMBOL_STR(mount_bdev) },
	{ 0x49bc9050, __VMLINUX_SYMBOL_STR(d_add) },
	{ 0x110ee7be, __VMLINUX_SYMBOL_STR(page_symlink_inode_operations) },
	{ 0xf9a02c35, __VMLINUX_SYMBOL_STR(generic_read_dir) },
	{ 0x97651e6c, __VMLINUX_SYMBOL_STR(vmemmap_base) },
	{ 0xbd495227, __VMLINUX_SYMBOL_STR(__bread_gfp) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x3683eb80, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0xded26d94, __VMLINUX_SYMBOL_STR(set_nlink) },
	{ 0xa07a37f0, __VMLINUX_SYMBOL_STR(memchr) },
	{ 0x95a9c476, __VMLINUX_SYMBOL_STR(generic_ro_fops) },
	{ 0x5c7e44ff, __VMLINUX_SYMBOL_STR(unlock_page) },
	{ 0xdbb1647d, __VMLINUX_SYMBOL_STR(inode_nohighmem) },
	{ 0x3d3374b2, __VMLINUX_SYMBOL_STR(__brelse) },
	{ 0x4dd36db4, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0x7cd8d75e, __VMLINUX_SYMBOL_STR(page_offset_base) },
	{ 0xed5341c, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xa916b694, __VMLINUX_SYMBOL_STR(strnlen) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xb440f3ac, __VMLINUX_SYMBOL_STR(unlock_new_inode) },
	{ 0xfaf9bdbf, __VMLINUX_SYMBOL_STR(kill_block_super) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xfafb434d, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa0065e39, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x45c76db9, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x643e0ce5, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xa68cb0b7, __VMLINUX_SYMBOL_STR(sync_filesystem) },
	{ 0xb191d294, __VMLINUX_SYMBOL_STR(sb_set_blocksize) },
	{ 0x1f2c405a, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0x3af46a97, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0xd729fde5, __VMLINUX_SYMBOL_STR(init_special_inode) },
	{ 0xea5f6ec7, __VMLINUX_SYMBOL_STR(iget_locked) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C71F75576209A5ABEEFADA8");
