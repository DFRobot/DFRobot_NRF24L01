DFRobot_NRF24L01 Library for Arduino
---------------------------------------------------------

The library is used to drive the NRF24L01 for data transfer

### Initialize the CE port and the CS port of the NRF24L01
  
    void NRF24L01_Gpio_Init(uint8_t ce,uint8_t cs);

### Check if NRF24L01 is detected

    void NRF24L01_check();

### Initialize NRF24L01	

    void NRF24L01_Init();
   
### Set the communication mode of the NRF24L01
    
    void NRF24L01_Set_Mode(nRf24l01ModeType);
	mode:MODE_TX MODE_RX

### send data	

	void send(uint8_t * value,uint8_t len);
	Note: i should be less than or equal to 32
	
### Test if chip is still sending.

    bool isSending();

### Checks if data is available for reading

    bool dataReady();
	Returns the length of the data
	
 
 * @file DFRobot_NRF24L01_send.ino DFRobot_NRF24L01_recevice.ino
 * @brief DFRobot's NRF24L01 Module
 * @n These two examples are used to implement the NRF24L01 data transfer
 *
 * @n [Get the module here](等上架后添加商品购买链接)
 * @n [Connection and Diagram](等上架后添加wiki链接)
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2017
 * @copyright	GNU Lesser General Public License
 *
 * @author [Wuxiao<xiao.wu@dfrobot.com>]
 * @version  V1.0
 * @date  2017-8-23
 * @https://github.com/DFRobot/DFRobot_NRF24L01