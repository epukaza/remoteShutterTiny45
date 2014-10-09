// nrf24_ping_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the NRF24 class. 
// It is designed to work with the example nrf24_ping_client. 
// It also works with ping_client from the Mirf library

#include <NRF24.h>
#define FOCUS 8
#define SHUTTER 9
// Singleton instance of the radio
NRF24 nrf24(2, 10);
// NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// NRF24 nrf24(8, 10);/(/ For Leonardo, need explicit SS pin
void setup() 
{
  if (!nrf24.init());
  // Defaults after init are 2.402 GHz (channel 2)
  // Now be compatible with Mirf ping_client
 if (!nrf24.setChannel(44));
 if (!nrf24.setThisAddress((uint8_t*)"serv1", 5));
 if (!nrf24.setPayloadSize(sizeof(unsigned long)));
 if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm));
 pinMode(FOCUS, OUTPUT);
 pinMode(SHUTTER, OUTPUT);
 digitalWrite(FOCUS, HIGH);
 digitalWrite(SHUTTER, HIGH);

}

void loop()
{
  
  /*
  digitalWrite(FOCUS, HIGH);
  delay(1000);
  digitalWrite(FOCUS, LOW);
  delay(1000);
  digitalWrite(SHUTTER, LOW);
  delay(1000);
  digitalWrite(SHUTTER, HIGH);
  */
//  Serial.println("waiting");
  nrf24.waitAvailable();
  // ping_client sends us an unsigned long containing its timestamp
  unsigned long data;
  uint8_t len = sizeof(data);
/*  if (!nrf24.recv((uint8_t*)&data, &len));
  
  if(data==0){//focus off
    digitalWrite(FOCUS, HIGH);
    //pinMode(FOCUS, INPUT_PULLUP);
  }
  if(data==1){//focus on
    //pinMode(FOCUS, OUTPUT);
    digitalWrite(FOCUS, LOW);
  }
  if(data==2){//take a picture
    //pinMode(SHUTTER, OUTPUT);
    digitalWrite(SHUTTER, LOW);
    delay(1000);
    digitalWrite(SHUTTER, HIGH);
    //pinMode(SHUTTER, INPUT_PULLUP);
  }
  if(data==4){
  }
*/
//   Serial.println(data);
  if (!nrf24.recv((uint8_t*)&data, &len));
  
  if(data==0){//focus off
    digitalWrite(FOCUS, HIGH);
    //pinMode(FOCUS, INPUT_PULLUP);
  }
  if(data==1){//focus on
    //pinMode(FOCUS, OUTPUT);
    digitalWrite(FOCUS, LOW);
  }
  if(data==2){//take a picture
    //pinMode(SHUTTER, OUTPUT);
    digitalWrite(SHUTTER, LOW);
    delay(1000);
    digitalWrite(SHUTTER, HIGH);
    //pinMode(SHUTTER, INPUT_PULLUP);
  }
  if(data==4){
  }
  // Now send the same data back
  // Need to set the address of the detination each time, since auto-ack changes the TX address
  if (!nrf24.setTransmitAddress((uint8_t*)"clie1", 5));
  // Send the same data back   
  if (!nrf24.send((uint8_t*)&data, sizeof(data)));
  if (!nrf24.waitPacketSent());
  
}

