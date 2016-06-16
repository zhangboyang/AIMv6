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

#include <syscall.h>
#include <libc/syscalls.h>
#include <percpu.h>
#include <proc.h>
#include <mp.h>

int sys_getpid(int sysno, int *errno)
{
	/* TODO: a quick test to enable printing from user space. */
	kprintf("PID %d CPU %d\n", current_proc->pid, cpuid());
	*errno = 0;
	return current_proc->pid;
}
ADD_SYSCALL(sys_getpid, NRSYS_getpid);
