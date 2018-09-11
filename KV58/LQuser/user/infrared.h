/*!
 * @file       LED.h
 * @brief      ���ⳣ�ú���ͷ�ļ�
 */

#ifndef _INFRARED_H_
#define _INFRARED_H_

#define inf0     PTC12  //PTE9     ���
#define inf1     PTC13  //PTE10    ��
#define inf2     PTC14  //PTE11    ��ǰ
#define inf3     PTC15  //PTE12    ǰ
#define inf4     PTD0  //PTC5      ��ǰ 
#define inf5     PTD1  //PTC4      ��
#define inf6     PTD2  //PTC3     �Һ�
#define inf7     PTD3  //PTC2     ��

extern int inf0_data;
extern int inf1_data;
extern int inf2_data;
extern int inf3_data;
extern int inf4_data;
extern int inf5_data;
extern int inf6_data;
extern int inf7_data;



//#define BT_LEFT_IN   gpio_get(BT_LEFT)
//#define BT_UP_IN     gpio_get(BT_UP)
//#define BT_DOWN_IN   gpio_get(BT_DOWN)
//#define BT_YES_IN    gpio_get(BT_YES)
//#define BT_RIGHT_IN  gpio_get(BT_RIGHT)

void infrared_init();
int infrared_pro();

#endif /* _LED_H_ */