#ifndef CCD_H
#define CCD_H


//1. 头文件
//2. 宏定义
//3. 变量类型定义
//4. 变量声明
//5. 函数声明

//1. 头文件
#include "common.h"
#include "control.h"
#include "LQGPIO.h"
#include "LQADC.h"
#include "LQFTM.h"
//#include "MK60_gpio.h"
//#include "MK60_adc.h"
//#include  "MK60_FTM.h"

//2. 宏定义
/****  
    只用一个ccd识别信标灯  
   CCD_CLK    PTD12
   CCD_SI     PTD13
   CCD_AO     ADC0_SE16
                    ****/
//#define CCD1_PORT	PORTD
#define CCD1_SI		PTD8  //PTD13
#define CCD1_CLK	PTD9  //PTD12      
#define	CCD1_ch		ADC0_DP2//HSADC1B_CH11 //ADC0_SE16 PTC8


//3. 变量类型定义

extern uint8 ad1[128];
extern uint8 ad2[128];
extern uint8 CCDSendflag;
extern uint8 ObstacleFlag;
extern uint16 ServoObstacle;

extern uint8 CCD1Threshold;
extern uint8 CCD1LightLimit;
extern uint8 CCD1LowerLimit;
extern uint8 CCD1UpperLimit;
extern uint8 CCD1PositionCen;
extern uint8 BlockCntFrontDefault;
extern uint8 Max_White;

//extern uint8 CCD2Threshold;
//extern uint8 CCD2LightLimit;
//extern uint8 CCD2LowerLimit;
//extern uint8 CCD2UpperLimit;
//extern uint8 CCD2PositionCen;
extern uint8 BlockCntBackDefault;

extern uint8 CCDBlockFlag;
extern uint8 CCDLightCnt ;
extern uint8 CCDPosition ;
extern uint8 BlockCntDefault;

//
extern uint8 BlockCntBackDefaultRight;
extern uint8 BlockCntBackDefaultLeft ;
extern uint8 al ;
extern uint8 bl ;
extern uint8 ar ;
extern uint8 br ;
extern uint8 kl ;
extern uint8 kr ;
extern uint8 BlockCntRightDefault;
extern uint8 BlockCntLeftDefault; 
extern uint8 cl;
extern uint8 cr;
extern uint8 BlockCntFrontDefault;
//4. 变量声明

//5. 函数声明
extern void CCD1_init(void);
extern void CCD1_scan(void);
//extern void CCD2_init(void);
//extern void CCD2_scan(void);
extern void CCD_pro(void);

#endif // end of __CCD_H__