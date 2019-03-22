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

/*! \addtogroup CAN_DEV CAN
 *
 * @{
 *
 * \ingroup DEV
 *
 * \details The CAN module provides an API for accessing an MCU's CAN hardware peripherals.
 * Implemented by Cobb Tuning Products LLC
 *
 *
 */

/*! \file
 * \brief CAN Bus Header File
 */

#ifndef MCU_CAN_H_
#define MCU_CAN_H_

#include "sos/dev/can.h"

#include "sos/fs/devfs.h"

#ifdef __cplusplus
extern "C" {
#endif

int mcu_can_open(const devfs_handle_t * handle) MCU_ROOT_CODE;
int mcu_can_read(const devfs_handle_t * handle, devfs_async_t * rop) MCU_ROOT_CODE;
int mcu_can_write(const devfs_handle_t * handle, devfs_async_t * wop) MCU_ROOT_CODE;
int mcu_can_ioctl(const devfs_handle_t * handle, int request, void * ctl) MCU_ROOT_CODE;
int mcu_can_close(const devfs_handle_t * handle) MCU_ROOT_CODE;

int mcu_can_addfilter(const devfs_handle_t * handle, void * ctl);
int mcu_can_removefilter(const devfs_handle_t * handle, void * ctl);

int mcu_can_getinfo(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;
int mcu_can_setaction(const devfs_handle_t * handle, void * ctl) MCU_ROOT_CODE;

// !! optimized routines with fewer safety checks !!
int mcu_can_getframe(const devfs_handle_t * handle, int channel, uint8_t *frame);
int mcu_can_putframe(const devfs_handle_t * handle, const uint32_t tx_id, const uint8_t *frame, uint8_t size);
int mcu_can_enable_interrupts(const devfs_handle_t * handle);
int mcu_can_disable_interrupts(const devfs_handle_t * handle);

#define CAN_RAW_DECLARE_CONFIG_STATE(can_raw_name,\
    can_reset_attr_baudrate, can_reset_attr_loopback ) \
    const can_reset_attr_t can_raw_name##_config = { \
       .baudRate = can_reset_attr_baudrate, \
       .bLoopBack = can_reset_attr_loopback, \
    }

#ifdef __cplusplus
}
#endif

#endif /* MCU_CAN_H_ */

/*! @} */


