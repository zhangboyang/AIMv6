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

#include <drivers/io/io-port.h>
#include <drivers/io/io-mem.h>
#include <io.h>
#include <mp.h>
#include <platform.h>

void early_mach_init(void)
{
	/* XXX: maybe unnecessary... */
	portio_bus_connect(&early_portio_bus,
			   &early_memory_bus,
			   LOONGSON3A_PORTIO_BASE);
}

void mach_init(void)
{
	int i;
	/* Enable all IPI bits and clear the IPI bits first */
	for (i = 0; i < nr_cpus(); ++i) {
		write32(LOONGSON3A_COREx_IPI_CLEAR(i), 0xffffffff);
		write32(LOONGSON3A_COREx_IPI_ENABLE(i), 0xffffffff);
	}
}

