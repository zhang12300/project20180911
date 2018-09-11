#ifndef __ImagePro_H__
#define __ImagePro_H__
/******************************************************************************/
/*******************************************************************************
  文件名：图像处理程序头文件IamgePro.h
  功  能：图像处理
  日  期：2016.5.12
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
//#include <stdio.h>
#include "common.h"
#include "LQMT9V034.h"
//#include "camera.h"
//#include "ImageGet.h"
//#include "Control.h"

//2. 宏定义
#define Failed 255
#define ImageCen 173
#define LightCntLPk 4      //低通滤波系数

//3. 变量类型定义

//4. 变量声明
extern int16  SignalPosition;
extern int16  LightCntAvg;
extern int16  LightCntAvgPre;
//extern uint16 Probe0;
extern uint16  LightCnt;				//白点计数

extern uint8  SignalFirstRow;
extern uint8  SignalLastRow;
extern int16  SignalAvgRow;
//extern int16  DLightCntAvg;
extern uint16 OriginLightCnt;

extern int16  SignalAvgRowPre;
//extern int16  SignalAvgRowTemp[2];
//extern uint8  SignalAvgRowPointer;
extern uint8  CCD_Flag; 

//5. 函数声明
extern uint16 SignalGet(void);
extern uint8 Img_Filter(void);


#endif //end of __ImagePro_H__