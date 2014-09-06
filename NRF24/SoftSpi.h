/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED
#define MOSI 0
#define MISO 1
#define SCK 2
#define SS 3

//pointless defines
#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06
//#define SPI_CLOCK_DIV64 0x07

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR



class SoftSpi {
public:
  inline static byte transfer(byte _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);
};

extern SoftSpi SPI;

byte SoftSpi::transfer(byte data) {
  unsigned char bit = 0;
  for(bit = 0; bit < 8; bit++)          // Loop through 8 bits
  {
    if(data & 0x80) digitalWrite(MOSI,HIGH);   // If bit(7) of "data" is high
    else digitalWrite(MOSI,LOW);          // if bit(7) of "data" is low
    digitalWrite(SCK,HIGH);                  // Serial Clock Rising Edge 
    data <<= 1;                             // Shift "data" to the left by one bit
    if(digitalRead(MISO)==HIGH) data |= 0x01;    // If bit of slave data is high
    else data &= ~0x01;                  // if bit of slave data is low
    digitalWrite(SCK,LOW);              // Serial Clock Falling Edge
  }
  return data;                      // Returns shifted data in value
}

void SoftSpi::attachInterrupt() {
}

void SoftSpi::detachInterrupt() {
}

#endif
