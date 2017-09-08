#ifndef _DRFOBOT_NRF24L01_H_
#define _DRFOBOT_NRF24L01_H_

#include <Arduino.h>

#include "nRF24L01.h"
#include "MirfSpiDriver.h"
#include <MirfHardwareSpiDriver.h>

#define MIRF_ADDR_LEN    5
#define MIRF_CONFIG ((1<<EN_CRC) | (0<<CRCO) )

class DFRobot_NRF24L01 {
    public:
        DFRobot_NRF24L01();

#if defined ARDUINO_ESP32_DEV || defined ARDUINO_ARCH_FIREBEETLE8266
        void NRF24L01_Gpio_Init(uint8_t ce = D6,uint8_t cs = D4);
#else
        void NRF24L01_Gpio_Init(uint8_t ce = 6,uint8_t cs = 4);
#endif
        void send(uint8_t *value,uint8_t len);
        bool dataReady();
        bool isSending();
        bool rxFifoEmpty();
        bool txFifoEmpty();
        uint8_t getData(uint8_t * data);
        uint8_t getStatus();
        void transmitSync(uint8_t *dataout,uint8_t len);
        void transferSync(uint8_t *dataout,uint8_t *datain,uint8_t len);
        void configRegister(uint8_t reg, uint8_t value);
        void readRegister(uint8_t reg, uint8_t * value, uint8_t len);
        void writeRegister(uint8_t reg, uint8_t * value, uint8_t len);
        void powerUpRx();
        void powerUpTx();
        void powerDown();
        void csnHi();
        void csnLow();
        void ceHi();
        void ceLow();
        void flushRx();
        void NRF24L01_Set_IRQ(uint8_t IRQ, void (*callback)(void));
        nRf24l01ModeType NRF24L01_Get_Mode();
        uint8_t NRF24L01_Read_Status_Register( void );
        uint8_t NRF24L01_Clear_IRQ_Flag( uint8_t IRQ_Source );
        uint8_t NRF24L01_Read_Reg( uint8_t RegAddr );
        bool NRF24L01_check();
        void NRF24L01_Init();
        void NRF24L01_Set_Mode(nRf24l01ModeType Mode );
        void NRF24L01_Set_Speed(nRf24l01SpeedType Speed);
        void NRF24L01_Set_Power(nRf24l01PowerType Power);
        void NRF24L01_Set_TxAddr( uint8_t *pAddr, uint8_t len );
        void NRF24L01_Set_RxAddr( uint8_t *pAddr, uint8_t Len );
        void NRF24L01_Set_RxAddr_Channel( uint8_t PipeNum, uint8_t *pAddr, uint8_t Len );
        
        /*
         * In sending mode.
         */

        uint8_t PTX;

        /*
         * CE Pin controls RX / TX, default 8.
         */

        uint8_t cePin;

        /*
         * CSN Pin Chip Select Not, default 7.
         */

        uint8_t csnPin;

        /*
         * Channel 0 - 127 or 0 - 84 in the US.
         */
        uint8_t channel;


        /*
         * Spi interface (must extend spi).
         */

        MirfSpiDriver *spi;
};

#endif /* _MIRF_H_ */
