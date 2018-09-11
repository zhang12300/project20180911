/*******************************************************************************
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年3月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上版本
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】137.500MHz
【pllclock】275.000MHz
------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug，将开源进行到底；
=============================================================
接口定义：
摄像头          单片机接口    
VCC             3.3V 
GND             GND
Y0-7            PTD0-7共8位并口    修改为B0-B7  
HREF            PTD13   不用了
VSY             PTD14  修改为A25
PCK             PTD12  修改为A24
-------------------------------------------------------------
TSL1401模块     单片机接口
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
多路电感模块    单片机接口
VCC             3.3V
GND             GND
ADC通道         管脚关系     
ADC0_SE10       PTE5
ADC0_DP2        PTE4
ADC0_SE4A       PTE6
ADC0_DP3        PTE11
ADC0_SE11       PTE12
ADC0_DP1        PTE16
ADC0_SE9        PTE17
ADC0_SE5A       PTE18
-------------------------------------------------------------
电源监控或者它用
ADC0_SE7A       HSADC0CH6  
-------------------------------------------------------------
九轴模块        单片机接口   FLEXCOMM8
VCC             3V3
GND             GND
SDA1            PTD8
SCL1            PTD9
//////////////////////////////////////////////////////////通用部分功能//////////
电机驱动        单片机接口   
VCC             3.3V
FTM0_CH0  PTC1，电机驱动接口
FTM0_CH1  PTC2，电机驱动接口
FTM0_CH2  PTC3，电机驱动接口
FTM0_CH3  PTC4，电机驱动接口
-------------------------------------------------------------
舵机接口        单片机接口
VADJ            可调电源
GND             GND
FTM3_CH6        PTC10，舵机接口  修改为FTM3_CH2    PTE7舵机接口
FTM3_CH7        PTC11，舵机接口
-------------------------------------------------------------
龙邱512编码器   单片机接口     
VCC             3V3
GND             GND      
LSB/A           PTA12     FTM1_QD_PHA	PTA12
DIR/B           PTA13     FTM1_QD_PHB	PTA13
LSB/A           PTB18    修改为FTM2_QD_PHA	PTA10
DIR/B           PTB19    修改为FTM2_QD_PHB	PTA11
-------------------------------------------------------------
OLED模块        单片机接口  核心板用的是PTC16-19
VCC             3.3V        用户自行修改初始化和管脚定义
GND             GND
RST             PTC13
DC              PTC14
SDA             PTC15
CLK             PTC16
CS              PTC12
-------------------------------------------------------------
蓝牙/USBTTL     单片机接口   
GND             GND
TX              PTE24   UART4_TX 接蓝牙的RX
RX              PTE25   UART4_RX 接蓝牙的TX
-------------------------------------------------------------
LED接口定义：
LED1            PTA17 核心板
LED2            PTC0  核心板
LED3            PTD15 核心板   
LED4            PTE29 核心板

-------------------------------------------------------------
KEY接口定义：
KEY0            PTB20  
KEY1            PTB21
KEY2            PTB22   //可中断触发

修改为 
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
红外接口
INF1	PTC12
INF2	PTC13
INF3	PTC14
INF4	PTC15
INF5	PTD0
INF6	PTD1
INF7	PTD2
INF8	PTD3

-------------------------------------------------------------
修改历史：
20180208-中断处理函数在startup_MKV58F24.s中，名字必须对应才能触发中断；
20180327-已经修改神眼摄像头的采集模式为DMA，分辨率为188*120，100db HDR；
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
//uint8 qidongflag=0;  //如果有用OLED修改参数的话，参数flag会被置位
//uint8 qidongflag1=0;
//uint8 failstop=0;
//==========================================================================================  
//测试函数名称        测试内部模块及功能           智能车及应用开发               完成状况
//----------------------------------------------------------------------------------------- 
//Test_LED();         //测试GPIO输出口              LED显示及外设控制              已完成
//Test_OLED();       //测试模拟SPI功能              OLED模块功能                   已完成
//Test_GPIO_KEY();   //测试GPIO输入                 按键检测功能                   已完成 
//Test_GPIO_EXINT(); //测试GPIO输入及外部中断       按键、中断检测功能             已完成     
//Test_UART();       //测试UART及中断               蓝牙、USB转TTL调试及通信       已完成
//Test_ADC0();       //测试ADC采集功能              电磁传感器及电源电压监控       部分完成,HSADC不能通过
//void Test_Servo();      //测试用FTM-PWM功能            数字舵机驱动控制               已完成
//Test_Motor();      //测试用FTM-PWM功能            电机驱动控制                   已完成
//Test_AB_Pulse_Cnt();//测试用FTM正交解码功能       编码器测速,电机舵机控制        已完成 
//Test_LPTMR_delay();//测试LPTMR功能                延时功能                       已完成
//Test_LPTMR_Counter();//测试LPTMR功能              计数功能                       已完成
//Test_DMA_Counter();//测试DMA计数功能              计数功能                       已完成
//TestOLED_TSL1401();//测试OLED和TSL1401功能        OLED显示屏及线阵摄像头         已完成
//TestOLED_MT9V034();//测试OLED和MT9V034功能        OLED显示屏及面阵摄像头动图     已完成
//Test_WDG();        //测试看门狗功能               程序监控                       已完成
//========================================================================================== 


void  main(void)
{ 
//  int twinkle_Flag = 0;
  uint16 time;
  
  init();
  LCD_CLS();                //清屏
  OLED_P6x8Str(60,4,"Wait");
  TakeOff = 1;
//  现在没有红外模块 by zhang 20180911
//  while(infrared_succeed == 0)
//  {
//   infrared_succeed = infrared_pro();   //红外采集，成功返回1;
//  }
 
  EnableInterrupts; //打开中断  
  Motor_Duty(Mot0, 300);
  Motor_Duty(Mot2, 300);
  LCD_CLS();                //清屏
  OLED_P6x8Str(60,4,"Go");
  //Stop=1;   //电机停车相关
  UART_Init(UART_4,115200);   //1500000   UART0修改为UART4  
  if(infrared_succeed == 1 )
  {
     USTrigger();
  }

   while(1)
    {
      
      Read_Switch();      //开关按键扫描
      Check_BottonPress();
         
//      while(SendPara)   //虚拟示波器，传数据
//      {
//        //SendPara=0;
//        //Send_Parameter();
//        if(new_img)  //此段不超过0.5ms 200ms主频  6ms 或8ms 执行一次
//       {
//        new_img=0;
//        SignalGet();
//        Direction_Control();
//        
//        Variable_update(); //运行参数    
//       }  
//        Send_Variable();   //Variable是运行参数  Parameter是设定参数
//        Read_Switch();      //开关按键扫描
//      }  
      
       while(Send_img && new_img)    //传图像//uint8 Send_img = 0;初始值为0；拨码2SW2会改变Send_img的值 by zhang 2018 09 11
       {
          new_img = 0;
          
          SignalGet();
//          if ((CCDLightCnt != 0 && CCDPosition != 255) && twinkle_Flag <=20)    // 正常情况下
//        {
//            Direction_Control();
//            twinkle_Flag = 0;
//        }
//        else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=20)   //前20次没有拍到图像
//        {
//          // DELAY_MS(30);
//           twinkle_Flag++;
//           continue;
//        }
//        else                             
//        {
          Direction_Control();
          Variable_update(); //运行参数  
          sendimg();  
          Send_CCD();  
          Send_Variable();   //Variable是运行参数  Parameter是设定参数
          Read_Switch();      //开关按键扫描
       }
       
       if(new_img)  //此段不超过0.5ms 200ms主频  6ms 或8ms 执行一次
      {
        new_img=0;
//        get_edge();   //得到图像的跳边沿
//        Search();    //黑线提取
        //while(new_img == 0);
        SignalGet();    
        Direction_Control();
        Variable_update(); //运行参数
        //Send_Variable();
        
        //led_flash();        //时间太长
      }  
      while(OLED_Refresh && new_img)
      {
        new_img = 0;
        img_extract(img,imgbuff_process,CAMERA_SIZE);   //二值化图像解压，一个数组单元存储一个像素点
        OLED_Draw_UI();            //画出OLED界面
        Read_Switch(); 
        SignalGet();
//        if ((CCDLightCnt != 0 && CCDPosition != 255) && twinkle_Flag <=20)    // 正常情况下
//        {
//            Direction_Control();
//            twinkle_Flag = 0;
//        }
//        else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=20)   //前两次没有拍到图像
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

void PIT0_IRQHandler()  //2ms一次中断
{
    static uint8 flag_100ms,cnt=0; //CCD_cnt=0;
    PIT_Flag_Clear(PIT0);       //清中断标志位
     
    if(!Stop)
    { 
     RunTime=RunTime+0.002;
     AverageSpeed=Distance/RunTime;
    }
    
    flag_100ms++;
    if(flag_100ms>Speed_Filter_Times) //>50
    {
     flag_100ms=0;  
     Speed_Control();  //100ms进行一次速度控制
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
   if(cnt==1)      //4ms运行一次
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
      MotorControl(PID_SPEED.OutLeft,PID_SPEED.OutRight);   //左右电机差速控制
   else;
}

void PIT1_IRQHandler()  //5ms中断一次
{
    PIT_Flag_Clear(PIT1);       //清中断标志位
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
//	PLL_Init(PLL235);//235         //设置内核及总线频率等
//	DisableInterrupts;
//	KEY_SW_Init();               //按键及输入口初始化  
//	//LED_Init();               //LED初始化
//	UART_Init(UART_4,115200); //串口初始化//????
//	//	默认使用:龙邱 OLED SPI模块
//	LCD_Init();               //LCD初始化
//	//LCD_CLS();                //清屏	  
//	LCD_Show_LQLogo();        //显示龙邱LOGO
//	time_delay_ms(500);       //延时  
//	LCD_CLS();                //清屏
//	//time_delay_ms(50);        //延时 
//	//LED_Ctrl(LEDALL, OFF);
//	GPIO_Init(GPIOB,7,GPO,1);
//	GPIO_Init(GPIOC,6,GPI,1);
//	GPIO_Init(GPIOC,7,GPI,1);
//	GPIO_Init(GPIOC,8,GPI,1);
//	GPIO_Init(GPIOC,9,GPI,1);
//	GPIO_Init(GPIOC,2,GPO,1);
//	
//	//电源采集ADC
//	//ADC0_Init();//????
//	//FTM_AB_Init(FTM2);
//	PIT_Init(PIT0, 2);
//	
//	//Servo_Init();          // 初始化舵机
//	//Motor_Init();          //初始化电机
//	MT9V034_Init();         //初始化摄像头
//	
//	//Para_Init();        //补充初始化为已有设定值wk
//	EnableInterrupts;
//	
//	//-----------------------------------------------------------------------------------------  
//	//  测试函数都是死循环，每次只能开启一个
//	//-----------------------------------------------------------------------------------------
//	//Test_ADC0();         //测试ADC采集功能               电磁传感器及电源电压监控 
//	//Test_UART();         //测试UART及中断                蓝牙、USB转TTL调试及通信
//	//Test_LED();          //测试GPIO输出口                LED显示及外设控制        
//	//Test_OLED();         //O测试模拟SPI功能              OLED模块功能   
//	//Test_GPIO_KEY();     //测试GPIO输入                  按键检测功能              
//	//Test_GPIO_EXINT();   //测试GPIO输入及外部中断        按键、中断检测功能  
//	//	Test_Servo();        //数字舵机测试
// 	//Test_Motor();        //直流电机驱动测试，            用龙邱全桥驱动板
//	//Test_9AX();          //测试I2C及龙邱九轴
//	//Test_MPU6050();      //测试I2C及6轴陀螺仪功能
//	//	Test_LQV034();       //OLED显示屏及面阵摄像头动图 
//	//Test_PIT();          //测试PIT定时中断功能
//	//Test_AB_Pulse_Cnt(); //测试编码器正交解码功能
//	//Test_LPTMR_delay();  //测试LPTMR延时功能                
//	//Test_LPTMR_Counter();//测试LPTMR计数功能   
//	//Test_DMA_Counter();  //测试DMA计数功能   
//	//TFTSPI_Test();          //测试龙邱TFT1.8吋SPI彩屏
//	//Test_OLED();  
//	Main_Program();      //主程序
//	//-----------------------------------------------------------------------------------------
//	while(1)
//	{   
//		//LED_Ctrl(LED1, RVS);//反转       
//		//time_delay_ms(500); //延时           
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
////电机控制
//void PIT0_IRQHandler()
//{
//	static uint8 flag_100ms,cnt=0;
//	PIT_Flag_Clear(PIT0);       //清中断标志位
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
//		Speed_Control();  //60ms进行一次速度控制
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
//	if(cnt==1)      //4ms运行一次
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
