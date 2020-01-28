/*
 * Artemis.ino - Simple calibration routine for the Si5351
 * based on the Si5351 Calibration example in the Etherkit Si5351 Library.
 * 
 * The main differences are that this sketch uses either SoftWire.h or Wire.h to
 * implement communication with the Si5351 via software I2C.
 * Also serial communication is via hardware serial or software serial using NeoSWSerial at 9600 baud.
 * This code reuses the same BoardConfiguration files as Orion to allow description of the board configuration.  
 * * The Etherkit Si5351 Library has been replaced with OrionSi5351 developed for the Aries
 * project. 
 * 
 * Copyright 2020 Michael Babineau, VE3WMB <mbabineau.ve3wmb@gmail.com>
 *                          
 * Copyright (original code) 2015 - 2018 Paul Warren <pwarren@pwarren.id.au>
 *                          Jason Milldrum <milldrum@gmail.com>
 *
 * Uses code from https://github.com/darksidelemm/open_radio_miniconf_2015
 * and the old version of the calibration sketch
 *
 * This sketch  is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License.
 * If not, see <http://www.gnu.org/licenses/>.
*/
#include "ArtemisSi5351.h"
#include "OrionBoardConfig.h"
#include "ArtemisConfig.h"

#if defined (DEBUG_USES_SW_SERIAL)
#include <NeoSWSerial.h>
#endif

#if defined (NEOSWSERIAL_EXTERNAL_PCINT)
ISR (PCINT0_vect)
{
  // handle pin change interrupt for D8 to D13 here.
  // Note SOFT_SERIAL_TX_PIN (MOSI) = 11 and SOFT_SERIAL_RX_PIN =  = 12  (MISO - PB4/PCINT4)for U3S Clones
  //
  NeoSWSerial::rxISR(PINB);
}  // end of PCINT0_vect

ISR (PCINT2_vect)
{
  NeoSWSerial::rxISR(PIND);
}  // end of PCINT2_vect
#endif

int32_t old_cal = 0;
int32_t cal_factor = 0; 

uint64_t rx_freq;
uint64_t target_freq = 1000000000ULL; // 10 MHz, in hundredths of hertz

#if defined (DEBUG_USES_SW_SERIAL)
NeoSWSerial debugSerial(SOFT_SERIAL_RX_PIN, SOFT_SERIAL_TX_PIN);  // RX, TX
#else
#define debugSerial Serial
#endif

void print_board_and_version() {
  debugSerial.print(F("Aries firmware version: "));
  debugSerial.print(ARTEMIS_FW_VERSION);
  debugSerial.println(BOARDNAME);
}

void setup()
{
  // Start serial and initialize the Si5351
  
  debugSerial.begin(9600);

  // The crystal load value needs to match in order to have an accurate calibration
  si5351bx_init();

  // Start on target frequency
  si5351bx_setfreq(CAL_CLOCK_NUM, target_freq, true);
  debugSerial.println(F("Initialising Artemis Si5351, you shouldn't see many of these!"));
  print_board_and_version();
  delay(500);
}



void loop()
{
  debugSerial.println();
  debugSerial.println(F("Adjust until your frequency counter reads as close to 10 MHz as possible."));
  debugSerial.println(F("Press 'q' when complete."));
  vfo_interface();

}

static void flush_input(void)
{
  while (debugSerial.available() > 0)
  debugSerial.read();
}

static void vfo_interface(void)
{
  rx_freq = target_freq;
  cal_factor = old_cal;
  debugSerial.println(F("   Up:   r   t  y  u  i   o  p"));
  debugSerial.println(F(" Down:   f   g  h  j  k   l  ;"));
  debugSerial.println(F("   Hz: 0.01 0.1 1 10 100 1K 10k"));
  while (1)
  {
  if (debugSerial.available() > 0)
  {
    char c = debugSerial.read();
    switch (c)
    {
      case 'q':
        flush_input();
        debugSerial.println();
        debugSerial.print(F("Calibration factor is "));
        debugSerial.println(cal_factor);
        debugSerial.println(F("Setting calibration factor, use this value for SI5351A_CLK_FREQ_CORRECTION in OrionBoardConfig.h."));
        si5351bx_set_correction(cal_factor);
        debugSerial.println(F("Resetting target frequency"));
        si5351bx_setfreq(CAL_CLOCK_NUM, target_freq, true);
        old_cal = cal_factor;
        return;
      case 'r': rx_freq += 1; break;
      case 'f': rx_freq -= 1; break;
      case 't': rx_freq += 10; break;
      case 'g': rx_freq -= 10; break;
      case 'y': rx_freq += 100; break;
      case 'h': rx_freq -= 100; break;
      case 'u': rx_freq += 1000; break;
      case 'j': rx_freq -= 1000; break;
      case 'i': rx_freq += 10000; break;
      case 'k': rx_freq -= 10000; break;
      case 'o': rx_freq += 100000; break;
      case 'l': rx_freq -= 100000; break;
      case 'p': rx_freq += 1000000; break;
      case ';': rx_freq -= 1000000; break;
      default:
        // Do nothing
      continue;
    }

    cal_factor = (int32_t)(target_freq - rx_freq) + old_cal;
    si5351bx_set_correction(cal_factor);
    si5351bx_setfreq(CAL_CLOCK_NUM, target_freq, true);
    debugSerial.print(F("Current difference:"));
    debugSerial.println(cal_factor);
    }
  }
}
