/* Copyright 2011-2016 Tyler Gilbert;
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

#include "sos/fs/devfs.h"
#include "mcu/pwm.h"

DEVFS_MCU_DRIVER_IOCTL_FUNCTION(pwm, PWM_VERSION, I_MCU_TOTAL + I_PWM_TOTAL, mcu_pwm_setchannel, mcu_pwm_getchannel, mcu_pwm_set, mcu_pwm_get, mcu_pwm_enable, mcu_pwm_disable)
