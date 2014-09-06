#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfSpiDriver.h>

#define _U_SPI_PORT PORTB
#define MOSI 0
#define MISO 1
#define SCK 2
#define SS 3

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
  pinMode(MOSI,OUTPUT);
  pinMode(MISO,INPUT);
  pinMode(SCK,OUTPUT);
  pinMode(SS,OUTPUT);

  // Setup
  Mirf.spi = &MirfSoftwareSpi;
  Mirf.csnPin = 5;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  
  // Read and print RF_SETUP
  byte rf_setup = 0;
  Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );

}

void loop() {
//  uint8_t i = 0;
//  for(i=0; i < 240; i++){
//    digitalWrite(SS,LOW);
//    transfer(i);
//    digitalWrite(SS,HIGH);
//    delay(20);
//  }
}
