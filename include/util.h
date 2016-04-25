/* Copyright (C) 2016 Gan Quan <coin2028@hotmail.com>
 * Copyright (C) 2016 David Gao <davidgao1001@gmail.com>
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

/* Kernel utility functions
 * Put miscellaneous functions and macros here */

#ifndef _UTIL_H
#define _UTIL_H

#include <sys/types.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define widthof(t)	(sizeof(t) * 8)

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof((a)[0]))

#define min2(a, b)	(((a) < (b)) ? (a) : (b))
#define max2(a, b)	(((a) > (b)) ? (a) : (b))

#define DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))

#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)


/* Note: ALIGNxxx are suited for powers of 2 only, while
 * ROUNDxxx can deal with any integer value. */
#define __ALIGN_MASK(x, a)	((typeof(x))((a) - 1))
#define IS_ALIGNED(x, a)	(((x) & __ALIGN_MASK(x, a)) == 0)
#define ALIGN_ABOVE(x, a)	((((x) - 1) | __ALIGN_MASK(x, a)) + 1)
#define ALIGN_BELOW(x, a)	((x) & ~__ALIGN_MASK(x, a))
#define PTR_ALIGN_ABOVE(p, a)	\
	((typeof(p))ALIGN_ABOVE((unsigned long)(p), (a)))
#define PTR_ALIGN_BELOW(p, a)	\
	((typeof(p))ALIGN_BELOW((unsigned long)(p), (a)))

#define ROUNDUP(x, d)		(DIV_ROUND_UP(x, d) * (d))
#define ROUNDDOWN(x, d)		((x) - ((x) % (d)))
#define ROUND_CLOSEST(x, d)	(((x) + ((d) / 2)) / (d))

#endif