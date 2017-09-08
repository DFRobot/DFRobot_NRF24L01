#include "MirfHardwareSpiDriver.h"
#include "stdio.h"

uint8_t MirfHardwareSpiDriver::transfer(uint8_t data)
{
    uint8_t ret;
#if defined ARDUINO_ESP32_DEV
    SPI.beginTransaction(SPISettings(10000000, SPI_MSBFIRST, SPI_MODE0));
#else
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
#endif
    ret = SPI.transfer(data);
    SPI.endTransaction();
    return ret;
}

void MirfHardwareSpiDriver::begin()
{
    SPI.begin();
}

void MirfHardwareSpiDriver::end()
{
}

MirfHardwareSpiDriver MirfHardwareSpi;
