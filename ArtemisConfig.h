#ifndef ARTEMISCONFIG_H
#define ARTEMISCONFIG_H
/*
   ArtemisConfig.h - Orion WSPR Beacon for pico-Balloon payloads for Arduino

   Copyright (C) 2018-2019 Michael Babineau <mbabineau.ve3wmb@gmail.com>

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
*/
#include <Arduino.h>

#define OFF false
#define ON true

// THIS FILE CONTAINS THE USER MODIFIABLE #DEFINES TO CONFIGURE THE ORION WSPR BEACON
// See Orion Manual for configuration details. 

#define ARTEMIS_FW_VERSION "v0.01a"  // Whole numbers are for released versions. (i.e. 1.0, 2.0 etc.)
// Numbers to the right of the decimal are allocated consecutively, one per GITHUB submission.(i.e. 0.01, 0.02 etc)
// a = alpha b=beta, r=release

#define CAL_CLOCK_NUM            SI5351A_WSPRTX_CLK_NUM
#define CALIBRATION_FREQUENCY_HZx10    1000000000ULL; // 10 MHz, in hundredths of hertz

#endif
