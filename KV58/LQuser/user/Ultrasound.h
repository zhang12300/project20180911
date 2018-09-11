#ifndef __Ultrasound_H__
#define __Ultrasound_H__
/******************************************************************************/
/*******************************************************************************
  �ļ��������������ͷ�ļ�SCCB.h
  ��  �ܣ����������
  ��  �ڣ�2016.06.01
  ��  �ߣ�ZTC
  ��  ע��
*******************************************************************************/
/******************************************************************************/
//1. ͷ�ļ�
//2. �궨��
//3. �������Ͷ���
//4. ��������
//5. ��������

//1. ͷ�ļ�
#include "common.h"
//#include "sysinit.h"
//#include "vectors.h"
//#include "MK60_gpio.h"
//#include "MK60_PIT.h"
//#include "MK60_uart.h"
#include "include.h"

//2. �궨��

//������Trigger���� E10
#define PORT_TRIG_BASE_PTR PORTB_BASE_PTR
#define PORT_TRIG PORTB
#define PIN_TRIG 8
//������ECHO����1 E11
#define PORT_ECHO_BASE_PTR PORTB_BASE_PTR
#define PORT_ECHO PORTB
#define PIN_ECHO 9
//Trigger�źŷ������ڣ������ж������ƣ�
#define USFrameLimit 2

//3. �������Ͷ���
typedef enum
{
    US_NOTINIT = 0,
    DistGetStart,				//���˴�������
    DistGetEcho,				//�ز������ػ��
    DistGetFinish,				//�ز��½��ػ�ü��ɼ���ȷ
} USStatusDef;


//4. ��������
extern uint8  USFrameCnt;
extern uint32 UStic;
extern uint32 UStoc;
extern uint16  USDistance;
extern uint16 FrontDistance[3];
extern uint8  UartByteCnt;
extern volatile USStatusDef USStatus;

//5. ��������
extern void UltrasoundInit();
//extern void Ultrasound2Init();
//void PORTB_IRQHandler();
extern uint8 USTrigger();
extern void USEchoPro();

#endif // end of __SCCB_H__