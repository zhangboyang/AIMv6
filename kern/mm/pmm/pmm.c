/* Copyright (C) 2016 David Gao <davidgao1001@gmail.com>
 *
 * This file is part of AIMv6.
 *
 * AIMv6 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AIMv6 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <sys/types.h>
#include <sys/param.h>

#include <mm.h>
#include <pmm.h>
#include <aim/sync.h>

#include <libc/string.h>

#include <mp.h>

/* dummy implementations */
static int __alloc(struct pages *pages) { return EOF; }
static void __free(struct pages *pages) {}
static addr_t __get_free(void) { return 0; }

static struct page_allocator __allocator = {
	.alloc		= __alloc,
	.free		= __free,
	.get_free	= __get_free
};

static lock_t __pmm_lock = EMPTY_LOCK(__pmm_lock);

void set_page_allocator(struct page_allocator *allocator)
{
	memcpy(&__allocator, allocator, sizeof(*allocator));
}

int alloc_pages(struct pages *pages)
{
	unsigned long flags;
	int ret;

	if (pages == NULL)
		return EOF;
	spin_lock_irq_save(&__pmm_lock, flags);
	kprintf("ALLOC: #%d alloc_pages request %u bytes\n", cpuid(), (unsigned long)pages->size);
	ret = __allocator.alloc(pages);
	kprintf("ALLOC: #%d alloc_pages return %p (%u bytes)\n", cpuid(), (unsigned long)pages->paddr, (unsigned long)pages->size);
	spin_unlock_irq_restore(&__pmm_lock, flags);
	return ret;
}

void free_pages(struct pages *pages)
{
	unsigned long paddr = pages->paddr, size = pages->size;
	unsigned long flags;

	spin_lock_irq_save(&__pmm_lock, flags);
	kprintf("ALLOC: #%d free_pages request %p (%u bytes)\n", cpuid(), paddr, size);
	if (!(pages->flags & GFP_UNSAFE))
		memset(pa2kva(pages->paddr), JUNKBYTE, pages->size);
	__allocator.free(pages);
	kprintf("ALLOC: #%d free_pages freed %p (%u bytes)\n", cpuid(), paddr, size);
	spin_unlock_irq_restore(&__pmm_lock, flags);
}

addr_t get_free_memory(void)
{
	return __allocator.get_free();
}

