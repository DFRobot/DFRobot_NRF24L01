
/*!
 * @file DFRobot_NRF24L01.cpp
 * @brief DFRobot's NRF24L01 data transmission
 * @n This example is used to implement the NRF24L01 data transfer
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Wuxiao](xiao.wu@dfrobot.com)
 * @version  V1.0
 * @date  2017-8-23
 * @https://github.com/DFRobot/DFRobot_NRF24L01
 */
#include "DFRobot_NRF24L01.h"

DFRobot_NRF24L01::DFRobot_NRF24L01(){
	channel = 1;
	spi = NULL;
}

void DFRobot_NRF24L01::transferSync(uint8_t *dataout,uint8_t *datain,uint8_t len){
	uint8_t i = 0;
	
	for(i = 0;i < len;i++){
		datain[i] = spi->transfer(dataout[i]);
	}		
}

void DFRobot_NRF24L01::transmitSync(uint8_t *dataout,uint8_t len){
	uint8_t i;
	for(i = 0;i < len;i++){
		spi->transfer(dataout[i]);
	}
}

extern bool DFRobot_NRF24L01::dataReady() 
{
    // See note in getData() function - just checking RX_DR isn't good enough
	uint8_t status = getStatus();

    // We can short circuit on RX_DR, but if it's not set, we still need
    // to check the FIFO for any pending packets
    if ( status & (1 << RX_DR) ) return 1;
    return !rxFifoEmpty();
}

extern bool DFRobot_NRF24L01::rxFifoEmpty(){
	uint8_t fifoStatus;

	readRegister(FIFO_STATUS,&fifoStatus,sizeof(fifoStatus));
	return (fifoStatus & (1 << RX_EMPTY));
}



extern uint8_t DFRobot_NRF24L01::getData(uint8_t * data) 
// Reads payload bytes into data array
{
    csnLow();                               // Pull down chip select
	spi->transfer(R_RX_PL_WID);
	uint8_t len = spi->transfer(0xFF);
	
	csnHi(); 
	csnLow();
    spi->transfer( R_RX_PAYLOAD );            // Send cmd to read rx payload
	transferSync(data,data,len); // Read payload
    csnHi();                               // Pull up chip select
    configRegister(STATUS,(1<<RX_DR));   // Reset status register
	return len;
}

void DFRobot_NRF24L01::configRegister(uint8_t reg, uint8_t value)
// Clocks only one byte into the given MiRF register
{
    csnLow();
    spi->transfer(W_REGISTER | (REGISTER_MASK & reg));
    spi->transfer(value);
    csnHi();
}

void DFRobot_NRF24L01::readRegister(uint8_t reg, uint8_t * value, uint8_t len)
// Reads an array of bytes from the given start position in the MiRF registers.
{
    csnLow();
    spi->transfer(R_REGISTER | (REGISTER_MASK & reg));
    transferSync(value,value,len);
    csnHi();
}

void DFRobot_NRF24L01::writeRegister(uint8_t reg, uint8_t * value, uint8_t len) 
// Writes an array of bytes into inte the MiRF registers.
{
    csnLow();
    spi->transfer(W_REGISTER | (REGISTER_MASK & reg));
    transmitSync(value,len);
    csnHi();
}


void DFRobot_NRF24L01::send(uint8_t * value,uint8_t len) 
// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.
{
	if(len >32){
		len = 32;
	}
    uint8_t status;
    status = getStatus();

    while (PTX) {
	    status = getStatus();
	    if((status & ((1 << TX_DS)  | (1 << MAX_RT)))){
		    PTX = 0;
		    break;
	    }
    }                  // Wait until last paket is send
    ceLow();
    powerUpTx();       // Set to transmitter mode , Power up
    csnLow();                    // Pull down chip select
    spi->transfer( FLUSH_TX );     // Write cmd to flush tx fifo
    csnHi();                    // Pull up chip select
    csnLow();                    // Pull down chip select
    spi->transfer( W_TX_PAYLOAD ); // Write cmd to write payload
    transmitSync(value,len);   // Write payload
    csnHi();                    // Pull up chip select
    ceHi();                     // Start transmission
}

/**
 * isSending.
 *
 * Test if chip is still sending.
 * When sending has finished return chip to listening.
 *
 */
bool DFRobot_NRF24L01::isSending(){
	uint8_t status;
	if(PTX){
		status = getStatus();
	    	
		/*
		 *  if sending successful (TX_DS) or max retries exceded (MAX_RT).
		 */

		if((status & ((1 << TX_DS)  | (1 << MAX_RT)))){
			powerUpRx();
			return false; 
		}

		return true;
	}
	return false;
}

uint8_t DFRobot_NRF24L01::getStatus(){
	uint8_t rv;
	readRegister(STATUS,&rv,1);
	return rv;
}

void DFRobot_NRF24L01::powerUpRx(){
	PTX = 0;
	ceLow();
	configRegister(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) );
	ceHi();
	configRegister(STATUS,(1 << TX_DS) | (1 << MAX_RT)); 
}

void DFRobot_NRF24L01::flushRx(){
    csnLow();
    spi->transfer( FLUSH_RX );
    csnHi();
}

void DFRobot_NRF24L01::powerUpTx(){
	PTX = 1;
	configRegister(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) );
}

void DFRobot_NRF24L01::ceHi(){
	digitalWrite(cePin,HIGH);
}

void DFRobot_NRF24L01::ceLow(){
	digitalWrite(cePin,LOW);
}

void DFRobot_NRF24L01::csnHi(){
	digitalWrite(csnPin,HIGH);
}

void DFRobot_NRF24L01::csnLow(){
	digitalWrite(csnPin,LOW);
}

void DFRobot_NRF24L01::powerDown(){
	ceLow();
	configRegister(CONFIG, mirf_CONFIG );
}



void DFRobot_NRF24L01::NRF24L01_Gpio_Init(uint8_t ce,uint8_t cs){
	cePin = ce;
	csnPin = cs;
	pinMode(cePin,OUTPUT);
    pinMode(csnPin,OUTPUT);

    ceLow();
    csnHi();
    // Initialize spi module
    spi->begin();
}

bool DFRobot_NRF24L01::NRF24L01_check(){
	bool ret = false;
	uint8_t i;
	uint8_t buf[5]={ 0XA5, 0XA5, 0XA5, 0XA5, 0XA5 };
	uint8_t read_buf[ 5 ] = { 0 };
	writeRegister( TX_ADDR, buf, 5 );			
	readRegister( TX_ADDR, read_buf, 5 );		 
	for( i = 0; i < 5; i++ )
	{
		if( buf[ i ] != read_buf[ i ] )
		{
			break;
		}	
	} 
	if( 5 == i )
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}

void DFRobot_NRF24L01:: NRF24L01_Set_TxAddr( uint8_t *pAddr, uint8_t len )
{
	len = ( len > 5 ) ? 5 : len;					
    writeRegister( TX_ADDR, pAddr, len );	
}
void DFRobot_NRF24L01:: NRF24L01_Set_RxAddr( uint8_t PipeNum, uint8_t *pAddr, uint8_t Len )
{
    Len = ( Len > 5 ) ? 5 : Len;
    PipeNum = ( PipeNum > 5 ) ? 5 : PipeNum;		

    writeRegister( RX_ADDR_P0 + PipeNum, pAddr, Len );	
}

uint8_t DFRobot_NRF24L01:: NRF24L01_Read_Reg( uint8_t RegAddr )
{
    uint8_t btmp;
	
    csnLow();
	
    spi->transfer( R_REGISTER | RegAddr );	
    btmp = spi->transfer( 0xFF );				
	
    csnHi();			
	
    return btmp;
}

uint8_t DFRobot_NRF24L01:: NRF24L01_Read_Status_Register( void )
{
    uint8_t Status;
	
    csnLow();		
	
    Status = spi->transfer( R_REGISTER + STATUS );	
	
    csnHi();		
	
    return Status;
}
uint8_t DFRobot_NRF24L01:: NRF24L01_Clear_IRQ_Flag( uint8_t IRQ_Source )
{
    uint8_t btmp = 0;

    IRQ_Source &= ( 1 << RX_DR ) | ( 1 << TX_DS ) | ( 1 << MAX_RT );	
    btmp = NRF24L01_Read_Status_Register( );			
			
    csnLow();		
    spi->transfer( W_REGISTER + STATUS );	
    spi->transfer( IRQ_Source | btmp );		
    csnHi( );			
	
    return ( NRF24L01_Read_Status_Register( ));			
}
void DFRobot_NRF24L01::NRF24L01_Init(){
	uint8_t addr[5] = {INIT_ADDR};
	ceHi();
    NRF24L01_Clear_IRQ_Flag( IRQ_ALL );

    configRegister( DYNPD, ( 1 << 0 ) ); 	
    configRegister( FEATRUE, 0x07 );
    //NRF24L01_Read_Reg( DYNPD );
    //NRF24L01_Read_Reg( FEATRUE );
	

    configRegister( CONFIG, /*( 1<<MASK_RX_DR ) |*/		
                                      ( 1 << EN_CRC ) |     
                                      ( 1 << PWR_UP ) );    
    configRegister( EN_AA, ( 1 << ENAA_P0 ) );   		
    configRegister( EN_RXADDR, ( 1 << ERX_P0 ) );		
    configRegister( SETUP_AW, AW_5BYTES );     			
    configRegister( SETUP_RETR, ARD_4000US |
                        ( REPEAT_CNT & 0x0F ) );         	
    configRegister( RF_CH, 60 );             			
    configRegister( RF_SETUP, 0x26 );

    NRF24L01_Set_TxAddr( &addr[0], 5 );                      
    NRF24L01_Set_RxAddr( 0, &addr[0], 5 );                   
}

void DFRobot_NRF24L01::NRF24L01_Set_Mode( nRf24l01ModeType Mode ){
	uint8_t controlreg = 0;
	controlreg = NRF24L01_Read_Reg( CONFIG );
	
    if( Mode == MODE_TX )       
	{
		
		controlreg &= ~( 1<< PRIM_RX );
	}
    else 
	{
		if( Mode == MODE_RX )  
		{ 
			controlreg |= ( 1<< PRIM_RX ); 
		}
	}

    configRegister( CONFIG, controlreg );
}

