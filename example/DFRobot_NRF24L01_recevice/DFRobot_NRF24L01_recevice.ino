/*!
 * @file DFRobot_NRF24L01.cpp
 * @brief DFRobot's NRF24L01 data transmission
 * @n This example is used to implement NRF24L01 to receive data
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2017-8-23
 * @https://github.com/DFRobot/DFRobot_NRF24L01
 */
#include <SPI.h>
#include <DFRobot_NRF24L01.h>

DFRobot_NRF24L01 MyNrf;

void setup(){
  Serial.begin(9600);
  MyNrf.spi = &MirfHardwareSpi;
#if defined ARDUINO_ESP32_DEV || defined ARDUINO_ARCH_FIREBEETLE8266
  MyNrf.NRF24L01_Gpio_Init(D6,D5);
#else
  MyNrf.NRF24L01_Gpio_Init(6,5);
#endif
  while(!MyNrf.NRF24L01_check()){
    Serial.println("RF24L01 is not find !...");
    delay(1000);
  }
  MyNrf.NRF24L01_Init();
  MyNrf.NRF24L01_Set_Mode(MODE_RX);
}

void loop(){
  uint8_t len = 0;
  uint8_t data[32];
    if(!MyNrf.isSending() && MyNrf.dataReady()){ 
        len = MyNrf.getData(data);
        int i;
        String Temp;
        for (i = 0; i < len; i++) 
        {
            Temp += char(data[i]);
        }
            Serial.print(Temp);
        }
    
}


