/*!
 * @file DFRobot_NRF24L01.cpp
 * @brief DFRobot's NRF24L01 data transmission
 * @n This example is used to implement NRF24L01 to send data
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
  MyNrf.NRF24L01_Set_Mode(MODE_TX);

}

void loop(){
  uint8_t data[32],i = 0;
  while(Serial.available()>0){
    data[i] = char(Serial.read());
    i++;
    if(i == 32)break;		/*Each send can only send up to 32 bytes*/
  }
  if(i>0){
      MyNrf.send( data, i );
      while(MyNrf.isSending()){
        delay(10);
      }
   }else{
      delay(1000);
   }

}





