/*
  USB MidiKliK 4X4 - USB MIDI 4 IN X 4 OUT firmware
  Based on the MIDITECH / MIDIPLUS 4X4 harware.
  Copyright (C) 2017/2018 by The KikGen labs.

  MAIN INCLUDE

  ------------------------   CAUTION  ----------------------------------
  THIS NOT A COPY OR A HACK OF ANY EXISTING MIDITECH/MIDIPLUS FIRMWARE.
  THAT FIRMWARE WAS ENTIRELY CREATED FROM A WHITE PAGE, WITHOUT
  DISASSEMBLING ANY SOFTWARE FROM MIDITECH/MIDIPLUS.

  UPLOADING THIS FIRMWARE TO YOUR MIDIPLUS/MIDITECH 4X4 USB MIDI
  INTERFACE  WILL PROBABLY CANCEL YOUR WARRANTY.

  IT WILL NOT BE POSSIBLE ANYMORE TO UPGRADE THE MODIFIED INTERFACE
  WITH THE MIDITECH/MIDIPLUS TOOLS AND PROCEDURES. NO ROLLBACK.

  THE AUTHOR DISCLAIM ANY DAMAGES RESULTING OF MODIFYING YOUR INTERFACE.
  YOU DO IT AT YOUR OWN RISKS.
  ---------------------------------------------------------------------

  This file is part of the USBMIDIKLIK-4x4 distribution
  https://github.com/TheKikGen/USBMidiKliK4x4
  Copyright (c) 2018 TheKikGen Labs team.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, version 3.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _USBMIDIKLIK4X4_H_
#define _USBMIDIKLIK4X4_H_
#pragma once



// Timer for attachCompare1Interrupt
#define TIMER2_RATE_MICROS 1000

// Sysex used to set some parameters of the interface.
#define SYSEX_INTERNAL_HEADER 0xF0,0x77,0x77,0x78,
#define SYSEX_INTERNAL_ACK 0x7F
#define SYSEX_INTERNAL_BUFF_SIZE 32

// LED light duration in milliseconds
#define LED_PULSE_MILLIS  5

// Macro to flash LEDS IN
#ifdef LEDS_MIDI
  #define FLASH_LED_IN(thisLed) flashLED_IN[thisLed]->start()
  #define FLASH_LED_OUT(thisLed) flashLED_OUT[thisLed]->start()
#else
  #define FLASH_LED_IN(thisLed) flashLED_CONNECT->start()
  #define FLASH_LED_OUT(thisLed) flashLED_CONNECT->start()
#endif


// MIDI Routing rules

#define FROM_SERIAL 1
#define FROM_USB    2

#define SERIAL_RULE 3
#define USBCABLE_RULE 4
#define INTELLITHRU_RULE 5

#define ROUTING_RESET_ALL 0
#define ROUTING_RESET_MIDIUSB 1
#define ROUTING_RESET_INTELLITHRU 2
#define ROUTING_INTELLITHRU_OFF 3

// BUS MODE (I2C)

#define BUS_MODE_MAX_NB_DEVICE 4 // DO NOT CHANGE

#define BUS_MODE_SLAVE_DEVICE_BASE_ADDR 4
#define BUS_MODE_SLAVE_DEVICE_LAST_ADDR BUS_MODE_SLAVE_DEVICE_BASE_ADDR + BUS_MODE_MAX_NB_DEVICE -1
#define BUS_MODE_DISABLED 0
#define BUS_MODE_ENABLED 1
#define BUS_MODE_MASTERID 0
#define BUS_MODE_FREQ 100000
#define BUS_MODE_SERIAL_INTERFACE_MAX BUS_MODE_MAX_NB_DEVICE * SERIAL_INTERFACE_MAX

// Macro to compute the max serial port in bus mode or not.
#define SERIAL_INTERFACE_COUNT (EEPROM_Params.I2C_BusModeState == BUS_MODE_ENABLED ? BUS_MODE_SERIAL_INTERFACE_MAX:SERIAL_INTERFACE_MAX)

// Default number of 15 secs periods to start after USB midi inactivity
// Can be changed by SYSEX
#define DEFAULT_INTELLIGENT_MIDI_THRU_DELAY_PERIOD 2

typedef struct {
      uint8_t  filterMsk;
      uint16_t cableInTargetsMsk;
      uint16_t jackOutTargetsMsk;
} midiRoutingRule_t;

typedef struct {
      uint8_t  filterMsk;
      uint16_t jackOutTargetsMsk;
} midiRoutingRuleJack_t;

// Use this structure to send and receive packet to/from USB
typedef union  {
    uint32_t i;
    uint8_t  packet[4];
} midiPacket_t;

// Functions prototypes
void Timer2Handler(void);
static void SerialSendMidiMsg(uint8_t const *, uint8_t);
static void SerialSendMidiPacket(const midiPacket_t *, uint8_t);
static void RouteMidiMsg( uint8_t, midiXparser* ) ;
static void RouteSysExMidiMsg( uint8_t , midiXparser*  ) ;
static void ParseSysExInternal(const midiPacket_t *) ;
static void RoutePacketToTarget(uint8_t, const midiPacket_t *) ;
static void ProcessSysExInternal() ;
void EEPROM_Check(bool);
void EEPROM_ParamsLoad();
void EEPROM_ParamsSave();

static uint8_t GetInt8FromHexChar(char);
static uint16_t GetInt16FromHex4Char(char *);
static uint16_t GetInt16FromHex4Bin(char * );
static uint16_t AsknNumber(uint8_t) ;
static char AskDigit();
static char AskChar();
static uint8_t AsknHexChar(char *, uint8_t ,char,char);
static void ShowGlobalSettings();
void ShowConfigMenu();

#endif
