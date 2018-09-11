#include "common.h"
#include "include.h"
float h[3][3]=
{
	3.5732,0,        -145,
	0,     25.03,    -295.49,
	0,     0.1189,   -0.40137
};
int map[60][80];
//�����жϸ�λ����

void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT1_IRQHandler();


void init()
{
   PLL_Init(PLL235);//235         //�����ں˼�����Ƶ�ʵ�
   DisableInterrupts;
   //OLED_Init();    
//   OLED_Draw_Logo();
   LCD_Init();               //LCD��ʼ��
   //LCD_CLS();                //����	  
//   LCD_Show_LQLogo();        //��ʾ����LOGO
//   time_delay_ms(500);       //��ʱ  
   LCD_CLS();                //����
//   OLED_CLS(); //OLED����
   KEY_SW_Init(); 

//   led_init();   //����Դ��
   LED_Init(); 
   infrared_init();   //�����ʼ��
   Para_Init();
   //led_flash(); 
   //I2C_Init();
   //adc_init (ADC0_SE14);// ��ص�ѹ�����ӿ� װ������Ϊ3.3/65535*5.7 
//   pit_init_ms(PIT0,2); 
//   pit_init_ms(PIT1,5); 
//   set_vector_handler(PIT0_VECTORn ,PIT_IRQHandler);  //set_vector_handler�������޸��ж��������е��жϺ������
//   set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);
   
   PIT_Init(PIT0, 2);//2ms��ʱ�ж�
   PIT_Init(PIT1, 5);//5ms��ʱ�ж�
   PIT_Init(PIT2, 60);//10ms��ʱ�ж�  ������
   PIT_Init(PIT3, 60);
   UltrasoundInit();
      
   //EEPROM_init();     //flash��ʼ��
   
   Servo_Init();        // ��ʼ�����
   Motor_Init();          //��ʼ�����
   duzhuanFlag = 0;
//   FTM_PWM_init(FTM1,FTM_CH1,100,sever_middle);   //��� PWM  PTA12�����Ƶ��Ϊ100hz ռ�ձȾ���Ϊ10000
   
//   Motor_Init();          //��ʼ�����
//   FTM_PWM_init(FTM0,FTM_CH4,10*1000,3000);      //���PWM Ƶ��Ϊ10khz ռ�ձȾ���Ϊ10000 
//   FTM_PWM_init(FTM0,FTM_CH5,10*1000,0); 
//   FTM_PWM_init(FTM0,FTM_CH6,10*1000,3000);      //���PWM Ƶ��Ϊ10khz ռ�ձȾ���Ϊ10000 
//   FTM_PWM_init(FTM0,FTM_CH7,10*1000,0); 
   SetSpeedRight = 2.2;
   
   FTM_AB_Init(FTM1);
   FTM_AB_Init(FTM2);
//   FTM_QUAD_Init(FTM2); //���������ʼ��;  
//   camera_init();
   MT9V034_Init();         //��ʼ������ͷ   
   CCD1_init();
 //  EnableInterrupts; //���ж�  

//   set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //���ó��ж�
//   set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);   
//   enable_irq(PORTD_IRQn); 
//   set_vector_handler(UART4_RX_TX_VECTORn,UART4_RX_IRQHandler);    //UART0�޸�ΪUART4
//   uart_rx_irq_en(UART4);                                          //UART0�޸�ΪUART4
//   NVIC_SetPriority(UART4_RX_TX_IRQn,0);                           //UART0�޸�ΪUART4   �������ȼ�
//   NVIC_SetPriority(DMA0_VECTORn,1);
//   NVIC_SetPriority(PORTD_VECTORn ,2); //PORTC�޸�ΪPORTD
//   NVIC_SetPriority(PIT1_VECTORn ,3); 
//   NVIC_SetPriority(PIT0_VECTORn ,4); 
//   enable_irq (PIT0_IRQn); 
//   enable_irq (PIT1_IRQn); 
}


//void Para_Init()
//{
//	map_init();
//	PID_SPEED.P=0.30;
//	PID_SPEED.I=0.015;
//	PID_SPEED.D = 0.01;
//	PID_TURN.P=0.013;//0.032;
//	PID_TURN.D=-0.007;//-0.010;
//	Fuzzy_Kp=0.0039;
//	Fuzzy_Kd=0.0040;
//	SetSpeed=3.3;
//	Set_Angle=50;
//	bais=25;//22;
//	Control_Para[0]=SetSpeed;
//	Control_Para[1]=Fuzzy_Kp;
//	Control_Para[2]=bais;
//	Control_Para[3]=PID_SPEED.P;
//	Control_Para[4]=PID_SPEED.I;
//	Control_Para[5]=PID_TURN.P;
//	Control_Para[6]=PID_TURN.D;
//}

void Para_Init()
{
 PID_SPEED.P=1.5;
 PID_SPEED.I=0.05;
 PID_TURN.P=0.01;
 PID_TURN.D=0.005; 
 Fuzzy_Kp=0.005;
 Fuzzy_Kd=0.0005;
 //SetSpeedRight=3.8;
 Set_Angle=50;
}


