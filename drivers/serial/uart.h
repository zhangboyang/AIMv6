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

#ifndef _DRIVERS_SERIAL_UART_H
#define _DRIVERS_SERIAL_UART_H

#ifdef RAW /* baremetal driver */

void uart_puts(const char *str);
//ssize_t uart_printf(const char *fmt, ...);
//ssize_t uart_vprintf(const char *fmt, va_list ap);

#else /* not RAW, or kernel driver */

#endif /* RAW */


#endif /* _DRIVERS_SERIAL_UART_H */
