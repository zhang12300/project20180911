#include "CCD.h"
#include "include.h"



uint8 ad1[128];
//uint8 ad2[128];
uint8 CCDSendflag = 0;
uint8 CCDLightCnt = 0;
uint8 CCDPosition = 0;

uint8  ObstacleFlag = 0;
uint16 ServoObstacle;

uint8 Max_White = 0;    //记录CCD白列像素最大值

uint8  CCD1Threshold = 40;   //16ms-60  100ms-160  40
uint8  CCD1LightLimit = 3;
uint8  CCD1LowerLimit = 20;
uint8  CCD1UpperLimit = 100;
uint8  CCD1PositionCen = 66;

//uint8  CCD2Threshold = 30;
//uint8  CCD2LightLimit = 3;
//uint8  CCD2LowerLimit = 24;
//uint8  CCD2UpperLimit = 112;
//uint8  CCD2PositionCen = 60;

uint8  CCDBlockFlag = 1;

uint8  BlockCnt;
uint8  BlockCntFrontDefault = 12;
uint8  BlockCntBackDefault = 8 ;


uint8 BlockCntBackDefaultRight = 12;
uint8 BlockCntBackDefaultLeft = 5;
uint8 al = 6;
uint8 bl = 10;
uint8 ar = 10;
uint8 br = 8;
uint8 kl = 2;
uint8 kr = 4 ;
uint8 cl = 10;
uint8 cr = 10;

uint8 dl = 10;
uint8 dr = 10;
uint8 BlockCntRightDefault = 12 ;
uint8 BlockCntLeftDefault = 12;


//------------------------------------------------------------------------------
//函数名: CCD1_init()
//功  能: CCD初始化
//
//输  入: 无
//
//输  出: 无
//
//作  者: 2016/7/6, by XZX
//------------------------------------------------------------------------------
void CCD1_init(void)
{
//      gpio_init(CCD1_PORT, CCD1_SI, 1, 0);						//CCD1初始化
//      gpio_init(CCD1_PORT, CCD1_CLK, 1, 0);
//      gpio_init(CCD1_SI, GPO, 0); 
//      gpio_init(CCD1_CLK, GPO, 0); 
      GPIO_Init(GPIOD, 8, 1, 0);
      GPIO_Init(GPIOD, 9, 1, 0);
      CCDLightCnt = 0;
      CCDPosition = 0;
      
//      adc_init(CCD1_ch);                                      //ad初始化
      ADC0_Init();
}

//------------------------------------------------------------------------------
//函数名: CCD2_init()
//功  能: CCD初始化
//
//输  入: 无
//
//输  出: 无
//
//作  者: 2016/7/6, by XZX
//------------------------------------------------------------------------------
//void CCD2_init(void)
//{
//      gpio_init(CCD2_PORT, CCD2_SI, 1, 0);						//CCD2初始化   只用了一个ccd，ccd2注释
//      gpio_init(CCD2_PORT, CCD2_CLK, 1, 0);
//      
//      CCDLightCnt = 0;
//      CCDPosition = 0;
//      
//      adc_init(CCD2_ch);
//}

//------------------------------------------------------------------------------
//函数名: CCD1_scan()
//功  能: CCD1扫描，完毕时，scan_ok置1
//
//输  入: 无
//
//输  出: 无
//
//作  者: 2016/7/6, by XZX
//------------------------------------------------------------------------------
void CCD1_scan(void)
{      
      gpio_set(CCD1_SI, 1);
      gpio_set(CCD1_CLK, 1);
      gpio_set(CCD1_SI, 0);
      for(int i = 0; i < 128; ++i)
      {
//            ad1[i] = adc_once(CCD1_ch, ADC_8bit);
            ad1[i] = ADC0_Once(CCD1_ch,ADC_8bit);
            gpio_set(CCD1_CLK, 0);
            gpio_set(CCD1_CLK, 1);
      }
      gpio_set(CCD1_CLK, 0);
      
}

//------------------------------------------------------------------------------
//函数名: CCD2_scan()
//功  能: CCD2扫描，完毕时，scan_ok置1
//
//输  入: 无
//
//输  出: 无
//
//作  者: 2016/7/6, by XZX
//------------------------------------------------------------------------------
//void CCD2_scan(void)
//{
//      gpio_ctrl(CCD2_PORT, CCD2_SI, 1);  
//      gpio_ctrl(CCD2_PORT, CCD2_CLK, 1);
//      gpio_ctrl(CCD2_PORT, CCD2_SI, 0);  
//      for(int i = 0; i < 128; ++i)
//      {
//            ad2[i] = adc_once(CCD2_ch, CCD2_nu, 8);	
//            gpio_ctrl(CCD2_PORT, CCD2_CLK, 0);
//            gpio_ctrl(CCD2_PORT, CCD2_CLK, 1);
//      }
//      gpio_ctrl(CCD2_PORT, CCD2_CLK, 0);
//      
//}

//------------------------------------------------------------------------------
//函数名: CCD_pro()
//功  能: CCD处理，完毕时，scan_ok置1
//
//输  入: 无
//
//输  出: 无
//
//作  者: 2016/7/6, by XZX
//------------------------------------------------------------------------------
void CCD_pro(void)
{
      uint8 i, Cnt;
      uint16 CCDPositionSum = 0;
      uint8 CCD_position[128] = 255;
      uint8 CCD_tubian = 8;  //16ms-30 100ms 50
      CCDLightCnt = 0;
      //二值化处理        
      for(i=0;i<128;i++)
      {            
         if(ad1[i] > CCD1Threshold)//CCD1Threshold = 60;
         {   
              CCD_position[CCDLightCnt] = i;    //记录满足要求点的坐标
              CCDLightCnt++;
              CCDPositionSum += i;               
         }             
      }
      Cnt = CCDLightCnt;
      for(i=0;i<CCDLightCnt;i++)  
      {
         if(CCD_position[i] == 0)
         {
            if(CCD_position[i+1] == 1);
            else 
            {
               if(ad1[0]-ad1[1] < CCD_tubian)    //说明不是灰度值突变
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - 0; 
               }
            }
              
         }
         else if (CCD_position[i] == 127)
         {
            if(CCD_position[i-1] == 126);
            else 
            {
               if(ad1[127]-ad1[126] < CCD_tubian)    //说明不是灰度值突变
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - 127; 
               }
            }
         }
         else 
         {
            if(CCD_position[i+1] == CCD_position[i] +1 && CCD_position[i-1] == CCD_position[i]-1);  //符合条件的中间列
            else if(CCD_position[i+1] == CCD_position[i] +1 && CCD_position[i-1] != CCD_position[i]-1)     //符合条件的左边界
            {
              if(ad1[CCD_position[i]]-ad1[CCD_position[i]-1] < CCD_tubian)    //说明不是灰度值突变
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - CCD_position[i]; 
               }
            }
            else if(CCD_position[i+1] != CCD_position[i] +1 && CCD_position[i-1] == CCD_position[i]-1)   //符合条件的右边界
            {
                if(ad1[CCD_position[i]]-ad1[CCD_position[i]+1] < CCD_tubian)    //说明不是灰度值突变
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - CCD_position[i]; 
               }
            }
            else  //孤立列
            {
                if(ad1[CCD_position[i]]-ad1[CCD_position[i]+1] < CCD_tubian || ad1[CCD_position[i]]-ad1[CCD_position[i]-1] < CCD_tubian)    //说明不是灰度值突变
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - CCD_position[i]; 
               }
            }
         }
      }
        CCDLightCnt = Cnt;
       
      Max_White = 0;
      for(i=0;i<CCDLightCnt;i++)
      {
         if(ad1[CCD_position[i]] > Max_White)
           Max_White = ad1[CCD_position[i]] ;
      }
        if( CCDLightCnt > 120)
       {   //全白说明有问题，不应该全部白
        CCDLightCnt = 0; 
        CCDPosition = 255;   //无效值255
        //CCD_Flag = 0;
       }
       else
        CCDPosition=CCDPositionSum/CCDLightCnt;
      
      
      
      //右转避障判断条件: 标志位为0，即只有第一次检测到才避障；亮灯点数判断，防止过于接近目标灯；CCD点数判断；CCD位置判断
      
   /***   if(  (ObstacleFlag ==0) && (Direction == RIGHT) && (SignalAvgRow < 170) && (CCDLightCnt > CCD1LightLimit) && (CCDPosition > CCD1LowerLimit) && (CCDPosition <CCD1UpperLimit))
      {
            
            ObstacleFlag = 1;
            
            //根据速度确定具体的打脚值
            
            if( SpeedNow <250){
               
                cl = 10;
                cr = 10;
                BlockCntRightDefault = 10;
               
            }
            else if(SpeedNow <275 ){
              
                 cl = 8;
                 cr = 8;
                 BlockCntRightDefault = 10;
                 
            }
            else{
              
                 cl = 7;
                 cr = 7;
                 BlockCntRightDefault = 10;
                 
            }
          
            
            //CCD位置在右边，向左打角避障
            
            if(CCDPosition < CCD1PositionCen ){      
                  
                  ServoObstacle=ForeServoPIDCen * (10 - cl) / 10 + ServoPIDMin * cl /10;
                  
            }
            else {                                  //CCD位置在左边，向右打角避障
                  
                  ServoObstacle=ForeServoPIDCen * (10 - cr) / 10 + ServoPIDMax * cr /10;
                  
            }
            
            BlockCnt=BlockCntRightDefault;
            
      }
      
      
      //左转避障判断条件: 标志位为0，即只有第一次检测到才避障；；亮灯点数判断，防止过于接近目标灯；CCD点数判断；CCD位置判断
      
      if(  (ObstacleFlag ==0) &&  (Direction == LEFT) && (SignalAvgRow < 170) && (CCDLightCnt > CCD2LightLimit) && (CCDPosition > CCD2LowerLimit) && (CCDPosition <CCD2UpperLimit))
      {
            
            ObstacleFlag = 1;
            
            //根据速度确定具体的打脚值
            
            if( SpeedNow <250){
               
                dl = 10;
                dr = 10;
                BlockCntLeftDefault = 10;
               
            }
            else if(SpeedNow <275 ){
              
                 dl = 8;
                 dr = 8;
                 BlockCntLeftDefault = 10;
                 
            }
            else{
              
                 dl = 7;
                 dr = 7;
                 BlockCntLeftDefault = 10;
                 
            }
            
            
            //CCD位置在左边，向右避障，向右打角
            if(CCDPosition < CCD2PositionCen ){       
                  
                  ServoObstacle=ForeServoPIDCen * (10 - dr) / 10 + ServoPIDMax * dr /10;
                  
                  
            }
            else {                                    //CCD位置在右边，向左避障，向左打角
                  
                  ServoObstacle=ForeServoPIDCen * (10 - dl) / 10 + ServoPIDMin * dl /10;
                  
            }
            
            BlockCnt=BlockCntLeftDefault;
            
      }
      
      
      
      
      if(BlockCnt>0){ 
            
            BlockCnt--;
            
//            if(Direction == RIGHT){                             //右转路径避障打角
//                  
//                  
            if( SpeedNow > 300 )  {
              SpeedPre = SpeedSet;
              SpeedSet = 300;
              
            }
                  ServoPWM = ( ServoPWM * 3 +  ServoObstacle *  2 ) /5;
                  
                  FTM1_C0V = ServoPWM ;
                  
                  
//            }else{                                        //后向避障打角
//                  
//                  if( ServoObstacle < ForeServoPIDCen && BlockCnt < ( BlockCntBackDefaultRight / kr )){   //向右避障第二阶段缓冲打角
//                        
//                        ServoObstacle = ServoObstacle * br /10 + ForeServoPIDCen * (10 - br) / 10 ;
//                        
//                  }
//                  
//                  if( ServoObstacle > ForeServoPIDCen && BlockCnt < ( BlockCntBackDefaultLeft / kl )){   //向左避障第二阶段缓冲打角
//                        
//                        ServoObstacle = ServoObstacle * bl /10 + ForeServoPIDCen * (10 - bl) / 10 ;
//                        
//                  }
//                  
//                  ServoPWM = ( ServoPWM * 3+  ServoObstacle * 2 ) / 5;
//                  
//                  FTM1_C0V = ServoPWM ;
//                  
//            }
            
            
            
      }else if(BlockCnt == 0 && Direction == RIGHT && SignalAvgRow < 180 && LightCntAvg < 53 && CCDLightCnt > CCD1LightLimit && CCDPosition > CCD1LowerLimit && CCDPosition <CCD1UpperLimit){
            
            //BlockCnt清零后判断是否还有障碍，标志位不清零
            
            BlockCnt=BlockCntRightDefault;
            
            
      }else if(BlockCnt == 0 && Direction == LEFT && SignalAvgRow < 180 && LightCntAvg  < 53 && CCDLightCnt > CCD2LightLimit && CCDPosition > CCD2LowerLimit && CCDPosition <CCD2UpperLimit){
            
            //BlockCnt清零后判断是否还有障碍，标志位不清零
            
            BlockCnt = BlockCntLeftDefault;
            
      }else{
            
            ObstacleFlag=0;
            
      }  ***/
      
      
}