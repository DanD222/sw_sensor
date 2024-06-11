/***********************************************************************//**
 * @file		NMEA_listener.h
 * @brief		NMEA listener for processing incoming NMEA Sentences
 * @author		Maximilian Betz
 * @copyright 		Copyright 2024. All rights reserved.
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
#ifndef NMEA_LISTENER_H_
#define NMEA_LISTENER_H_

#include "FreeRTOS_wrapper.h"
#include "candriver.h"

extern Queue <CANpacket> MC_et_al_queue;

#endif /* NMEA_LISTENER_H_ */
