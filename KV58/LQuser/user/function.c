#include "common.h"
#include "include.h"
float h[3][3]=
{
	3.5732,0,        -145,
	0,     25.03,    -295.49,
	0,     0.1189,   -0.40137
};
int map[60][80];
//配置中断复位函数

void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT1_IRQHandler();


void init()
{
   PLL_Init(PLL235);//235         //设置内核及总线频率等
   DisableInterrupts;
   //OLED_Init();    
//   OLED_Draw_Logo();
   LCD_Init();               //LCD初始化
   //LCD_CLS();                //清屏	  
//   LCD_Show_LQLogo();        //显示龙邱LOGO
//   time_delay_ms(500);       //延时  
   LCD_CLS();                //清屏
//   OLED_CLS(); //OLED清屏
   KEY_SW_Init(); 

//   led_init();   //开电源灯
   LED_Init(); 
   infrared_init();   //红外初始化
   Para_Init();
   //led_flash(); 
   //I2C_Init();
   //adc_init (ADC0_SE14);// 电池电压采样接口 装换比例为3.3/65535*5.7 
//   pit_init_ms(PIT0,2); 
//   pit_init_ms(PIT1,5); 
//   set_vector_handler(PIT0_VECTORn ,PIT_IRQHandler);  //set_vector_handler函数来修改中断向量表中的中断函数入口
//   set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);
   
   PIT_Init(PIT0, 2);//2ms定时中断
   PIT_Init(PIT1, 5);//5ms定时中断
   PIT_Init(PIT2, 60);//10ms定时中断  超声波
   PIT_Init(PIT3, 60);
   UltrasoundInit();
      
   //EEPROM_init();     //flash初始化
   
   Servo_Init();        // 初始化舵机
   Motor_Init();          //初始化电机
   duzhuanFlag = 0;
//   FTM_PWM_init(FTM1,FTM_CH1,100,sever_middle);   //舵机 PWM  PTA12输出，频率为100hz 占空比精度为10000
   
//   Motor_Init();          //初始化电机
//   FTM_PWM_init(FTM0,FTM_CH4,10*1000,3000);      //电机PWM 频率为10khz 占空比精度为10000 
//   FTM_PWM_init(FTM0,FTM_CH5,10*1000,0); 
//   FTM_PWM_init(FTM0,FTM_CH6,10*1000,3000);      //电机PWM 频率为10khz 占空比精度为10000 
//   FTM_PWM_init(FTM0,FTM_CH7,10*1000,0); 
   SetSpeedRight = 2.2;
   
   FTM_AB_Init(FTM1);
   FTM_AB_Init(FTM2);
//   FTM_QUAD_Init(FTM2); //正交解码初始化;  
//   camera_init();
   MT9V034_Init();         //初始化摄像头   
   CCD1_init();
 //  EnableInterrupts; //打开中断  

//   set_vector_handler(PORTD_VECTORn ,PORTD_IRQHandler);    //设置场中断
//   set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);   
//   enable_irq(PORTD_IRQn); 
//   set_vector_handler(UART4_RX_TX_VECTORn,UART4_RX_IRQHandler);    //UART0修改为UART4
//   uart_rx_irq_en(UART4);                                          //UART0修改为UART4
//   NVIC_SetPriority(UART4_RX_TX_IRQn,0);                           //UART0修改为UART4   设置优先级
//   NVIC_SetPriority(DMA0_VECTORn,1);
//   NVIC_SetPriority(PORTD_VECTORn ,2); //PORTC修改为PORTD
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


