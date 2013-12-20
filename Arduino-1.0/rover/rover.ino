/*
 * Copyright (C) 2012 Paul Bovbel, paul@bovbel.com
 * 
 * This file is part of the Mover-Bot robot platform (http://code.google.com/p/mover-bot/)
 * 
 * Mover-Bot is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this source code. If not, see http://www.gnu.org/licenses/
 */

/* ADK Accessory firmware for the Mover-bot project.
 * 
 * Maintains specified motor speed, and transmits battery status to Android phone.
 */

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

//PIN LOCATIONS
#define  PIN_8  8

//USB COMMANDS
#define LED_8 8
#define FLASH_MODE 'flash'

//FREQUENCY
#define UPDATE_FREQ 200


// ADK CONFIG
AndroidAccessory acc("X3R", "Rover", "Remote control rover", "0.1", "http://www.bovbel.com", "0000000012345678");

//Timers
long arduinoTimer = millis();
long usbTimer = millis();


//VALUES
boolean led8;
boolean flash;
boolean blinkValue;

void setup()
{
  // Serial Communication
  Serial.begin(115200);
  
  //Pin Modes
  pinMode(PIN_8, OUTPUT);

  //Power Up ADK
  acc.powerOn();
}

void loop()
{
  byte msg[3];

  if(acc.isConnected() && millis()-usbTimer >= 1000/COMM_FREQ)
  {
    usbTimer = millis();
		
    int len = acc.read(msg, sizeof(msg), 1); // read data into msg variable
    if(len > 0)
    {
      switch (msg[1])
      {
        case LED_8:
          if(led8)
          {
            led8 = false; 
          }
          else
          {
            led8 = true;
          }
  	  break;
        case FLASH_MODE:
          if(flash)
          {
            flash = false; 
          }
          else
          {
            flash = true;
          }
  	  break;
      }
    }
  }

  //Control update, 100 Hz loop
  if (millis()-arduinoTimer >= 1000/COMM_FREQ) 
  {
    arduinoTimer = millis();
  }
}
