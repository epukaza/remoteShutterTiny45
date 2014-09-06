#define BUTTON 4

#include <NRF24.h>
#include <SoftSpi.h>

NRF24 nrf24(10,SS);
uint8_t data[1];

void setup() 
{
  pinMode(BUTTON, OUTPUT);
  digitalWrite(BUTTON, LOW);
  if (!nrf24.init())
  digitalWrite(BUTTON, HIGH);
  if (!nrf24.setChannel(20))
  digitalWrite(BUTTON, HIGH);
  if (!nrf24.setThisAddress((uint8_t*)"clie1", 5))
  digitalWrite(BUTTON, HIGH);
  if (!nrf24.setPayloadSize(1))
  digitalWrite(BUTTON, HIGH);
  if (!nrf24.setRF(NRF24::NRF24DataRate2Mbps, NRF24::NRF24TransmitPower0dBm))
  digitalWrite(BUTTON, HIGH);
}

// With printing commented and delay removed, this can achieve about 666 round trips per second
void loop()
{
  // Configure for carrier wave:
  nrf24.spiWriteRegister(NRF24_REG_06_RF_SETUP, NRF24_CONT_WAVE | NRF24_PLL_LOCK | NRF24_PWR_0dBm);
  if (!nrf24.powerUpTx())
  digitalWrite(BUTTON, HIGH);
  nrf24.setTransmitAddress((uint8_t*)"servl",5);
  data[0]=1;
  nrf24.send(data, (uint8_t)1);


  delay(5000);
  if (!nrf24.powerDown())
  digitalWrite(BUTTON, HIGH);
 
  delay(5000);
}
