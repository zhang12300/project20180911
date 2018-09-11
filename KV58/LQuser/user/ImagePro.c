/******************************************************************************/
/*******************************************************************************
文件名：图像处理程序文件ImagePro.c
功  能：图像处理
日  期：2018.6.10
作  者：WZY
备  注：OV7725 80*60
*******************************************************************************/
/******************************************************************************/

#include "ImagePro.h"
#include "include.h"

int16  SignalPosition;      //信标位置（2次滤波）
int16  OriginSignalPosition;//信标信号列数
uint8  ScanStartLine = 0;	//信标搜索起始行   10
uint8  ScanEndLine = 60;	    //信标搜索结束行
uint8  BWThreshold = 100;	//二值化阈值
uint8  NoLightLimit =3;     //采到信标后没有亮点跳出行数上限
int16  LightCntAvg = 0;     //对点数进行低通滤波后的结果
int16  LightCntAvgPre = 0;
uint8  SignalFirstRow = 0;     //信标第一行
uint8  SignalLastRow = 0;      //信标最后一行
int16  SignalAvgRow = 0;      //信标 信号行数
int16  SignalAvgRowPre = 0;
uint8  CCD_Flag;    //检测不到信号时，启用CCD的标志
uint16  LightCnt = 0;				//白点计数


//uint16 DLightCntAvg = 0;        //信标点数变化量
uint16 OriginLightCnt = 0;        //上一次的白点数
//uint16 UPBlock[16][2]={{150,190}, {110,230}, {100,240}, {90,250}, {80,260}, {60,280}, {50,290}, {40,300}, {40,300}, {30,310}, {25,320}, {20,320}, {15,320}, {10,320}, {5,320}, {0,320}};
uint16 UPBlock[16][2]={{38,48}, {28,58}, {25,60}, {23,63}, {20,65}, {15,70}, {13,73}, {10,75}, {10,75}, {8,78}, {6,80}, {5,80}, {4,80}, {3,80}, {0,80}, {0,80}};



//uint16 Probe0 = 0;
uint32 Probe2;

//   连通域面积计算，然后滤波
uint8 Img_Filter(void)
{
 /**  uint8  imgRow = 0;   
   uint8  imgCol = 0;
   uint16 LightCount=0;
   
   for(imgRow = 0; imgRow < 59; imgRow++)
   {
      for(imgCol = 0; imgCol < 10; imgCol++)
      {
          if(imgbuff_process[imgRow*10+imgCol] == 0xff)    //全是白点
          {						                       
              LineLightFlag = 1;                               //置位行内亮点标志
              LightCnt=LightCnt+8;
              PositionSum = PositionSum + 64*imgCol + 28;
               RowSum = RowSum + imgRow*8;
          }
          else if(imgbuff_process[imgRow*10+imgCol] == 0x00);     //全是黑点
          else 
          {
                    for(n=7;n>=0;n--)
                    {
                      temp=(imgbuff_process[imgRow*10+imgCol]>>n)&1;// 获取该点像素值 （0或1）     
                      if(temp == 1) //白点         
                      {
                           if(LightCnt == 0)
                           {
                              SignalFirstRow = imgRow;
                           }                        
                           LineLightFlag = 1;                               //置位行内亮点标志
                           LightCnt++;
                           PositionSum = PositionSum + 8*imgCol + 7 - n;
                           RowSum += imgRow;
                      }
                     } 
                  }

            }     //白点列搜索结束
            if(LightCnt !=0 && LineLightFlag == 0 )//之前扫描到白点，白点数有累计值，突然某一行没有扫描到白点
            {   
                  if(NoLightCnt == 0)
                  {
                        SignalLastRow = imgRow;                    
                  }
                  NoLightCnt++;
            }
            if(NoLightCnt >= NoLightLimit)  //及时退出，避免圆盘反射干扰
            {                 
                  break;
            }         
      }          //白点行搜索结束  **/
   
}

//======================================================================
//函数名：SignalGet
//功  能：信标位置获取函数
//参  数：无
//返  回：1成功 0失败
//影  响：SignalPosition
//说  明：仍有优化空间，如根据前一行位置限定下一行搜索位置，每行搜到亮点消失几个点后break
//        但是暂时时间充足
//======================================================================
uint16 SignalGet(void){
     // Probe2 = PIT_CVAL(0);    
      uint8  imgRow = 0;
      uint16 imgCol = 0;			
      uint32 PositionSum = 0;		        //位置求和
      uint8  LineLightFlag = 0;              //行内亮点有无标志
      uint8  NoLightCnt = 0;                //采到信标后无亮点行数计数
      //uint16 LightCntAvgPre = 0;
      int32  RowSum = 0;                    //行数求和
      int16  temp, n;    //一个字节里获取某一个像素点会用到n
      //int16  BlockUdisRow;
      int16  StartCol = 0, EndCol = 10; //1行的像素点存10个字节
      // uint8  FullFlag = 0;
      //Probe0 = 0;
      
      
      LightCnt = 0;  //新图像白点数清零
   //   Img_Filter();   //图像滤波  搜索连通域面积 
      for(imgRow = ScanStartLine ; imgRow < ScanEndLine - 1; imgRow++)
      {
            LineLightFlag = 0;               //清零行内亮点标志
            for(imgCol = StartCol; imgCol < EndCol; imgCol++)
            {
                  if(imgbuff_process[imgRow*10+imgCol] == 0x00)    //全是白点
                  {						
                        if(LightCnt == 0)
                        {
                              SignalFirstRow = imgRow;
                        }                        
                        LineLightFlag = 1;                               //置位行内亮点标志
                        LightCnt=LightCnt+8;
                        PositionSum = PositionSum + 64*imgCol + 28;
                        RowSum = RowSum + imgRow*8;
                        /*		if((PositionSum & 0x8000 != 0)||(LightCnt>200)){		//求和溢出或计数溢出处理
                                PositionSum = PositionSum / LightCnt; 
                                  LightCnt = 1;
                           }*/
                  }
                  else if(imgbuff_process[imgRow*10+imgCol] == 0xFF);     //全是黑点
                  else 
                  {
                    for(n=7;n>=0;n--)
                    {
                      temp=(imgbuff_process[imgRow*10+imgCol]>>n)&1;// 获取该点像素值 （0或1）     
                      if(temp == 0) //白点         
                      {
                           if(LightCnt == 0)
                           {
                              SignalFirstRow = imgRow;
                           }                        
                           LineLightFlag = 1;                               //置位行内亮点标志
                           LightCnt++;
                           PositionSum = PositionSum + 8*imgCol + 7 - n;
                           RowSum += imgRow;
                      }
                     } 
                  }

            }     //白点列搜索结束
            if(LightCnt !=0 && LineLightFlag == 0 )//之前扫描到白点，白点数有累计值，突然某一行没有扫描到白点
            {   
                  if(NoLightCnt == 0)
                  {
                        SignalLastRow = imgRow;                    
                  }
                  NoLightCnt++;
            }
            if(NoLightCnt >= NoLightLimit)  //及时退出，避免圆盘反射干扰
            {                 
                  break;
            }         
      }          //白点行搜索结束
      

      //Probe2 = PIT_CVAL(0);
      OriginLightCnt = LightCnt;  //摄像头处理结束
      
      CCD_pro();  //CCD处理
      infrared_succeed = infrared_pro();   //红外采集，成功返回1
       
      if(LightCnt < Camera_threshhold || LightCnt > Camera_threshholdH)   //摄像头采集失败   标志位清零
      {          
            LightCntAvg = 0;
            SignalFirstRow = 0;
            SignalLastRow = 0;
            SignalAvgRow = 0; 
            SignalPosition = 0;  
      }
      else                     //求连通域中心
      {
//            CCD_Flag = 0;
            LightCntAvgPre = LightCntAvg;
            LightCntAvg = ((LightCntLPk - 1)*LightCntAvg +LightCnt) / LightCntLPk;   //LightCntLPk == 4     
            OriginSignalPosition = PositionSum / LightCnt;        //这一幅图像的列平均
            
            if(SignalPosition > 0)
            {
                  SignalPosition = (SignalPosition + OriginSignalPosition) / 2;      //两次求平均
            }
            else
            {
                  SignalPosition = OriginSignalPosition;                 //初始为0的时候，直接值OriginSignalPosition
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
                  SignalAvgRow = (temp * 3 + SignalAvgRow)/4;      //两次求平均
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