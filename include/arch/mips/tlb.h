/* Copyright (C) 2016 Gan Quan <coin2028@hotmail.com>
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

#ifndef _ASM_MM_TLBOPS_H
#define _ASM_MM_TLBOPS_H

#include <addrspace.h>
#include <mmu.h>
#include <sys/types.h>
#include <mipsregs.h>

#define tlbp()		asm volatile ("tlbp")
#define tlbr()		asm volatile ("tlbr")
#define tlbwr()		asm volatile ("tlbwr")
#define tlbwi()		asm volatile ("tlbwi")

/*
 * IMPORTANT NOTE:
 * MIPS TLB doesn't allow duplicate virtual pages, so one should always
 * clean TLB entries by filling ENTRYHI with this macro.
 *
 * Side Note:
 * Loongson 3A is fine with such situation but results in undefined behavior.
 * Other MIPS CPUs may shutdown TLB, or, in the extreme, HCF(?).
 */
#define ENTRYHI_DUMMY(idx) ((idx) << (PAGE_SHIFT + 1))

void tlb_flush(void);
void tlb_remove(addr_t vaddr);

#if __mips_isa_rev == 1
extern int get_tlb_entries(void);	/* machine specific */
#else	/* Rev. > 2 */
static inline int get_tlb_entries(void)
{
	uint32_t config1 = read_c0_config1();
	return ((config1 >> 25) & 0x3f) + 1;
}
#endif

#endif

