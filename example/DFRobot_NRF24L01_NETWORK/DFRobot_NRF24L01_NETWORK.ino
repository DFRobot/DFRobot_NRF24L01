#include <SPI.h>
#include <DFRobot_NRF24L01.h>

DFRobot_NRF24L01 MyNrf;

/*You can open the corresponding macro definition according to the corresponding settings*/
#define MASTER 1
//#define SLAVE1 1
//#define SLAVE2 1
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
  MyNrf.NRF24L01_Set_Mode(MODE_RX);
}

void loop(){
  uint8_t data[32],len = 0;
  if(Serial.available()){
    while(Serial.available()){
#ifdef MASTER
      if(Serial.read() == '1'){
        Serial.println("send >>>>> recv1");
        MyNrf.NRF24L01_Set_TxAddr((uint8_t *)"recv1",5);
      }else{
        Serial.println("send >>>>> recv2");
        MyNrf.NRF24L01_Set_TxAddr((uint8_t *)"recv2",5);
      }
#elif SLAVE1
      Serial.read();
      MyNrf.NRF24L01_Set_TxAddr((uint8_t *)"mast1",5);
#elif SLAVE2
      Serial.read();
      MyNrf.NRF24L01_Set_TxAddr((uint8_t *)"mast1",5);
#endif
    }
    MyNrf.NRF24L01_Set_Mode(MODE_TX);
    
    delay(50);
    MyNrf.send((uint8_t *)"Hello Word!", 11);
    while(MyNrf.isSending())
      delay(10);
    MyNrf.NRF24L01_Set_Mode(MODE_RX);
#ifdef MASTER
    MyNrf.NRF24L01_Set_RxAddr((uint8_t *)"mast1",5);
#elif SLAVE1
    MyNrf.NRF24L01_Set_RxAddr((uint8_t *)"recv1",5);
#elif SLAVE2
    MyNrf.NRF24L01_Set_RxAddr((uint8_t *)"recv2",5);
#endif
    delay(50);
  }
  if(!MyNrf.isSending() && MyNrf.dataReady()){ 
    len = MyNrf.getData(data);
    int i;
    String Temp;
    for (i = 0; i < len; i++) 
    {
      Temp += char(data[i]);
    }
    Serial.println(Temp);
  }
}


