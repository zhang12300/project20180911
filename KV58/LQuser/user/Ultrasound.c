/******************************************************************************/
/*******************************************************************************
�ļ���������������ļ�Ultrasound.c
��  �ܣ����������
��  �ڣ�2016.06.01
��  �ߣ�ZTC
��  ע��
*******************************************************************************/
/******************************************************************************/

#include "Ultrasound.h"

volatile USStatusDef USStatus = US_NOTINIT;   //��ǰͼ��״̬��־��־λ

uint8  USFrameCnt = 0;
uint32 UStic;               //���������������忪ʼʱPIT0��ֵ
uint32 UStoc;               //�������������������ʱPIT0��ֵ
uint16 USDistance = 0;            //��þ���
uint16  FrontDistance[3];      //���ǰ�����
uint8  UartByteCnt = 0;




//5. ��������
void UltrasoundInit();
//void Ultrasound2Init();
uint8 USTrigger();
void USEchoPro();
void USDelay();


//USDelay����
//3�� * 60 * 1 = 180 �����㣬Ҳ����1us����һ��׼��
void USDelay()
{
      int16 ii;
      for(ii=0;ii<3000;ii++);
}

//------------------------------------------------------------------------------
//��������UltrasoundInit()
//��  �ܣ���������ʼ��
//��  ������
//��  �أ���
//˵  ����
//------------------------------------------------------------------------------
void UltrasoundInit(){
      //pit_init(PIT0,70*periph_clk_khz);   		//��ʱPIT0Ϊ70ms
      //pit_init(PIT1,0x7FFFFFFE);					//��ʱ���ᣬ�о��ŵ���ѭ�����ʼ����ȽϺ�
      //enable_pit_interrupt(PIT0);
      
      //������TRIG���ų�ʼ��, ����Ϊ���IO����, Ĭ�����Ϊ�͵�ƽ
//      PORT_PCR_REG(PORT_TRIG_BASE_PTR, PIN_TRIG) |= PORT_PCR_MUX(0x01);    //GPIO
//      GPIO_PDDR_REG(PORT_TRIG) |= (1<<PIN_TRIG);
//      GPIO_PDOR_REG(PORT_TRIG) &= ~(1<<PIN_TRIG);

      GPIO_Init(GPIOB,8,GPO,0);
      
      //������ECHO���ų�ʼ���� Ĭ�����룬�����غ��½��ض������ж�
//      PORT_PCR_REG(PORT_ECHO_BASE_PTR, PIN_ECHO) |= (
//                                                     PORT_PCR_MUX(0x01)    	//GPIO
//                                                           |	PORT_PCR_IRQC(0xA)		//�����غ��½��ض������ж�
//                                                                 );
      EXTI_Init(GPIOB, 9, falling_down);
      
      
      PORTB_ISFR = PORT_ISFR_ISF_MASK;       //��ECHO����PORT�ı�־λ
}

////------------------------------------------------------------------------------
////��������Ultrasound2Init()
////��  �ܣ���������ʼ��
////��  ������
////��  �أ���
////˵  ����
////------------------------------------------------------------------------------
//void Ultrasound2Init(){
//      //pit_init(PIT0,70*periph_clk_khz);   		//��ʱPIT0Ϊ70ms
//      //pit_init(PIT1,0x7FFFFFFE);					//��ʱ���ᣬ�о��ŵ���ѭ�����ʼ����ȽϺ�
//      //enable_pit_interrupt(PIT0);
//      
//     uart_init(UART5,periph_clk_khz,9600); 
//     enableuartreint(UART5,55);
//     set_irq_priority(55,2); 
//    
//}
//------------------------------------------------------------------------------
//��������USTrigger()
//��  �ܣ������������;���ֵ����
//��  ������
//��  �أ�	0�������
//			1������������
//˵  ��������Լ15us���壬�����뵥Ƭ����Ƶ�й�
//        ���������߳�����֡ͼ��Լ66ms������һ�β��
//------------------------------------------------------------------------------
uint8 USTrigger(){
      
      USFrameCnt++;
      if(USStatus == DistGetFinish || USStatus == US_NOTINIT){
//            GPIO_PDOR_REG(PORT_TRIG) |= (1<<PIN_TRIG);
            gpio_set (PTB8, 1); 
            USDelay();
//            GPIO_PDOR_REG(PORT_TRIG) &= ~(1<<PIN_TRIG);
            gpio_set (PTB8, 0); 
//            PIT_TCTRL(PIT2) |= (PIT_TCTRL_TEN_MASK );   //ʹ�� PITn��ʱ��,����PITn�ж�           
//            PIT_LDVAL(PIT2)  = 60*29375;
//            PIT_Init(PIT2, 60);//60ms��ʱ�ж�  ������
            
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
//            //uart_sendN(UART0, (uint8 *)"\nError In USTrigger()!", 22);  //���󾯱�
//      }
      else{}
//      while((GPIO_PDIR_REG(PORTE)&(1<<11))==0);
//      UStic = PIT_CVAL(2);
//      set_irq_priority(91,1);
//      enable_irq(ECHO_IRQ);                 //ECHO�ж�IRQ
      return 1;
}
//------------------------------------------------------------------------------
//��������USEchoPro()
//��  �ܣ��������ز�����
//��  ������
//��  �أ���
//˵  ����
//------------------------------------------------------------------------------
//void USEchoPro(){
void PORTB_IRQHandler(void) 
{
       float Dist;
	//PTB9
	if((PORTB_ISFR & 0x200))//���ж� PTD14 (1<<14)
	{
		PORTB_ISFR |= 0x200;  //����жϱ�ʶ    
		// �û����� 
	}
        
        if(USStatus == DistGetStart)
        {
//          UStic = PIT_CVAL(2);
//          USStatus == DistGetEcho;
           UStoc = PIT_CVAL(2);
//           PIT_TCTRL(PIT2) &= (~PIT_TCTRL_TEN_MASK );   //��ֹPITn��ʱ��,
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

