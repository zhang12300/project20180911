/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��12��15��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��120.000MHz
��pllclock��240.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_LED_H__
#define __LQ_LED_H__

#include "include.h"


#define LED_RED    PTE30
#define LED_GREEN PTE29
#define LED_BLUE  PTE13

#define LED_GREEN_ON    gpio_set(LED_GREEN,0)
#define LED_GREEN_OFF   gpio_set(LED_GREEN,1)
#define LED_GREEN_TURN  gpio_turn(LED_GREEN)

#define LED_BLUE_ON     gpio_set(LED_BLUE,0)
#define LED_BLUE_OFF    gpio_set(LED_BLUE,1)
#define LED_BLUE_TURN   gpio_turn(LED_BLUE)

#define LED_RED_ON      gpio_set(LED_RED,0)
#define LED_RED_OFF     gpio_set(LED_RED,1)
#define LED_RED_TURN    gpio_turn(LED_RED)
/*******************************************************************************
* Definitions
******************************************************************************/
//����ģ���
typedef enum
{
  LED0=0,
  LED1=1,
  LED2=2,   
  LED3=3,   
  LED4=4,
  LED5=5,
  LEDALL=6,//ȫ���ĸ�   
} LEDn_e;

typedef enum
{
  ON=0,  //��
  OFF=1, //��
  RVS=2, //��ת  
}LEDs_e;

extern void LED_Init(void);
extern void LED_Ctrl(LEDn_e ledno, LEDs_e sta);
extern void Test_LED(void);

#endif 
