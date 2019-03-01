/* Copyright 2019 Cobb Tuning Products LLC
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

#ifndef DEV_CAN_ISOTP_H_
#define DEV_CAN_ISOTP_H_

#include "sos/dev/can_isotp.h"
#include "mcu/can.h"
#include "fifo.h"


/*! \details This stores the data for the state.
 *
 */
struct isotp_link;
typedef struct {
  struct isotp_link *links_head;
} can_isotp_state_t;



/*! \details This is used for the configuration of the device.
 *
 */
//typedef struct {
//  can_reset_attr_t can;
//} can_isotp_config_t;

#ifdef __cplusplus
extern "C" {
#endif

int can_isotp_open(const devfs_handle_t * handle);
int can_isotp_ioctl(const devfs_handle_t * handle, int request, void * ctl);
int can_isotp_read(const devfs_handle_t * handle, devfs_async_t * async);
int can_isotp_write(const devfs_handle_t * handle, devfs_async_t * async);
int can_isotp_close(const devfs_handle_t * handle);

#define CAN_ISOTP_DECLARE_CONFIG_STATE(can_isotp_name,\
    can_reset_attr_baudrate, can_reset_attr_loopback ) \
    can_isotp_state_t can_isotp_name##_state MCU_SYS_MEM; \
    const can_reset_attr_t can_isotp_name##_config = { \
       .baudRate = can_reset_attr_baudrate, \
       .bLoopBack = can_reset_attr_loopback, \
    }


#ifdef __cplusplus
}
#endif


#endif /* DEV_CAN_ISOTP_H_ */

