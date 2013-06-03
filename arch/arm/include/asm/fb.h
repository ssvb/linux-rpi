#ifndef _ASM_FB_H_
#define _ASM_FB_H_

#include <linux/fb.h>
#include <linux/fs.h>
#include <asm/page.h>

extern int enable_cached_fb;

static inline void fb_pgprotect(struct file *file, struct vm_area_struct *vma,
				unsigned long off)
{
	if (enable_cached_fb) {
		printk("vma->vm_page_prot = pgprot_writethrough(vma->vm_page_prot)\n");
		vma->vm_page_prot = pgprot_writethrough(vma->vm_page_prot);
	} else {
		printk("vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot)\n");
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}
}

static inline void *fb_ioremap(unsigned long physaddr, size_t size)
{
	if (enable_cached_fb) {
		printk("ioremap_cached(physaddr, size)\n");
		return ioremap_cached(physaddr, size);
	} else {
		printk("ioremap_wc(physaddr, size)\n");
		return ioremap_wc(physaddr, size);
	}
}

static inline int fb_is_primary_device(struct fb_info *info)
{
	return 0;
}

#endif /* _ASM_FB_H_ */
