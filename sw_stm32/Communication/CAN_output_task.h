/***********************************************************************//**
 * @file		CAN_output_task.h
 * @brief		CAN output manager: globals
 * @author		Dr. Klaus Schaefer
 * @copyright 		Copyright 2021 Dr. Klaus Schaefer. All rights reserved.
 * @license 		This project is released under the GNU Public License GPL-3.0

    <Larus Flight Sensor Firmware>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************************/
#ifndef CAN_OUTPUT_TASK_H_
#define CAN_OUTPUT_TASK_H_

#include "FreeRTOS_wrapper.h"

extern RestrictedTask CAN_task;

//!< helper routine to synchronize the CAN output loop
inline void trigger_CAN(void)
{
  CAN_task.notify_give();
}

#endif /* CAN_OUTPUT_TASK_H_ */
