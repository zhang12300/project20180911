#ifndef __ImagePro_H__
#define __ImagePro_H__
/******************************************************************************/
/*******************************************************************************
  �ļ�����ͼ�������ͷ�ļ�IamgePro.h
  ��  �ܣ�ͼ����
  ��  �ڣ�2016.5.12
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
//#include <stdio.h>
#include "common.h"
#include "LQMT9V034.h"
//#include "camera.h"
//#include "ImageGet.h"
//#include "Control.h"

//2. �궨��
#define Failed 255
#define ImageCen 173
#define LightCntLPk 4      //��ͨ�˲�ϵ��

//3. �������Ͷ���

//4. ��������
extern int16  SignalPosition;
extern int16  LightCntAvg;
extern int16  LightCntAvgPre;
//extern uint16 Probe0;
extern uint16  LightCnt;				//�׵����

extern uint8  SignalFirstRow;
extern uint8  SignalLastRow;
extern int16  SignalAvgRow;
//extern int16  DLightCntAvg;
extern uint16 OriginLightCnt;

extern int16  SignalAvgRowPre;
//extern int16  SignalAvgRowTemp[2];
//extern uint8  SignalAvgRowPointer;
extern uint8  CCD_Flag; 

//5. ��������
extern uint16 SignalGet(void);
extern uint8 Img_Filter(void);


#endif //end of __ImagePro_H__