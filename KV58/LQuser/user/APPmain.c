/*******************************************************************************
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��3��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4�����ϰ汾
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug������Դ���е��ף�
=============================================================
�ӿڶ��壺
����ͷ          ��Ƭ���ӿ�    
VCC             3.3V 
GND             GND
Y0-7            PTD0-7��8λ����    �޸�ΪB0-B7  
HREF            PTD13   ������
VSY             PTD14  �޸�ΪA25
PCK             PTD12  �޸�ΪA24
-------------------------------------------------------------
TSL1401ģ��     ��Ƭ���ӿ�
VCC             5V
GND             GND
SI              PTE27
SCK             PTE28
ADC             ADC0_SE8
ADC             ADC0_SE4B

SI              PTE2
SCK             PTE3
ADC             ADC0DP0
ADC             ADC0_SE5B
===============================================================
��·���ģ��    ��Ƭ���ӿ�
VCC             3.3V
GND             GND
ADCͨ��         �ܽŹ�ϵ     
ADC0_SE10       PTE5
ADC0_DP2        PTE4
ADC0_SE4A       PTE6
ADC0_DP3        PTE11
ADC0_SE11       PTE12
ADC0_DP1        PTE16
ADC0_SE9        PTE17
ADC0_SE5A       PTE18
-------------------------------------------------------------
��Դ��ػ�������
ADC0_SE7A       HSADC0CH6  
-------------------------------------------------------------
����ģ��        ��Ƭ���ӿ�   FLEXCOMM8
VCC             3V3
GND             GND
SDA1            PTD8
SCL1            PTD9
//////////////////////////////////////////////////////////ͨ�ò��ֹ���//////////
�������        ��Ƭ���ӿ�   
VCC             3.3V
FTM0_CH0  PTC1����������ӿ�
FTM0_CH1  PTC2����������ӿ�
FTM0_CH2  PTC3����������ӿ�
FTM0_CH3  PTC4����������ӿ�
-------------------------------------------------------------
����ӿ�        ��Ƭ���ӿ�
VADJ            �ɵ���Դ
GND             GND
FTM3_CH6        PTC10������ӿ�  �޸�ΪFTM3_CH2    PTE7����ӿ�
FTM3_CH7        PTC11������ӿ�
-------------------------------------------------------------
����512������   ��Ƭ���ӿ�     
VCC             3V3
GND             GND      
LSB/A           PTA12     FTM1_QD_PHA	PTA12
DIR/B           PTA13     FTM1_QD_PHB	PTA13
LSB/A           PTB18    �޸�ΪFTM2_QD_PHA	PTA10
DIR/B           PTB19    �޸�ΪFTM2_QD_PHB	PTA11
-------------------------------------------------------------
OLEDģ��        ��Ƭ���ӿ�  ���İ��õ���PTC16-19
VCC             3.3V        �û������޸ĳ�ʼ���͹ܽŶ���
GND             GND
RST             PTC13
DC              PTC14
SDA             PTC15
CLK             PTC16
CS              PTC12
-------------------------------------------------------------
����/USBTTL     ��Ƭ���ӿ�   
GND             GND
TX              PTE24   UART4_TX ��������RX
RX              PTE25   UART4_RX ��������TX
-------------------------------------------------------------
LED�ӿڶ��壺
LED1            PTA17 ���İ�
LED2            PTC0  ���İ�
LED3            PTD15 ���İ�   
LED4            PTE29 ���İ�

-------------------------------------------------------------
KEY�ӿڶ��壺
KEY0            PTB20  
KEY1            PTB21
KEY2            PTB22   //���жϴ���

�޸�Ϊ 
BSW1	PTD4
BSW2	PTD5
BSW3	PTD6
BSW4	PTD7

SW1	PTD13
SW2	PTD14
SW3	PTD10
SW4	PTD11
SW5	PTD12
-------------------------------------------------------------
����ӿ�
INF1	PTC12
INF2	PTC13
INF3	PTC14
INF4	PTC15
INF5	PTD0
INF6	PTD1
INF7	PTD2
INF8	PTD3

-------------------------------------------------------------
�޸���ʷ��
20180208-�жϴ�������startup_MKV58F24.s�У����ֱ����Ӧ���ܴ����жϣ�
20180327-�Ѿ��޸���������ͷ�Ĳɼ�ģʽΪDMA���ֱ���Ϊ188*120��100db HDR��
********************************************************************************/
#include "common.h"
#include "include.h"

//extern uint8 RotaryIslandFlag;
//extern uint8 RightInAngle;
//extern uint8 LeftInAngle;
//extern u32 ServoValue;
//extern uint8_t Threshold;
//extern u8 Image_Data[4800];//[60][150];
//void Main_Program();
//uint8 flagggg=0;
//extern uint8 BlackLeftStep1ScanRow;
//extern uint8 BlackRightStep1ScanRow;
//extern int32 DeviPre;
//extern u32 ServoValue;
//extern s16 speed;
//uint8 qidongflag=0;  //�������OLED�޸Ĳ����Ļ�������flag�ᱻ��λ
//uint8 qidongflag1=0;
//uint8 failstop=0;
//==========================================================================================  
//���Ժ�������        �����ڲ�ģ�鼰����           ���ܳ���Ӧ�ÿ���               ���״��
//----------------------------------------------------------------------------------------- 
//Test_LED();         //����GPIO�����              LED��ʾ���������              �����
//Test_OLED();       //����ģ��SPI����              OLEDģ�鹦��                   �����
//Test_GPIO_KEY();   //����GPIO����                 ������⹦��                   ����� 
//Test_GPIO_EXINT(); //����GPIO���뼰�ⲿ�ж�       �������жϼ�⹦��             �����     
//Test_UART();       //����UART���ж�               ������USBתTTL���Լ�ͨ��       �����
//Test_ADC0();       //����ADC�ɼ�����              ��Ŵ���������Դ��ѹ���       �������,HSADC����ͨ��
//void Test_Servo();      //������FTM-PWM����            ���ֶ����������               �����
//Test_Motor();      //������FTM-PWM����            �����������                   �����
//Test_AB_Pulse_Cnt();//������FTM�������빦��       ����������,����������        ����� 
//Test_LPTMR_delay();//����LPTMR����                ��ʱ����                       �����
//Test_LPTMR_Counter();//����LPTMR����              ��������                       �����
//Test_DMA_Counter();//����DMA��������              ��������                       �����
//TestOLED_TSL1401();//����OLED��TSL1401����        OLED��ʾ������������ͷ         �����
//TestOLED_MT9V034();//����OLED��MT9V034����        OLED��ʾ������������ͷ��ͼ     �����
//Test_WDG();        //���Կ��Ź�����               ������                       �����
//========================================================================================== 


void  main(void)
{ 
//  int twinkle_Flag = 0;
  uint16 time;
  
  init();
  LCD_CLS();                //����
  OLED_P6x8Str(60,4,"Wait");
  TakeOff = 1;
//  ����û�к���ģ�� by zhang 20180911
//  while(infrared_succeed == 0)
//  {
//   infrared_succeed = infrared_pro();   //����ɼ����ɹ�����1;
//  }
 
  EnableInterrupts; //���ж�  
  Motor_Duty(Mot0, 300);
  Motor_Duty(Mot2, 300);
  LCD_CLS();                //����
  OLED_P6x8Str(60,4,"Go");
  //Stop=1;   //���ͣ�����
  UART_Init(UART_4,115200);   //1500000   UART0�޸�ΪUART4  
  if(infrared_succeed == 1 )
  {
     USTrigger();
  }

   while(1)
    {
      
      Read_Switch();      //���ذ���ɨ��
      Check_BottonPress();
         
//      while(SendPara)   //����ʾ������������
//      {
//        //SendPara=0;
//        //Send_Parameter();
//        if(new_img)  //�˶β�����0.5ms 200ms��Ƶ  6ms ��8ms ִ��һ��
//       {
//        new_img=0;
//        SignalGet();
//        Direction_Control();
//        
//        Variable_update(); //���в���    
//       }  
//        Send_Variable();   //Variable�����в���  Parameter���趨����
//        Read_Switch();      //���ذ���ɨ��
//      }  
      
       while(Send_img && new_img)    //��ͼ��//uint8 Send_img = 0;��ʼֵΪ0������2SW2��ı�Send_img��ֵ by zhang 2018 09 11
       {
          new_img = 0;
          
          SignalGet();
//          if ((CCDLightCnt != 0 && CCDPosition != 255) && twinkle_Flag <=20)    // ���������
//        {
//            Direction_Control();
//            twinkle_Flag = 0;
//        }
//        else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=20)   //ǰ20��û���ĵ�ͼ��
//        {
//          // DELAY_MS(30);
//           twinkle_Flag++;
//           continue;
//        }
//        else                             
//        {
          Direction_Control();
          Variable_update(); //���в���  
          sendimg();  
          Send_CCD();  
          Send_Variable();   //Variable�����в���  Parameter���趨����
          Read_Switch();      //���ذ���ɨ��
       }
       
       if(new_img)  //�˶β�����0.5ms 200ms��Ƶ  6ms ��8ms ִ��һ��
      {
        new_img=0;
//        get_edge();   //�õ�ͼ���������
//        Search();    //������ȡ
        //while(new_img == 0);
        SignalGet();    
        Direction_Control();
        Variable_update(); //���в���
        //Send_Variable();
        
        //led_flash();        //ʱ��̫��
      }  
      while(OLED_Refresh && new_img)
      {
        new_img = 0;
        img_extract(img,imgbuff_process,CAMERA_SIZE);   //��ֵ��ͼ���ѹ��һ�����鵥Ԫ�洢һ�����ص�
        OLED_Draw_UI();            //����OLED����
        Read_Switch(); 
        SignalGet();
//        if ((CCDLightCnt != 0 && CCDPosition != 255) && twinkle_Flag <=20)    // ���������
//        {
//            Direction_Control();
//            twinkle_Flag = 0;
//        }
//        else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=20)   //ǰ����û���ĵ�ͼ��
//        {
//          // DELAY_MS(30);
//           twinkle_Flag++;
//           continue;
//        }
//        else                             
//        {
//           Direction_Control();
//           twinkle_Flag = 0;
//        }  
        Direction_Control();
        Check_BottonPress();
      }   
     // time = pit_time_get(PIT1);
     }
   
}

void PIT0_IRQHandler()  //2msһ���ж�
{
    static uint8 flag_100ms,cnt=0; //CCD_cnt=0;
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
     
    if(!Stop)
    { 
     RunTime=RunTime+0.002;
     AverageSpeed=Distance/RunTime;
    }
    
    flag_100ms++;
    if(flag_100ms>Speed_Filter_Times) //>50
    {
     flag_100ms=0;  
     Speed_Control();  //100ms����һ���ٶȿ���
     SpeedCount=0;
    }
    if(Starting)
    {
      Start_Cnt--; 
//      LED_GREEN_TURN;
      if(Start_Cnt==0)
      {
        Starting=0;
        Stop=0;
//        LED_BLUE_OFF;
//        LED_GREEN_OFF;
      }
    }
   cnt++;
   if(cnt==1)      //4ms����һ��
   {
     Get_Speed();
   }
   if(cnt>=2)
   {
     cnt=0;
   }
   SpeedCount++;
   Speed_Control_Output();
   if (HighSpeed == 1 )
      MotorControl(PID_SPEED.OutLeft,PID_SPEED.OutRight);   //���ҵ�����ٿ���
   else;
}

void PIT1_IRQHandler()  //5ms�ж�һ��
{
    PIT_Flag_Clear(PIT1);       //���жϱ�־λ
    static int CCD_cnt=0;
    CCD_cnt++;
    if(CCD_cnt >= 3)   //15ms
    {
      CCD1_scan();
      CCD_cnt = 0; 
    }
    
}


//void main(void)
//{  
//	PLL_Init(PLL235);//235         //�����ں˼�����Ƶ�ʵ�
//	DisableInterrupts;
//	KEY_SW_Init();               //����������ڳ�ʼ��  
//	//LED_Init();               //LED��ʼ��
//	UART_Init(UART_4,115200); //���ڳ�ʼ��//????
//	//	Ĭ��ʹ��:���� OLED SPIģ��
//	LCD_Init();               //LCD��ʼ��
//	//LCD_CLS();                //����	  
//	LCD_Show_LQLogo();        //��ʾ����LOGO
//	time_delay_ms(500);       //��ʱ  
//	LCD_CLS();                //����
//	//time_delay_ms(50);        //��ʱ 
//	//LED_Ctrl(LEDALL, OFF);
//	GPIO_Init(GPIOB,7,GPO,1);
//	GPIO_Init(GPIOC,6,GPI,1);
//	GPIO_Init(GPIOC,7,GPI,1);
//	GPIO_Init(GPIOC,8,GPI,1);
//	GPIO_Init(GPIOC,9,GPI,1);
//	GPIO_Init(GPIOC,2,GPO,1);
//	
//	//��Դ�ɼ�ADC
//	//ADC0_Init();//????
//	//FTM_AB_Init(FTM2);
//	PIT_Init(PIT0, 2);
//	
//	//Servo_Init();          // ��ʼ�����
//	//Motor_Init();          //��ʼ�����
//	MT9V034_Init();         //��ʼ������ͷ
//	
//	//Para_Init();        //�����ʼ��Ϊ�����趨ֵwk
//	EnableInterrupts;
//	
//	//-----------------------------------------------------------------------------------------  
//	//  ���Ժ���������ѭ����ÿ��ֻ�ܿ���һ��
//	//-----------------------------------------------------------------------------------------
//	//Test_ADC0();         //����ADC�ɼ�����               ��Ŵ���������Դ��ѹ��� 
//	//Test_UART();         //����UART���ж�                ������USBתTTL���Լ�ͨ��
//	//Test_LED();          //����GPIO�����                LED��ʾ���������        
//	//Test_OLED();         //O����ģ��SPI����              OLEDģ�鹦��   
//	//Test_GPIO_KEY();     //����GPIO����                  ������⹦��              
//	//Test_GPIO_EXINT();   //����GPIO���뼰�ⲿ�ж�        �������жϼ�⹦��  
//	//	Test_Servo();        //���ֶ������
// 	//Test_Motor();        //ֱ������������ԣ�            ������ȫ��������
//	//Test_9AX();          //����I2C���������
//	//Test_MPU6050();      //����I2C��6�������ǹ���
//	//	Test_LQV034();       //OLED��ʾ������������ͷ��ͼ 
//	//Test_PIT();          //����PIT��ʱ�жϹ���
//	//Test_AB_Pulse_Cnt(); //���Ա������������빦��
//	//Test_LPTMR_delay();  //����LPTMR��ʱ����                
//	//Test_LPTMR_Counter();//����LPTMR��������   
//	//Test_DMA_Counter();  //����DMA��������   
//	//TFTSPI_Test();          //��������TFT1.8��SPI����
//	//Test_OLED();  
//	Main_Program();      //������
//	//-----------------------------------------------------------------------------------------
//	while(1)
//	{   
//		//LED_Ctrl(LED1, RVS);//��ת       
//		//time_delay_ms(500); //��ʱ           
//	}
//}
//
//void Main_Program()
//{
//	int i;
//	Stop=1;
//	Dirc=1;
//	new_img=1;
//	while(1)
//	{
//		Read_Switch();
//		//Check_BottonPress();
//		if(SendPara)
//		{
//			SendPara=0;
//			Send_Parameter();
//		}
//		if(new_img)
//		{
//			//get_edge();
//			//Search();
//			//Direction_Control();
//			new_img = 0;
//			if(0)
//			{
//				Send_Begin();
//				Variable_update();
//				Send_Variable();
//				sendimg();
//			}
//			if(1)
//			{
//				img_extract(img,imgbuff_process,CAMERA_SIZE);
//				OLED_Draw_UI();
//			}
//		}
//	}
//}
//
//////////////////////////////////////===================///////////////////////////
////�������
//void PIT0_IRQHandler()
//{
//	static uint8 flag_100ms,cnt=0;
//	PIT_Flag_Clear(PIT0);       //���жϱ�־λ
//	
//	if(!Stop)
//	{
//		RunTime=RunTime+0.002;
//		AverageSpeed=Distance/RunTime;
//	}
//	//100ms
//	flag_100ms++;
//	if(flag_100ms>Speed_Filter_Times)
//	{
//		flag_100ms=0;  
//		Speed_Control();  //60ms����һ���ٶȿ���
//		SpeedCount=0;
//	}
//	if(Starting)
//	{
//		Start_Cnt--; 
//		LED_GREEN_TURN;
//		if(Start_Cnt==0)
//		{
//			Starting=0;
//			Stop=0;
//			LED_BLUE_OFF;
//			LED_GREEN_OFF;
//		}
//	}
//	
//	cnt++;
//	if(cnt==1)      //4ms����һ��
//	{
//		//Get_Speed();
//	}
//	if(cnt>=2)	cnt=0;
//	
//	SpeedCount++;
//	Speed_Control_Output();
//	//Moto_Out();
//}
//
//
//
//
