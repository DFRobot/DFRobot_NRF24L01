# NRF24L01
Provides an Arduino library that uses the SPI to configure the NRF24L01 to implement data transfer.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)

* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary

Use NRF24L01 to achieve the specified data transmission, or point to point transmission

## Installation

To use this library to download a zip file, unzip it into the Arduino libraries directory. Or use the Arduino IDE to add a ZIP library

## Methods

```C++

#include <SPI.h>
#include <DFRobot_NRF24L01.h>

DFRobot_NRF24L01 MyNrf;

//Initialize the CE port and the CS port of the NRF24L01
void NRF24L01_Gpio_Init(uint8_t ce,uint8_t cs);

//Returns true if NRF24L01 is detected, false otherwise.
bool NRF24L01_check(void);

//Initialize NRF24L01
void NRF24L01_Init(void);

//Set the communication mode of the NRF24L01.(Mode: MODE_TX || MODE_RX)
void NRF24L01_Set_Mode(nRf24l01ModeType Mode);

//Set the communication speed.(Speed: SPEED_250K || SPEED_1M || SPEED_2M)
void NRF24L01_Set_Speed(nRf24l01SpeedType Speed);

//Set the power(Power: POWER_F18DBM || POWER_F12DBM || POWER_F6DBM || POWER_F0DBM)
void NRF24L01_Set_Power(nRf24l01PowerType Power);

//Get the NRF24L01 communication mode, return mode (mode: MODE_TX || MODE_RX)
nRf24l01ModeType NRF24L01_Get_Mode(void);

//Set the send address (note that the address length should not exceed 5)
void NRF24L01_Set_TxAddr(uint8_t *addr,uint8_t len);

//Set the receiving address (note that the address length should not exceed 5)
void NRF24L01_Set_RxAddr(uint8_t *addr,uint8_t len);

//send data(Note: len should be less than or equal to 32)
void send(uint8_t * value,uint8_t len);

//Configure interrupt pins and callback functions
void NRF24L01_Set_IRQ(uint8_t pin, void *callback);

//Test if chip is still sending.
bool isSending();

//Checks if data is available for reading
bool dataReady();

//Gets the received data and returns the length of the data
uint8_t getData(uint8_t *data);

## History

- Sep 8, 2017 - Version 1.0.0 released.

## Credits

Written by DFRobot_Wuxiao, 2017. (Welcome to our [website](https://www.dfrobot.com/))
