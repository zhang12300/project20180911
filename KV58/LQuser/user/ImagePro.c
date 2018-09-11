/******************************************************************************/
/*******************************************************************************
�ļ�����ͼ��������ļ�ImagePro.c
��  �ܣ�ͼ����
��  �ڣ�2018.6.10
��  �ߣ�WZY
��  ע��OV7725 80*60
*******************************************************************************/
/******************************************************************************/

#include "ImagePro.h"
#include "include.h"

int16  SignalPosition;      //�ű�λ�ã�2���˲���
int16  OriginSignalPosition;//�ű��ź�����
uint8  ScanStartLine = 0;	//�ű�������ʼ��   10
uint8  ScanEndLine = 60;	    //�ű�����������
uint8  BWThreshold = 100;	//��ֵ����ֵ
uint8  NoLightLimit =3;     //�ɵ��ű��û������������������
int16  LightCntAvg = 0;     //�Ե������е�ͨ�˲���Ľ��
int16  LightCntAvgPre = 0;
uint8  SignalFirstRow = 0;     //�ű��һ��
uint8  SignalLastRow = 0;      //�ű����һ��
int16  SignalAvgRow = 0;      //�ű� �ź�����
int16  SignalAvgRowPre = 0;
uint8  CCD_Flag;    //��ⲻ���ź�ʱ������CCD�ı�־
uint16  LightCnt = 0;				//�׵����


//uint16 DLightCntAvg = 0;        //�ű�����仯��
uint16 OriginLightCnt = 0;        //��һ�εİ׵���
//uint16 UPBlock[16][2]={{150,190}, {110,230}, {100,240}, {90,250}, {80,260}, {60,280}, {50,290}, {40,300}, {40,300}, {30,310}, {25,320}, {20,320}, {15,320}, {10,320}, {5,320}, {0,320}};
uint16 UPBlock[16][2]={{38,48}, {28,58}, {25,60}, {23,63}, {20,65}, {15,70}, {13,73}, {10,75}, {10,75}, {8,78}, {6,80}, {5,80}, {4,80}, {3,80}, {0,80}, {0,80}};



//uint16 Probe0 = 0;
uint32 Probe2;

//   ��ͨ��������㣬Ȼ���˲�
uint8 Img_Filter(void)
{
 /**  uint8  imgRow = 0;   
   uint8  imgCol = 0;
   uint16 LightCount=0;
   
   for(imgRow = 0; imgRow < 59; imgRow++)
   {
      for(imgCol = 0; imgCol < 10; imgCol++)
      {
          if(imgbuff_process[imgRow*10+imgCol] == 0xff)    //ȫ�ǰ׵�
          {						                       
              LineLightFlag = 1;                               //��λ���������־
              LightCnt=LightCnt+8;
              PositionSum = PositionSum + 64*imgCol + 28;
               RowSum = RowSum + imgRow*8;
          }
          else if(imgbuff_process[imgRow*10+imgCol] == 0x00);     //ȫ�Ǻڵ�
          else 
          {
                    for(n=7;n>=0;n--)
                    {
                      temp=(imgbuff_process[imgRow*10+imgCol]>>n)&1;// ��ȡ�õ�����ֵ ��0��1��     
                      if(temp == 1) //�׵�         
                      {
                           if(LightCnt == 0)
                           {
                              SignalFirstRow = imgRow;
                           }                        
                           LineLightFlag = 1;                               //��λ���������־
                           LightCnt++;
                           PositionSum = PositionSum + 8*imgCol + 7 - n;
                           RowSum += imgRow;
                      }
                     } 
                  }

            }     //�׵�����������
            if(LightCnt !=0 && LineLightFlag == 0 )//֮ǰɨ�赽�׵㣬�׵������ۼ�ֵ��ͻȻĳһ��û��ɨ�赽�׵�
            {   
                  if(NoLightCnt == 0)
                  {
                        SignalLastRow = imgRow;                    
                  }
                  NoLightCnt++;
            }
            if(NoLightCnt >= NoLightLimit)  //��ʱ�˳�������Բ�̷������
            {                 
                  break;
            }         
      }          //�׵�����������  **/
   
}

//======================================================================
//��������SignalGet
//��  �ܣ��ű�λ�û�ȡ����
//��  ������
//��  �أ�1�ɹ� 0ʧ��
//Ӱ  �죺SignalPosition
//˵  ���������Ż��ռ䣬�����ǰһ��λ���޶���һ������λ�ã�ÿ���ѵ�������ʧ�������break
//        ������ʱʱ�����
//======================================================================
uint16 SignalGet(void){
     // Probe2 = PIT_CVAL(0);    
      uint8  imgRow = 0;
      uint16 imgCol = 0;			
      uint32 PositionSum = 0;		        //λ�����
      uint8  LineLightFlag = 0;              //�����������ޱ�־
      uint8  NoLightCnt = 0;                //�ɵ��ű����������������
      //uint16 LightCntAvgPre = 0;
      int32  RowSum = 0;                    //�������
      int16  temp, n;    //һ���ֽ����ȡĳһ�����ص���õ�n
      //int16  BlockUdisRow;
      int16  StartCol = 0, EndCol = 10; //1�е����ص��10���ֽ�
      // uint8  FullFlag = 0;
      //Probe0 = 0;
      
      
      LightCnt = 0;  //��ͼ��׵�������
   //   Img_Filter();   //ͼ���˲�  ������ͨ����� 
      for(imgRow = ScanStartLine ; imgRow < ScanEndLine - 1; imgRow++)
      {
            LineLightFlag = 0;               //�������������־
            for(imgCol = StartCol; imgCol < EndCol; imgCol++)
            {
                  if(imgbuff_process[imgRow*10+imgCol] == 0x00)    //ȫ�ǰ׵�
                  {						
                        if(LightCnt == 0)
                        {
                              SignalFirstRow = imgRow;
                        }                        
                        LineLightFlag = 1;                               //��λ���������־
                        LightCnt=LightCnt+8;
                        PositionSum = PositionSum + 64*imgCol + 28;
                        RowSum = RowSum + imgRow*8;
                        /*		if((PositionSum & 0x8000 != 0)||(LightCnt>200)){		//������������������
                                PositionSum = PositionSum / LightCnt; 
                                  LightCnt = 1;
                           }*/
                  }
                  else if(imgbuff_process[imgRow*10+imgCol] == 0xFF);     //ȫ�Ǻڵ�
                  else 
                  {
                    for(n=7;n>=0;n--)
                    {
                      temp=(imgbuff_process[imgRow*10+imgCol]>>n)&1;// ��ȡ�õ�����ֵ ��0��1��     
                      if(temp == 0) //�׵�         
                      {
                           if(LightCnt == 0)
                           {
                              SignalFirstRow = imgRow;
                           }                        
                           LineLightFlag = 1;                               //��λ���������־
                           LightCnt++;
                           PositionSum = PositionSum + 8*imgCol + 7 - n;
                           RowSum += imgRow;
                      }
                     } 
                  }

            }     //�׵�����������
            if(LightCnt !=0 && LineLightFlag == 0 )//֮ǰɨ�赽�׵㣬�׵������ۼ�ֵ��ͻȻĳһ��û��ɨ�赽�׵�
            {   
                  if(NoLightCnt == 0)
                  {
                        SignalLastRow = imgRow;                    
                  }
                  NoLightCnt++;
            }
            if(NoLightCnt >= NoLightLimit)  //��ʱ�˳�������Բ�̷������
            {                 
                  break;
            }         
      }          //�׵�����������
      

      //Probe2 = PIT_CVAL(0);
      OriginLightCnt = LightCnt;  //����ͷ�������
      
      CCD_pro();  //CCD����
      infrared_succeed = infrared_pro();   //����ɼ����ɹ�����1
       
      if(LightCnt < Camera_threshhold || LightCnt > Camera_threshholdH)   //����ͷ�ɼ�ʧ��   ��־λ����
      {          
            LightCntAvg = 0;
            SignalFirstRow = 0;
            SignalLastRow = 0;
            SignalAvgRow = 0; 
            SignalPosition = 0;  
      }
      else                     //����ͨ������
      {
//            CCD_Flag = 0;
            LightCntAvgPre = LightCntAvg;
            LightCntAvg = ((LightCntLPk - 1)*LightCntAvg +LightCnt) / LightCntLPk;   //LightCntLPk == 4     
            OriginSignalPosition = PositionSum / LightCnt;        //��һ��ͼ�����ƽ��
            
            if(SignalPosition > 0)
            {
                  SignalPosition = (SignalPosition + OriginSignalPosition) / 2;      //������ƽ��
            }
            else
            {
                  SignalPosition = OriginSignalPosition;                 //��ʼΪ0��ʱ��ֱ��ֵOriginSignalPosition
            }
            
            
//            if(SignalPosition > 178)
//            {
//                  
//                  SignalAvgRow = (RowSum * 10) / LightCnt - (SignalPosition - 178) * 6  / 10;
//                  
//            }
//            else if(SignalPosition < 168)
//            {
//                  
//                  SignalAvgRow = (RowSum * 10) / LightCnt - (168 - SignalPosition) * 6 / 10;
//                  
//            }
//            else
//            {
                  
             
                  
//           }
            
            if(SignalAvgRow > 0)
            {
                  temp = SignalAvgRow;
                  SignalAvgRow = RowSum / LightCnt;                  //(RowSum * 10) / LightCnt;
                  SignalAvgRow = (temp * 3 + SignalAvgRow)/4;      //������ƽ��
            }
            else
            {
                  SignalAvgRow = RowSum / LightCnt;                   
            }
//            if(SignalAvgRow > temp){
//                  
//                  SignalAvgRow = (temp * 3 + SignalAvgRow)/4;
//                  
//            }
//            else{
//                  
//                  SignalAvgRow = temp;
//                  
//            }
            
//            if(SignalAvgRow > 150){
//                 // LostDirection = Direction;
//            }
            //            if( ( SignalPosition < 183 && SignalPosition > 163 ) || SignalAvgRow > 200 ){
            //                  
            //                  SignalAvgRow = (RowSum * 10) / LightCnt;
            //                  SignalAvgRow = (temp * 3 + SignalAvgRow)/4;
            //                  
            //            }
            //            
            //SignalPosition = PositionSum / LightCnt;
      }
      return LightCnt;
}