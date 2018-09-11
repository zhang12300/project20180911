/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年3月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】137.500MHz
【pllclock】275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
uint8 imgbuff[CAMERA_SIZE];                       //定义存储接收图像的数组
uint8 imgbuff_process[CAMERA_SIZE];               //定义处理图像用的数组
uint8 img_edg[CAMERA_SIZE*2];                           //
uint8 img[CAMERA_W*CAMERA_H];                           //
uint8 LMR[3][CAMERA_H];
uint8 new_img=0;

uint8_t Threshold;                  //OSTU大津法计算的图像阈值
volatile u8  Line_Cont=0;          //行计数
volatile u8  Field_Over_Flag=0;    //场标识
uint16_t cc;
int OFFSET0=0;      //最远处，赛道中心值综合偏移量
int OFFSET1=0;      //第二格
int OFFSET2=0;      //最近，第三格
int TXV=0;          //梯形的左高度，右高度

reg_s camera_reg[] =
{
    //寄存器，寄存器值次
    {OV7725_COM4         , 0xC1},//C1*150 //41 75 //81 115
    {OV7725_CLKRC        , 0x00},//曝光可以用1/2窗口，这样会更好
    {OV7725_COM2         , 0x03},//Bit[5:4]: AEC evaluate window 00: Full window 01: 1/2 window 10: 1/4 window 11: Low 2/3 window
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1E},
#elif (CAMERA_H == 120 )
    {OV7725_VOutSize     , 0x3c},
#elif (CAMERA_H == 180 )
    {OV7725_VOutSize     , 0x5a},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86}, 
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x38},
    {OV7725_CNST         , 0x0A},   // 0x0A keyong 0x10  0x12    0x1b 摄像头阈值
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
	{OV7725_UVADJ1       , 0x02},//0x02},

};
uint8 camera_cfgnum = ARR_SIZE( camera_reg ) ; /*结构体数组成员数目*/


__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) ;
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) ;

//摄像头图像采集中断处理函数 
void PORTA_IRQHandler(void) 
{
	//场中断PTD14
	if((PORTA_ISFR & 0x2000000))//场中断 PTD14 (1<<14)
	{
		PORTA_ISFR |= 0x2000000;  //清除中断标识    
		// 用户程序 
        	DMATransDataStart(DMA_CH4,(uint32_t)(imgbuff),CAMERA_DMA_NUM); //DMA开始传输数据PTD12管脚触发  A24
			return ;
	}
}
void MT9V034_Init(void)
{     
	u16 i=0,j=0;
	uint8 data = 0;
	//GPIO口初始化
//	GPIO_Init(GPIOD,13,GPI,0);   //行中断
	EXTI_Init(GPIOA,25,falling_up);    //场中断  
	GPIO_Init(GPIOB,0,GPI,0);          //八位数据输入口      
	GPIO_Init(GPIOB,1,GPI,0);
	GPIO_Init(GPIOB,2,GPI,0);
	GPIO_Init(GPIOB,3,GPI,0);
	GPIO_Init(GPIOB,4,GPI,0);
	GPIO_Init(GPIOB,5,GPI,0);
	GPIO_Init(GPIOB,6,GPI,0);
	GPIO_Init(GPIOB,7,GPI,0);
	GPIO_Init(GPIOA,24,GPI,0);     //像素  
	
	//摄像头寄存器设置
	SCCB_Init();                     //两个地址口都拉高，为MT9V034_I2C_ADDR 
	///////////////////////////////////////////复位///////////////////////////////////////////////////
	if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) )//SCCB_RegWrite(ADDR_OV7725>>1, OV7725_COM7, 0x80)) //复位传感器
    {
		LCD_P6x8Str(2,1,(u8*)"OV reset error");
		while(1);
    }
	time_delay_ms(1);
	////////////////////////////////////////////读版本/////////////////////////////////////////////////
	if( 1 == SCCB_ReadByte( &data, 1, OV7725_VER ) ) //if(SCCB_RegRead(ADDR_OV7725>>1,OV7725_VER,&data) == 0)//读取摄像头版本寄存器 
	{
		if(data != OV7725_ID)                                  //芯片ID不正确，说明没有正确读取导数据，等待      
		{
			LCD_P6x8Str(2,1,(u8*)"OV7725 NG           ");                      //摄像头识别失败，停止运行
			while(1); 
		} 
		else                                                   //芯片ID正确
		{
			LCD_P6x8Str(2,1,(u8*)"OV7725 OK           ");
		}
	}
	else 
	{
		LCD_P6x8Str(2,1,(u8*)"OV7725 read version error");
		while(1); //摄像头识别失败，停止运行
	}
	time_delay_ms(2);
	/////////////////////////////////////////////写寄存器////////////////////////////////////////////////
	for( i = 0 ; i < camera_cfgnum ; i++ )
	{
		while(!SCCB_ReadByte( &data, 1, camera_reg[i].addr));
		
		while(1)
		{
			time_delay_ms(3);
			if( 1 == SCCB_ReadByte( &data, 1, camera_reg[i].addr) )
			{
				if(data == camera_reg[i].val)
				{
					break;
				}
				else
				{
					time_delay_ms(3);
					SCCB_WriteByte(camera_reg[i].addr, camera_reg[i].val);
				}
			}
		}
	}
	LCD_P6x8Str(2,4,(u8*)"OV write reg - OK");
	time_delay_ms(200);
	DMATransDataInit(DMA_CH4,(void*)&PTB_BYTE0_IN,(void *)imgbuff,PTA24,DMA_BYTE1,CAMERA_DMA_NUM,DMA_falling_down);//初始化DMA采集  
}

/***************************************************************  
* 
* 函数名称：void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_PORTx2BUFF_cfg cfg) 
* 功能说明：初始化DMA 
* 参数说明：通道编号，源地址，目的地址，触发管脚，字节数，循环次数，触发边沿 
* 函数返回：无 
* 修改时间：2018年3月27日 
* 备 注： 
***************************************************************/ 
__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void * DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) 
{ 
	u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //计算传输字节数
	//开启时钟 
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //打开DMA模块时钟
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //打开DMA多路复用器时钟
	// 配置 DMA 通道 的 传输控制块 TCD ( Transfer Control Descriptor ) 
	DMA_SADDR(CHn) =    (u32)SADDR;                         // 设置  源地址
	DMA_DADDR(CHn) =    (u32)DADDR;                         // 设置目的地址
	DMA_SOFF(CHn)  =    0;                                  // 设置源地址不变
	DMA_DOFF(CHn)  =    BYTEs;                                  // 每次传输后，目的加BYUEs
	DMA_ATTR(CHn)  =    (0
						 | DMA_ATTR_SMOD(0x0)                // 源地址模数禁止  Source address modulo feature is disabled
							 | DMA_ATTR_SSIZE(byten)             // 源数据位宽 ：DMA_BYTEn  。    SSIZE = 0 -> 8-bit ，SSIZE = 1 -> 16-bit ，SSIZE = 2 -> 32-bit ，SSIZE = 4 -> 16-byte
								 | DMA_ATTR_DMOD(0x0)                // 目标地址模数禁止
									 | DMA_ATTR_DSIZE(byten)             // 目标数据位宽 ：DMA_BYTEn  。  设置参考  SSIZE
										 );
	DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //当前主循环次数
	DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//起始主循环次数
	
	DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0  disable Minor Loop Mapping
	
	DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // 通道每次传输字节数，这里设置为BYTEs个字节。注：值为0表示传输4GB 
	
	// 配置 DMA 传输结束后的操作 
	DMA_SLAST(CHn)      =   0;                              //调整源地址的附加值,主循环结束后恢复源地址
	DMA_DLAST_SGA(CHn)  =   0;                              //调整目的地址的附加值,主循环结束后恢复目的地址或者保持地址
	DMA_CSR(CHn)        =   (0
							 | DMA_CSR_BWC(3)               //带宽控制,每读一次，eDMA 引擎停止 8 个周期（0不停止；1保留；2停止4周期；3停止8周期）
							 | DMA_CSR_DREQ_MASK            //主循环结束后停止硬件请求
								 | DMA_CSR_INTMAJOR_MASK        //主循环结束后产生中断
									 );
	// 配置 DMA 触发源 
	DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
											  | DMAMUX_CHCFG_ENBL_MASK                        // Enable routing of DMA request 
												  | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) // 通道触发传输源:     
													  );
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));                                //开启PORTx端口
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));                        //设置端口方向为输入
	PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
													 | PORT_PCR_MUX(1)               // 复用GPIO
														 | PORT_PCR_IRQC(cfg & 0x03 )    // 确定触发模式
															 | ((cfg & 0xc0 ) >> 6)          // 开启上拉或下拉电阻，或者没有
																 );
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));  
	
	//开启中断 
	DMA_EN(CHn);                                      //使能通道CHn 硬件请求
	DMA_IRQ_EN(CHn);                                //允许DMA通道传输
} 

/*************************************************************** 

* 
* 函数名称：void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
* 功能说明：设置DMA传输的目的地址和循环次数 
* 参数说明： 
* 函数返回：无
* 修改时间：2018年3月27日 
* 备 注： 
***************************************************************/ 
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
{ 
	DMA_DADDR(CHn) = address;                              //目的地址 
	DMA_CITER_ELINKNO(CHn) = DMA_CITER_ELINKNO_CITER(Val); //当前主循环次数 
	DMA_BITER_ELINKNO(CHn) = DMA_BITER_ELINKYES_BITER(Val);//起始主循环次数 
	//开启中断 
	DMA_EN(CHn);                                           //使能通道CHn 硬件请求
	DMA_IRQ_EN(CHn);                                     //允许DMA通道传输
} 

/*************************************************************************
* 北京龙邱智能科技 KV58智能车母板           
*
*  函数名称：void SCCB_Init(void)
*  功能说明：配置SCCB所用引脚为GPIO功能，暂时不配置数据方向
*  参数说明：无
*  函数返回：无
*  修改时间：2017年12月5日
*  备    注：
*************************************************************************/
void SCCB_Init(void)
{
	GPIO_Init(GPIOB, 18,GPO,1);//配置为GPIO功能
	GPIO_Init(GPIOB, 19,GPO,1);//配置为GPIO功能 
        
        PORT_PCR_REG(PORTB_BASE_PTR, 18);  //上拉电阻
        PORT_PCR_REG(PORTB_BASE_PTR, 19);
}

/*************************************************************************
* 北京龙邱智能科技 KV58智能车母板           
*
*  函数名称：void SCCB_Wait(void)
*  功能说明：SCCB等待演示
*  参数说明：无
*  函数返回：无
*  修改时间：2017年12月5日
*  备    注：
*************************************************************************/
void SCCB_Wait(void)
{
	int i=0;
	for(i=0;i < 1000;i++)
	{ 
		asm ("nop");
	}  
}

/***************************************************************
* 
* 函数名称：SendPicture 
* 功能说明：发送图像到上位机 ，不同的上位机注意修改对应的数据接收协议
* 参数说明： 
* 函数返回：void 
* 修改时间：2018年3月27日 
* 备 注： 
***************************************************************/ 
void UARTSendPicture(uint8_t tmImage[IMAGEH][IMAGEW]) 
{ 
	int i = 0, j = 0; 
	UART_Put_Char(UART_4,0x00); //发送帧头标志 
	UART_Put_Char(UART_4,0xFF); //发送帧头标志 
	UART_Put_Char(UART_4,0x01); //发送帧头标志 
	UART_Put_Char(UART_4,0x00); //发送帧头标志 
	for(i=0;i < IMAGEH; i++) 
	{ 
		for(j=0;j <IMAGEW-3;j++) 
		{ 
			/*if(tmImage[i][j]==0xFE) 
			{ 
			tmImage[i][j]=0xFF; //防止发送标志位 
		} 
			if(tmImage[i][j]==0xEF) 
			{ 
			tmImage[i][j]=0xEE; //防止发送标志位 
		} */
			UART_Put_Char(UART_4,tmImage[i][j]);     
		} 
	} 
} 


/*!
 *  @brief      二值化图像解压
 */
//void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
//{
//    uint8 colour[2] = {0, 1};
////    uint8 tmpsrc;
////    while(srclen --)
////    {
////        tmpsrc = *src++;
////        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
////        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
////    }
//	int i,j;
//	for(i = 0; i < srclen; i++)
//	{
//		for(j = 0;j < 8; j ++)
//		{
//			dst[8*i+j] = (src[i] >> (7 - j))&0x01;
//		}
//	}
//}
void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {0, 1};
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}