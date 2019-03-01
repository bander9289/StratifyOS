/* Copyright 2011-2018 Tyler Gilbert; 
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */


#include "config.h"
#include <errno.h>
#include "device/sys.h"
#include "mcu/core.h"
#include "device/sys.h"
#include "mcu/debug.h"
#include "scheduler/scheduler_local.h"
#include "signal/sig_local.h"
#include "device/sys.h"
#include "symbols.h"


int sys_23_open(const devfs_handle_t * handle){
    return sys_open(handle);
}

int sys_23_ioctl(const devfs_handle_t * handle, int request, void * ctl){
	sys_23_info_t * sys = ctl;

	switch(request){
	case I_SYS_GETINFO: //this will be the wrong version
		break;
	case I_SYS_23_GETINFO:
		memset(sys, 0, sizeof(sys_23_info_t));
		strncpy(sys->version, SOS_SYS_VERSION, 7);
		strncpy(sys->sys_version, sos_board_config.sys_version, 7);
		strncpy(sys->arch, ARCH, 7);
		sys->security = 0;
		sys->signature = symbols_table[0];
		sys->cpu_freq = mcu_core_getclock();
		sys->sys_mem_size = sos_board_config.sys_memory_size;
		sys->o_flags = sos_board_config.o_sys_flags;
		strncpy(sys->stdin_name, sos_board_config.stdin_dev, NAME_MAX-1);
		strncpy(sys->stdout_name, sos_board_config.stdout_dev, NAME_MAX-1);
		strncpy(sys->name, sos_board_config.sys_name, NAME_MAX-1);
		mcu_core_getserialno(&(sys->serial));
		return 0;
	default:
        return sys_ioctl(handle, request, ctl);
	}
	errno = EINVAL;
	return -1;
}

int sys_23_read(const devfs_handle_t * handle, devfs_async_t * rop){
    return sys_read(handle, rop);
}

int sys_23_write(const devfs_handle_t * handle, devfs_async_t * wop){
    return sys_write(handle, wop);
}

int sys_23_close(const devfs_handle_t * handle){
    return sys_close(handle);
}
