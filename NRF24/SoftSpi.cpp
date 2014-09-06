/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#include <Arduino.h>
#include "pins_arduino.h"
#include "SoftSpi.h"

SoftSpi SPI;

void SoftSpi::begin() {

  // Set SS to high so a connected chip will be "deselected" by default
  digitalWrite(SS, HIGH);

  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).
  pinMode(SS, OUTPUT);

  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // By doing this AFTER enabling SPI, we avoid accidentally
  // clocking in a single bit since the lines go directly
  // from "input" to SPI control.  
  // http://code.google.com/p/arduino/issues/detail?id=888
  digitalWrite(SCK, LOW);
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
}


void SoftSpi::end() {
}

void SoftSpi::setBitOrder(uint8_t bitOrder){
}

void SoftSpi::setDataMode(uint8_t mode){
}

void SoftSpi::setClockDivider(uint8_t rate){
}