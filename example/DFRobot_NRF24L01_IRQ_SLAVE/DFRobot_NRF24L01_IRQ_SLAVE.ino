#include <SPI.h>
#include <DFRobot_NRF24L01.h>

DFRobot_NRF24L01 MyNrf;

void callback(){
  uint8_t data[32],len = 0;
  if(MyNrf.NRF24L01_Get_Mode() == MODE_RX){
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

void setup(){
  Serial.begin(9600);
  MyNrf.spi = &MirfHardwareSpi;
#if defined ARDUINO_ESP32_DEV || defined ARDUINO_ARCH_FIREBEETLE8266
  MyNrf.NRF24L01_Gpio_Init(D6,D5);      /*CE = D6, CS = D5*/
  MyNrf.NRF24L01_Set_IRQ(D2,callback);  /*Set interrupt io port and callback function*/
#else
  MyNrf.NRF24L01_Gpio_Init(6,5);        /*CE = 6, CS = 5*/
  MyNrf.NRF24L01_Set_IRQ(2,callback);   /*Set interrupt io port and callback function*/
#endif
  while(!MyNrf.NRF24L01_check()){
    Serial.println("RF24L01 is not find !...");
    delay(1000);
  }
  MyNrf.NRF24L01_Init();
  MyNrf.NRF24L01_Set_Speed(SPEED_250K);
  MyNrf.NRF24L01_Set_Power(POWER_F0DBM);
  MyNrf.NRF24L01_Set_Mode(MODE_RX);
  MyNrf.NRF24L01_Set_RxAddr((uint8_t *)"recv1",5);
}

void loop(){
  uint8_t data[32],len = 0;
  if(Serial.available()){
    while(Serial.available())
      Serial.read();
    MyNrf.NRF24L01_Set_TxAddr((uint8_t *)"mast1",5);
    MyNrf.NRF24L01_Set_Mode(MODE_TX);
    delay(50);
    MyNrf.send((uint8_t *)"I'M SLAVE 1!", 11);
    while(MyNrf.isSending())
      delay(10);
    MyNrf.NRF24L01_Set_Mode(MODE_RX);
    MyNrf.NRF24L01_Set_RxAddr((uint8_t *)"recv1",5);
  }
}

