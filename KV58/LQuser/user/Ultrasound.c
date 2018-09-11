/******************************************************************************/
/*******************************************************************************
文件名：超声波测距文件Ultrasound.c
功  能：超声波测距
日  期：2016.06.01
作  者：ZTC
备  注：
*******************************************************************************/
/******************************************************************************/

#include "Ultrasound.h"

volatile USStatusDef USStatus = US_NOTINIT;   //当前图像状态标志标志位

uint8  USFrameCnt = 0;
uint32 UStic;               //超声波回来的脉冲开始时PIT0的值
uint32 UStoc;               //超声波回来的脉冲结束时PIT0的值
uint16 USDistance = 0;            //测得距离
uint16  FrontDistance[3];      //测得前面距离
uint8  UartByteCnt = 0;




//5. 函数声明
void UltrasoundInit();
//void Ultrasound2Init();
uint8 USTrigger();
void USEchoPro();
void USDelay();


//USDelay函数
//3步 * 60 * 1 = 180 次运算，也就是1us，不一定准。
void USDelay()
{
      int16 ii;
      for(ii=0;ii<3000;ii++);
}

//------------------------------------------------------------------------------
//函数名：UltrasoundInit()
//功  能：超声波初始化
//参  数：无
//返  回：无
//说  明：
//------------------------------------------------------------------------------
void UltrasoundInit(){
      //pit_init(PIT0,70*periph_clk_khz);   		//定时PIT0为70ms
      //pit_init(PIT1,0x7FFFFFFE);					//总时间轴，感觉放到主循环里初始化会比较好
      //enable_pit_interrupt(PIT0);
      
      //超声波TRIG引脚初始化, 定义为输出IO引脚, 默认输出为低电平
//      PORT_PCR_REG(PORT_TRIG_BASE_PTR, PIN_TRIG) |= PORT_PCR_MUX(0x01);    //GPIO
//      GPIO_PDDR_REG(PORT_TRIG) |= (1<<PIN_TRIG);
//      GPIO_PDOR_REG(PORT_TRIG) &= ~(1<<PIN_TRIG);

      GPIO_Init(GPIOB,8,GPO,0);
      
      //超声波ECHO引脚初始化， 默认输入，上升沿和下降沿都触发中断
//      PORT_PCR_REG(PORT_ECHO_BASE_PTR, PIN_ECHO) |= (
//                                                     PORT_PCR_MUX(0x01)    	//GPIO
//                                                           |	PORT_PCR_IRQC(0xA)		//上升沿和下降沿都触发中断
//                                                                 );
      EXTI_Init(GPIOB, 9, falling_down);
      
      
      PORTB_ISFR = PORT_ISFR_ISF_MASK;       //清ECHO所在PORT的标志位
}

////------------------------------------------------------------------------------
////函数名：Ultrasound2Init()
////功  能：超声波初始化
////参  数：无
////返  回：无
////说  明：
////------------------------------------------------------------------------------
//void Ultrasound2Init(){
//      //pit_init(PIT0,70*periph_clk_khz);   		//定时PIT0为70ms
//      //pit_init(PIT1,0x7FFFFFFE);					//总时间轴，感觉放到主循环里初始化会比较好
//      //enable_pit_interrupt(PIT0);
//      
//     uart_init(UART5,periph_clk_khz,9600); 
//     enableuartreint(UART5,55);
//     set_irq_priority(55,2); 
//    
//}
//------------------------------------------------------------------------------
//函数名：USTrigger()
//功  能：超声波触发和距离值更新
//参  数：无
//返  回：	0代表出错
//			1代表正常运行
//说  明：产生约15us脉冲，脉宽与单片机主频有关
//        测距结束或者超过两帧图像（约66ms）进行一次测距
//------------------------------------------------------------------------------
uint8 USTrigger(){
      
      USFrameCnt++;
      if(USStatus == DistGetFinish || USStatus == US_NOTINIT){
//            GPIO_PDOR_REG(PORT_TRIG) |= (1<<PIN_TRIG);
            gpio_set (PTB8, 1); 
            USDelay();
//            GPIO_PDOR_REG(PORT_TRIG) &= ~(1<<PIN_TRIG);
            gpio_set (PTB8, 0); 
//            PIT_TCTRL(PIT2) |= (PIT_TCTRL_TEN_MASK );   //使能 PITn定时器,并开PITn中断           
//            PIT_LDVAL(PIT2)  = 60*29375;
//            PIT_Init(PIT2, 60);//60ms定时中断  超声波
            
            UStic = PIT_CVAL(2);
//            USFrameCnt = 0;
            USStatus = DistGetStart;
//            Dist = (float)(UStic - UStoc);
//            if(UStic<UStoc){
//                  Dist += PIT_LDVAL2;
//            }
//            Dist = 170 * (Dist / PIT_LDVAL2);
//            //if(Dist>100)   Dist=100;
//            USDistance = (USDistance*1+(int16)Dist*4)/5;
            
      }
//      else if(USFrameCnt >= USFrameLimit){
////            GPIO_PDOR_REG(PORT_TRIG) |= (1<<PIN_TRIG);
//            gpio_set (PTB8, 1); 
//            USDelay();
////            GPIO_PDOR_REG(PORT_TRIG) &= ~(1<<PIN_TRIG);
//            gpio_set (PTB8, 0); 
//            USFrameCnt = 0;
//            USStatus = DistGetStart;
//            
//            //uart_sendN(UART0, (uint8 *)"\nError In USTrigger()!", 22);  //错误警报
//      }
      else{}
//      while((GPIO_PDIR_REG(PORTE)&(1<<11))==0);
//      UStic = PIT_CVAL(2);
//      set_irq_priority(91,1);
//      enable_irq(ECHO_IRQ);                 //ECHO中断IRQ
      return 1;
}
//------------------------------------------------------------------------------
//函数名：USEchoPro()
//功  能：超声波回波处理
//参  数：无
//返  回：无
//说  明：
//------------------------------------------------------------------------------
//void USEchoPro(){
void PORTB_IRQHandler(void) 
{
       float Dist;
	//PTB9
	if((PORTB_ISFR & 0x200))//场中断 PTD14 (1<<14)
	{
		PORTB_ISFR |= 0x200;  //清除中断标识    
		// 用户程序 
	}
        
        if(USStatus == DistGetStart)
        {
//          UStic = PIT_CVAL(2);
//          USStatus == DistGetEcho;
           UStoc = PIT_CVAL(2);
//           PIT_TCTRL(PIT2) &= (~PIT_TCTRL_TEN_MASK );   //禁止PITn定时器,
           USStatus = DistGetFinish;
           Dist = (float)(UStic - UStoc);
           if(UStic<UStoc){
                  Dist += PIT_LDVAL2;
            }
            Dist = 1020 * (Dist / PIT_LDVAL2);
            //if(Dist>100)   Dist=100;
            USDistance = (USDistance*1+(int16)Dist*4)/5;
        }
//        else if(USStatus == DistGetEcho)
//        {
//          UStoc = PIT_CVAL(2);
//          USStatus = DistGetFinish;
          if(infrared_succeed == 1 )  
            USTrigger();
//        }
} 

