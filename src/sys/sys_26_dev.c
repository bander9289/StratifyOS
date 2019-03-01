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
#include "sos/dev/sys.h"
#include "mcu/core.h"
#include "device/sys.h"
#include "mcu/debug.h"
#include "scheduler/scheduler_local.h"

#include "signal/sig_local.h"
#include "device/sys.h"
#include "symbols.h"

extern void mcu_core_hardware_id();

static int read_task(sys_taskattr_t * task);

uint8_t sys_euid MCU_SYS_MEM;

extern u32 _text;

int sys_26_open(const devfs_handle_t * handle){
	return 0;
}

int sys_26_ioctl(const devfs_handle_t * handle, int request, void * ctl){
	sys_id_t * id = ctl;
	sys_26_info_t * info = ctl;
	sys_killattr_t * killattr = ctl;

	int i;
	switch(request){
	case  I_SYS_GETINFO:
		memset(info, 0, sizeof(sys_info_t));
		strncpy(info->kernel_version, SOS_SYS_VERSION, 7);
		strncpy(info->sys_version, sos_board_config.sys_version, 7);
		strncpy(info->arch, ARCH, 15);
		info->security = 0;
		info->signature = symbols_table[0];
		info->cpu_freq = mcu_core_getclock();
		info->sys_mem_size = sos_board_config.sys_memory_size;
		info->o_flags = sos_board_config.o_sys_flags;
		strncpy(info->id, sos_board_config.sys_id, PATH_MAX-1);
		strncpy(info->stdin_name, sos_board_config.stdin_dev, NAME_MAX-1);
		strncpy(info->stdout_name, sos_board_config.stdout_dev, NAME_MAX-1);
		strncpy(info->name, sos_board_config.sys_name, NAME_MAX-1);
		mcu_core_getserialno(&(info->serial));
        info->hardware_id = *((u32*)(&_text + BOOTLOADER_HARDWARE_ID_OFFSET/sizeof(u32)));
        return 0;
	case I_SYS_GETTASK:
		return read_task(ctl);

	case I_SYS_GETID:
		memcpy(id->id, sos_board_config.sys_id, PATH_MAX-1);
		return 0;
	case I_SYS_KILL:
		for(i = 1; i < task_get_total(); i++){
			if( (task_get_pid(i) == killattr->id) &&
					!task_thread_asserted(i)
			){
				signal_root_send(task_get_current(),
						i,
						killattr->si_signo,
						killattr->si_sigcode,
						killattr->si_sigvalue, 1);
				break;
			}
		}
		return 0;
	case I_SYS_PTHREADKILL:
		return signal_root_send(task_get_current(),
				killattr->id,
				killattr->si_signo,
				killattr->si_sigcode,
				killattr->si_sigvalue, 1);
	case I_SYS_GETBOARDCONFIG:
		memcpy(ctl, &sos_board_config, sizeof(sos_board_config));
		return 0;
	default:
		break;
	}
    return SYSFS_SET_RETURN(EINVAL);
}

int sys_26_read(const devfs_handle_t * handle, devfs_async_t * async){
    MCU_UNUSED_ARGUMENT(handle); MCU_UNUSED_ARGUMENT(async);
    return SYSFS_SET_RETURN(ENOTSUP);
}

int sys_26_write(const devfs_handle_t * handle, devfs_async_t * async){
    MCU_UNUSED_ARGUMENT(handle); MCU_UNUSED_ARGUMENT(async);
    return SYSFS_SET_RETURN(ENOTSUP);
}

int sys_26_close(const devfs_handle_t * handle){
	return 0;
}

int read_task(sys_taskattr_t * task){
	int ret;
	if ( task->tid < task_get_total() ){
		if ( task_enabled( task->tid )){
			task->is_enabled = 1;
			task->pid = task_get_pid( task->tid );
			task->timer = task_root_gettime(task->tid);
			task->mem_loc = (uint32_t)sos_sched_table[task->tid].attr.stackaddr;
			task->mem_size = sos_sched_table[task->tid].attr.stacksize;
			task->stack_ptr = (uint32_t)sos_task_table[task->tid].sp;
            task->prio = task_get_priority(task->tid);
			task->prio_ceiling = sos_sched_table[task->tid].attr.schedparam.sched_priority;
			task->is_active = (task_active_asserted(task->tid) != 0) | ((task_stopped_asserted(task->tid != 0)<<1));
			task->is_thread = task_thread_asserted( task->tid );

			strncpy(task->name, ((struct _reent*)sos_task_table[ task->tid ].global_reent)->procmem_base->proc_name, NAME_MAX);

			if ( !task->is_thread && ( sos_task_table[task->tid].reent != NULL) ){
				task->malloc_loc = (uint32_t)&(((struct _reent*)sos_task_table[task->tid].reent)->procmem_base->base)
						+ ((struct _reent*)sos_task_table[task->tid].reent)->procmem_base->size;
			} else {
				task->malloc_loc = 0;
			}


			ret = 1;

		} else {
			task->is_enabled = 0;
			ret = 0;
		}
		errno = 0;
	} else {
		errno = ESRCH;
		ret = -1;
	}

	return ret;
}
