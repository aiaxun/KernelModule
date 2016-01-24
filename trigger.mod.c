#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x1e94b2a0, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xea4f61d9, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xf9801325, __VMLINUX_SYMBOL_STR(set_pages_x) },
	{ 0xdfad15a3, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x7378123e, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe007de41, __VMLINUX_SYMBOL_STR(kallsyms_lookup_name) },
	{ 0x28cb2bb6, __VMLINUX_SYMBOL_STR(find_vma) },
	{ 0xd75c79df, __VMLINUX_SYMBOL_STR(smp_call_function) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0xa9aab72c, __VMLINUX_SYMBOL_STR(pv_cpu_ops) },
	{ 0x4c58599c, __VMLINUX_SYMBOL_STR(set_pages_nx) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C0DC027071F04E2A0A1E396");
