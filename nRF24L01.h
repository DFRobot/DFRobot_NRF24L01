/* Memory Map */
#ifndef _NRF24L01_
#define _NRF24L01_
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17

/* Bit Mnemonics */
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      1
#define LNA_HCURR   0
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

#define R_RX_PL_WID	  0x60
#define DYNPD         0x1C
#define FEATRUE       0x1D

#define FIXED_PACKET_LEN    32		//包长度
#define REPEAT_CNT          15		//重复次数
#define INIT_ADDR           0x34,0x43,0x10,0x10,0x02
#define IRQ_ALL             ( (1<<RX_DR) | (1<<TX_DS) | (1<<MAX_RT) )
#define MAX_TX              0x10	//达到最大发送次数中断
#define TX_OK               0x20	//TX发送完成中断
#define RX_OK               0x40	//接收到数据中断
#define AW_RERSERVED        0x0 
#define AW_3BYTES           0x1
#define AW_4BYTES           0x2
#define AW_5BYTES           0x3

#define ARD_250US       (0x00<<4)
#define ARD_500US       (0x01<<4)
#define ARD_750US       (0x02<<4)
#define ARD_1000US      (0x03<<4)
#define ARD_2000US      (0x07<<4)
#define ARD_4000US      (0x0F<<4)
#define ARC_DISABLE     0x00
#define ARC_15          0x0F

#define PWR_18DB  		(0x00<<1)
#define PWR_12DB  		(0x01<<1)
#define PWR_6DB   		(0x02<<1)
#define PWR_0DB   		(0x03<<1)

typedef enum ModeType
{
    MODE_TX = 0,
    MODE_RX
}nRf24l01ModeType;

typedef enum SpeedType
{
    SPEED_250K = 0,
    SPEED_1M,
    SPEED_2M
}nRf24l01SpeedType;

typedef enum PowerType
{
    POWER_F18DBM = 0,
    POWER_F12DBM,
    POWER_F6DBM,
    POWER_F0DBM
}nRf24l01PowerType;

#endif