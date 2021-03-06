#include <SPI.h>
#include <DFRobot_NRF24L01.h>

DFRobot_NRF24L01 MyNrf;

void setup(){
  Serial.begin(9600);
  MyNrf.spi = &MirfHardwareSpi;
#if defined ARDUINO_ESP32_DEV || defined ARDUINO_ARCH_FIREBEETLE8266
  MyNrf.NRF24L01_Gpio_Init(D6,D5);      /*CE = D6, CS = D5*/
#else
  MyNrf.NRF24L01_Gpio_Init(6,5);        /*CE = 6, CS = 5*/
#endif
  while(!MyNrf.NRF24L01_check()){
    Serial.println("RF24L01 is not find !...");
    delay(1000);
  }
  MyNrf.NRF24L01_Init();
  MyNrf.NRF24L01_Set_Mode(MODE_TX);

}

void loop(){
  uint8_t data[32],len = 0;
  while(Serial.available()>0){
    data[len] = char(Serial.read());
    len++;
    if(len == 32)break;     /*Each send can only send up to 32 bytes*/
  }
  if(len>0){
    MyNrf.send(data, len);
    while(MyNrf.isSending()){
      delay(10);
    }
  }else{
    delay(1000);
  }
}


