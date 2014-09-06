#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfSpiDriver.h>

#define _U_SPI_PORT PORTB
#define MOSI 0
#define MISO 1
#define SCK 2
#define SS 3
#define LED 4

byte data[1];

class SoftSpi : public MirfSpiDriver{
  public: 
	virtual uint8_t transfer(uint8_t data);
	virtual void begin();
	virtual void end();
};

uint8_t SoftSpi::transfer(uint8_t data){
  unsigned char bit = 0;
  uint8_t ret=0;
  for(bit = 0; bit < 8; bit++)          // Loop through 8 bits
  {
    if(data & 0x80) digitalWrite(MOSI,HIGH);   // If bit(7) of "data" is high
    else digitalWrite(MOSI,LOW);          // if bit(7) of "data" is low
    digitalWrite(SCK,HIGH);                  // Serial Clock Rising Edge 
    data <<= 1;                             // Shift "data" to the left by one bit
    if(digitalRead(MISO)==HIGH) ret |= 0x01;    // If bit of slave data is high
    else ret &= ~0x01;                  // if bit of slave data is low
    ret <<=1;
    digitalWrite(SCK,LOW);              // Serial Clock Falling Edge
  }

  return ret;                      // Returns shifted data in value
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
  pinMode(LED, OUTPUT);

  // Setup
  Mirf.spi = &MirfSoftwareSpi;
  Mirf.csnPin = 5;
  Mirf.init();
  Mirf.setRADDR((byte *)"servl");
  Mirf.payload = 1;
  Mirf.config();
}

void loop() {
  if(!Mirf.isSending() && Mirf.dataReady()){
    Mirf.getData(data);
    if(data[0] == 1) digitalWrite(LED, HIGH);
    else if(data[0]==2) digitalWrite(LED,LOW);
  }
}
