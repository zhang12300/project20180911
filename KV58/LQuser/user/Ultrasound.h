#ifndef __Ultrasound_H__
#define __Ultrasound_H__
/******************************************************************************/
/*******************************************************************************
  文件名：超声波测距头文件SCCB.h
  功  能：超声波测距
  日  期：2016.06.01
  作  者：ZTC
  备  注：
*******************************************************************************/
/******************************************************************************/
//1. 头文件
//2. 宏定义
//3. 变量类型定义
//4. 变量声明
//5. 函数声明

//1. 头文件
#include "common.h"
//#include "sysinit.h"
//#include "vectors.h"
//#include "MK60_gpio.h"
//#include "MK60_PIT.h"
//#include "MK60_uart.h"
#include "include.h"

//2. 宏定义

//超声波Trigger引脚 E10
#define PORT_TRIG_BASE_PTR PORTB_BASE_PTR
#define PORT_TRIG PORTB
#define PIN_TRIG 8
//超声波ECHO引脚1 E11
#define PORT_ECHO_BASE_PTR PORTB_BASE_PTR
#define PORT_ECHO PORTB
#define PIN_ECHO 9
//Trigger信号发送周期（按场中断来控制）
#define USFrameLimit 2

//3. 变量类型定义
typedef enum
{
    US_NOTINIT = 0,
    DistGetStart,				//发了触发脉冲
    DistGetEcho,				//回波上升沿获得
    DistGetFinish,				//回波下降沿获得即采集正确
} USStatusDef;


//4. 变量声明
extern uint8  USFrameCnt;
extern uint32 UStic;
extern uint32 UStoc;
extern uint16  USDistance;
extern uint16 FrontDistance[3];
extern uint8  UartByteCnt;
extern volatile USStatusDef USStatus;

//5. 函数声明
extern void UltrasoundInit();
//extern void Ultrasound2Init();
//void PORTB_IRQHandler();
extern uint8 USTrigger();
extern void USEchoPro();

#endif // end of __SCCB_H__