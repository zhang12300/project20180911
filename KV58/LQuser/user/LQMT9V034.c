/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��3��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4������
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
uint8 imgbuff[CAMERA_SIZE];                       //����洢����ͼ�������
uint8 imgbuff_process[CAMERA_SIZE];               //���崦��ͼ���õ�����
uint8 img_edg[CAMERA_SIZE*2];                           //
uint8 img[CAMERA_W*CAMERA_H];                           //
uint8 LMR[3][CAMERA_H];
uint8 new_img=0;

uint8_t Threshold;                  //OSTU��򷨼����ͼ����ֵ
volatile u8  Line_Cont=0;          //�м���
volatile u8  Field_Over_Flag=0;    //����ʶ
uint16_t cc;
int OFFSET0=0;      //��Զ������������ֵ�ۺ�ƫ����
int OFFSET1=0;      //�ڶ���
int OFFSET2=0;      //�����������
int TXV=0;          //���ε���߶ȣ��Ҹ߶�

reg_s camera_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
    {OV7725_COM4         , 0xC1},//C1*150 //41 75 //81 115
    {OV7725_CLKRC        , 0x00},//�ع������1/2���ڣ����������
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
    {OV7725_CNST         , 0x0A},   // 0x0A keyong 0x10  0x12    0x1b ����ͷ��ֵ
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
	{OV7725_UVADJ1       , 0x02},//0x02},

};
uint8 camera_cfgnum = ARR_SIZE( camera_reg ) ; /*�ṹ�������Ա��Ŀ*/


__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) ;
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) ;

//����ͷͼ��ɼ��жϴ����� 
void PORTA_IRQHandler(void) 
{
	//���ж�PTD14
	if((PORTA_ISFR & 0x2000000))//���ж� PTD14 (1<<14)
	{
		PORTA_ISFR |= 0x2000000;  //����жϱ�ʶ    
		// �û����� 
        	DMATransDataStart(DMA_CH4,(uint32_t)(imgbuff),CAMERA_DMA_NUM); //DMA��ʼ��������PTD12�ܽŴ���  A24
			return ;
	}
}
void MT9V034_Init(void)
{     
	u16 i=0,j=0;
	uint8 data = 0;
	//GPIO�ڳ�ʼ��
//	GPIO_Init(GPIOD,13,GPI,0);   //���ж�
	EXTI_Init(GPIOA,25,falling_up);    //���ж�  
	GPIO_Init(GPIOB,0,GPI,0);          //��λ���������      
	GPIO_Init(GPIOB,1,GPI,0);
	GPIO_Init(GPIOB,2,GPI,0);
	GPIO_Init(GPIOB,3,GPI,0);
	GPIO_Init(GPIOB,4,GPI,0);
	GPIO_Init(GPIOB,5,GPI,0);
	GPIO_Init(GPIOB,6,GPI,0);
	GPIO_Init(GPIOB,7,GPI,0);
	GPIO_Init(GPIOA,24,GPI,0);     //����  
	
	//����ͷ�Ĵ�������
	SCCB_Init();                     //������ַ�ڶ����ߣ�ΪMT9V034_I2C_ADDR 
	///////////////////////////////////////////��λ///////////////////////////////////////////////////
	if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80 ) )//SCCB_RegWrite(ADDR_OV7725>>1, OV7725_COM7, 0x80)) //��λ������
    {
		LCD_P6x8Str(2,1,(u8*)"OV reset error");
		while(1);
    }
	time_delay_ms(1);
	////////////////////////////////////////////���汾/////////////////////////////////////////////////
	if( 1 == SCCB_ReadByte( &data, 1, OV7725_VER ) ) //if(SCCB_RegRead(ADDR_OV7725>>1,OV7725_VER,&data) == 0)//��ȡ����ͷ�汾�Ĵ��� 
	{
		if(data != OV7725_ID)                                  //оƬID����ȷ��˵��û����ȷ��ȡ�����ݣ��ȴ�      
		{
			LCD_P6x8Str(2,1,(u8*)"OV7725 NG           ");                      //����ͷʶ��ʧ�ܣ�ֹͣ����
			while(1); 
		} 
		else                                                   //оƬID��ȷ
		{
			LCD_P6x8Str(2,1,(u8*)"OV7725 OK           ");
		}
	}
	else 
	{
		LCD_P6x8Str(2,1,(u8*)"OV7725 read version error");
		while(1); //����ͷʶ��ʧ�ܣ�ֹͣ����
	}
	time_delay_ms(2);
	/////////////////////////////////////////////д�Ĵ���////////////////////////////////////////////////
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
	DMATransDataInit(DMA_CH4,(void*)&PTB_BYTE0_IN,(void *)imgbuff,PTA24,DMA_BYTE1,CAMERA_DMA_NUM,DMA_falling_down);//��ʼ��DMA�ɼ�  
}

/***************************************************************  
* 
* �������ƣ�void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_PORTx2BUFF_cfg cfg) 
* ����˵������ʼ��DMA 
* ����˵����ͨ����ţ�Դ��ַ��Ŀ�ĵ�ַ�������ܽţ��ֽ�����ѭ���������������� 
* �������أ��� 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void * DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) 
{ 
	u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //���㴫���ֽ���
	//����ʱ�� 
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��
	// ���� DMA ͨ�� �� ������ƿ� TCD ( Transfer Control Descriptor ) 
	DMA_SADDR(CHn) =    (u32)SADDR;                         // ����  Դ��ַ
	DMA_DADDR(CHn) =    (u32)DADDR;                         // ����Ŀ�ĵ�ַ
	DMA_SOFF(CHn)  =    0;                                  // ����Դ��ַ����
	DMA_DOFF(CHn)  =    BYTEs;                                  // ÿ�δ����Ŀ�ļ�BYUEs
	DMA_ATTR(CHn)  =    (0
						 | DMA_ATTR_SMOD(0x0)                // Դ��ַģ����ֹ  Source address modulo feature is disabled
							 | DMA_ATTR_SSIZE(byten)             // Դ����λ�� ��DMA_BYTEn  ��    SSIZE = 0 -> 8-bit ��SSIZE = 1 -> 16-bit ��SSIZE = 2 -> 32-bit ��SSIZE = 4 -> 16-byte
								 | DMA_ATTR_DMOD(0x0)                // Ŀ���ַģ����ֹ
									 | DMA_ATTR_DSIZE(byten)             // Ŀ������λ�� ��DMA_BYTEn  ��  ���òο�  SSIZE
										 );
	DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //��ǰ��ѭ������
	DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//��ʼ��ѭ������
	
	DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0  disable Minor Loop Mapping
	
	DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // ͨ��ÿ�δ����ֽ�������������ΪBYTEs���ֽڡ�ע��ֵΪ0��ʾ����4GB 
	
	// ���� DMA ���������Ĳ��� 
	DMA_SLAST(CHn)      =   0;                              //����Դ��ַ�ĸ���ֵ,��ѭ��������ָ�Դ��ַ
	DMA_DLAST_SGA(CHn)  =   0;                              //����Ŀ�ĵ�ַ�ĸ���ֵ,��ѭ��������ָ�Ŀ�ĵ�ַ���߱��ֵ�ַ
	DMA_CSR(CHn)        =   (0
							 | DMA_CSR_BWC(3)               //�������,ÿ��һ�Σ�eDMA ����ֹͣ 8 �����ڣ�0��ֹͣ��1������2ֹͣ4���ڣ�3ֹͣ8���ڣ�
							 | DMA_CSR_DREQ_MASK            //��ѭ��������ֹͣӲ������
								 | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
									 );
	// ���� DMA ����Դ 
	DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
											  | DMAMUX_CHCFG_ENBL_MASK                        // Enable routing of DMA request 
												  | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) // ͨ����������Դ:     
													  );
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));                                //����PORTx�˿�
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));                        //���ö˿ڷ���Ϊ����
	PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
													 | PORT_PCR_MUX(1)               // ����GPIO
														 | PORT_PCR_IRQC(cfg & 0x03 )    // ȷ������ģʽ
															 | ((cfg & 0xc0 ) >> 6)          // �����������������裬����û��
																 );
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));  
	
	//�����ж� 
	DMA_EN(CHn);                                      //ʹ��ͨ��CHn Ӳ������
	DMA_IRQ_EN(CHn);                                //����DMAͨ������
} 

/*************************************************************** 

* 
* �������ƣ�void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
* ����˵��������DMA�����Ŀ�ĵ�ַ��ѭ������ 
* ����˵���� 
* �������أ���
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
{ 
	DMA_DADDR(CHn) = address;                              //Ŀ�ĵ�ַ 
	DMA_CITER_ELINKNO(CHn) = DMA_CITER_ELINKNO_CITER(Val); //��ǰ��ѭ������ 
	DMA_BITER_ELINKNO(CHn) = DMA_BITER_ELINKYES_BITER(Val);//��ʼ��ѭ������ 
	//�����ж� 
	DMA_EN(CHn);                                           //ʹ��ͨ��CHn Ӳ������
	DMA_IRQ_EN(CHn);                                     //����DMAͨ������
} 

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Init(void)
*  ����˵��������SCCB��������ΪGPIO���ܣ���ʱ���������ݷ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Init(void)
{
	GPIO_Init(GPIOB, 18,GPO,1);//����ΪGPIO����
	GPIO_Init(GPIOB, 19,GPO,1);//����ΪGPIO���� 
        
        PORT_PCR_REG(PORTB_BASE_PTR, 18);  //��������
        PORT_PCR_REG(PORTB_BASE_PTR, 19);
}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Wait(void)
*  ����˵����SCCB�ȴ���ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
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
* �������ƣ�SendPicture 
* ����˵��������ͼ����λ�� ����ͬ����λ��ע���޸Ķ�Ӧ�����ݽ���Э��
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
void UARTSendPicture(uint8_t tmImage[IMAGEH][IMAGEW]) 
{ 
	int i = 0, j = 0; 
	UART_Put_Char(UART_4,0x00); //����֡ͷ��־ 
	UART_Put_Char(UART_4,0xFF); //����֡ͷ��־ 
	UART_Put_Char(UART_4,0x01); //����֡ͷ��־ 
	UART_Put_Char(UART_4,0x00); //����֡ͷ��־ 
	for(i=0;i < IMAGEH; i++) 
	{ 
		for(j=0;j <IMAGEW-3;j++) 
		{ 
			/*if(tmImage[i][j]==0xFE) 
			{ 
			tmImage[i][j]=0xFF; //��ֹ���ͱ�־λ 
		} 
			if(tmImage[i][j]==0xEF) 
			{ 
			tmImage[i][j]=0xEE; //��ֹ���ͱ�־λ 
		} */
			UART_Put_Char(UART_4,tmImage[i][j]);     
		} 
	} 
} 


/*!
 *  @brief      ��ֵ��ͼ���ѹ
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