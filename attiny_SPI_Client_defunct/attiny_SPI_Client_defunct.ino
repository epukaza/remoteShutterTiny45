#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfSpiDriver.h>
#include "avr/interrupt.h"

#define _U_SPI_PORT PORTB
#define MOSI 0
#define MISO 1
#define SCK 2
#define SS 3
#define BUTTON 4

int value = HIGH;
int prev = HIGH;
uint8_t send;
byte data[1];


class SoftSpi : public MirfSpiDriver{
  public: 
	virtual uint8_t transfer(uint8_t data);
	virtual void begin();
	virtual void end();
};

uint8_t SoftSpi::transfer(uint8_t data){
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

void SoftSpi::begin(){
}

void SoftSpi::end(){
}


SoftSpi MirfSoftwareSpi;

void setup() {
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(SS, OUTPUT);
  pinMode(BUTTON, OUTPUT);
  
  // Setup
  Mirf.spi = &MirfSoftwareSpi;
  Mirf.csnPin = 5;
  Mirf.init();
  Mirf.payload = 1;
  Mirf.setRADDR((byte *)"clie1");
  Mirf.config();
}

void loop() {
  Mirf.setTADDR((byte *)"serv1");
  data[0] = 1;
  Mirf.send((byte *)data);
  digitalWrite(BUTTON, HIGH);
//  while(Mirf.isSending()){}
//  delay(1000);
  data[0] = 2;
  Mirf.send((byte *)data);
  digitalWrite(BUTTON, LOW);
//  while(Mirf.isSending()){}
//  delay(1000);
  /*
  value = digitalRead(BUTTON);
  if(value != prev){
    Mirf.setTADDR((byte *)"serv1");
    prev = value;
    if(value==HIGH){//button not pressed, LED should be off
      send = 2;
    }
    else if(value == LOW){//button has been pressed
      send = 1;
    }
    Mirf.send(&send);
    while(!Mirf.isSending()){}
  }
  */
}
