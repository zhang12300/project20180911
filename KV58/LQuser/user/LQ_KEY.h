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
#ifndef __LQ_KEY_H__
#define __LQ_KEY_H__

#include "include.h"
//#define BT_SHOW    PTC7
#define BT_RIGHT_LEFT   PTB20//PTC8
#define BT_UP_DOWN      PTB21//PTC6
//#define BT_DOWN    PTD10//PTC9
#define BT_YES     PTB22
//#define BT_LEFT    PTD12//PTC10

#define SW1      PTC6//PTC12
#define SW2      PTC7//PTC13
#define SW3      PTC8//PTC14
#define SW4      PTC9//PTC15


#define SW1_IN   gpio_get(SW1)
#define SW2_IN   gpio_get(SW2)
#define SW3_IN   gpio_get(SW3)
#define SW4_IN   gpio_get(SW4)

#define BT_SHOW_IN  gpio_get(BT_SHOW)
#define BT_LEFT_IN   gpio_get(BT_LEFT)
#define BT_UP_IN     gpio_get(BT_UP)
#define BT_DOWN_IN   gpio_get(BT_DOWN)
#define BT_YES_IN    gpio_get(BT_YES)
#define BT_RIGHT_IN  gpio_get(BT_RIGHT)

/*******************************************************************************
* Definitions
******************************************************************************/
//����ģ���
typedef enum
{
    KEY0=0,
    KEY1=1,
    KEY2=2,   
} KEYn_e;
typedef enum
{
    LOW=0,  //DOWN
    HIGH=1, //UP  
    FAIL=0xff,
}KEYs_;//e;

extern void TestLED(void);
extern void KEY_SW_Init(void);
extern u8 KEY_Read(KEYn_e keyno);
extern void  Test_GPIO_KEY(void);
extern void  Test_GPIO_EXINT(void);
void water_lights(); 
void led_flash();
#endif 
