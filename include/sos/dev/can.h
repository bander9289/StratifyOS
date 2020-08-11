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

#ifndef SOS_DEV_CAN_H_
#define SOS_DEV_CAN_H_

#include <stdint.h>

#include "mcu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MCU_PACK {
	u32 o_flags /*! A bitmask for the supported features */;
	u32 o_events /*! Events supported by this driver */;
} can_info_t;

typedef struct MCU_PACK
{
	uint32_t rx_id;
	uint32_t rx_mask;
} can_rxfilter_attr_t;

typedef struct MCU_PACK
{
  uint32_t baudRate;
  bool bLoopBack;
} can_reset_attr_t;

#define CAN_VERSION (0x0001)
#define CAN_IOC_IDENT_CHAR 'c'
#define I_CAN_ADDFILTER _IOCTLW(CAN_IOC_IDENT_CHAR, I_MCU_TOTAL + 0, can_rxfilter_attr_t)
#define I_CAN_REMOVEFILTER _IOCTLW(CAN_IOC_IDENT_CHAR, I_MCU_TOTAL + 1, int)
#define I_CAN_RESET _IOCTLW(CAN_IOC_IDENT_CHAR, I_MCU_TOTAL + 1, can_reset_attr_t)

#ifdef __cplusplus
}
#endif

#endif // SOS_DEV_CAN_H_

