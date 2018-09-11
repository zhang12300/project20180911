#include "CCD.h"
#include "include.h"



uint8 ad1[128];
//uint8 ad2[128];
uint8 CCDSendflag = 0;
uint8 CCDLightCnt = 0;
uint8 CCDPosition = 0;

uint8  ObstacleFlag = 0;
uint16 ServoObstacle;

uint8 Max_White = 0;    //��¼CCD�����������ֵ

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
//������: CCD1_init()
//��  ��: CCD��ʼ��
//
//��  ��: ��
//
//��  ��: ��
//
//��  ��: 2016/7/6, by XZX
//------------------------------------------------------------------------------
void CCD1_init(void)
{
//      gpio_init(CCD1_PORT, CCD1_SI, 1, 0);						//CCD1��ʼ��
//      gpio_init(CCD1_PORT, CCD1_CLK, 1, 0);
//      gpio_init(CCD1_SI, GPO, 0); 
//      gpio_init(CCD1_CLK, GPO, 0); 
      GPIO_Init(GPIOD, 8, 1, 0);
      GPIO_Init(GPIOD, 9, 1, 0);
      CCDLightCnt = 0;
      CCDPosition = 0;
      
//      adc_init(CCD1_ch);                                      //ad��ʼ��
      ADC0_Init();
}

//------------------------------------------------------------------------------
//������: CCD2_init()
//��  ��: CCD��ʼ��
//
//��  ��: ��
//
//��  ��: ��
//
//��  ��: 2016/7/6, by XZX
//------------------------------------------------------------------------------
//void CCD2_init(void)
//{
//      gpio_init(CCD2_PORT, CCD2_SI, 1, 0);						//CCD2��ʼ��   ֻ����һ��ccd��ccd2ע��
//      gpio_init(CCD2_PORT, CCD2_CLK, 1, 0);
//      
//      CCDLightCnt = 0;
//      CCDPosition = 0;
//      
//      adc_init(CCD2_ch);
//}

//------------------------------------------------------------------------------
//������: CCD1_scan()
//��  ��: CCD1ɨ�裬���ʱ��scan_ok��1
//
//��  ��: ��
//
//��  ��: ��
//
//��  ��: 2016/7/6, by XZX
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
//������: CCD2_scan()
//��  ��: CCD2ɨ�裬���ʱ��scan_ok��1
//
//��  ��: ��
//
//��  ��: ��
//
//��  ��: 2016/7/6, by XZX
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
//������: CCD_pro()
//��  ��: CCD�������ʱ��scan_ok��1
//
//��  ��: ��
//
//��  ��: ��
//
//��  ��: 2016/7/6, by XZX
//------------------------------------------------------------------------------
void CCD_pro(void)
{
      uint8 i, Cnt;
      uint16 CCDPositionSum = 0;
      uint8 CCD_position[128] = 255;
      uint8 CCD_tubian = 8;  //16ms-30 100ms 50
      CCDLightCnt = 0;
      //��ֵ������        
      for(i=0;i<128;i++)
      {            
         if(ad1[i] > CCD1Threshold)//CCD1Threshold = 60;
         {   
              CCD_position[CCDLightCnt] = i;    //��¼����Ҫ��������
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
               if(ad1[0]-ad1[1] < CCD_tubian)    //˵�����ǻҶ�ֵͻ��
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
               if(ad1[127]-ad1[126] < CCD_tubian)    //˵�����ǻҶ�ֵͻ��
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - 127; 
               }
            }
         }
         else 
         {
            if(CCD_position[i+1] == CCD_position[i] +1 && CCD_position[i-1] == CCD_position[i]-1);  //�����������м���
            else if(CCD_position[i+1] == CCD_position[i] +1 && CCD_position[i-1] != CCD_position[i]-1)     //������������߽�
            {
              if(ad1[CCD_position[i]]-ad1[CCD_position[i]-1] < CCD_tubian)    //˵�����ǻҶ�ֵͻ��
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - CCD_position[i]; 
               }
            }
            else if(CCD_position[i+1] != CCD_position[i] +1 && CCD_position[i-1] == CCD_position[i]-1)   //�����������ұ߽�
            {
                if(ad1[CCD_position[i]]-ad1[CCD_position[i]+1] < CCD_tubian)    //˵�����ǻҶ�ֵͻ��
               {
                  Cnt--;   
                  CCDPositionSum = CCDPositionSum - CCD_position[i]; 
               }
            }
            else  //������
            {
                if(ad1[CCD_position[i]]-ad1[CCD_position[i]+1] < CCD_tubian || ad1[CCD_position[i]]-ad1[CCD_position[i]-1] < CCD_tubian)    //˵�����ǻҶ�ֵͻ��
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
       {   //ȫ��˵�������⣬��Ӧ��ȫ����
        CCDLightCnt = 0; 
        CCDPosition = 255;   //��Чֵ255
        //CCD_Flag = 0;
       }
       else
        CCDPosition=CCDPositionSum/CCDLightCnt;
      
      
      
      //��ת�����ж�����: ��־λΪ0����ֻ�е�һ�μ�⵽�ű��ϣ����Ƶ����жϣ���ֹ���ڽӽ�Ŀ��ƣ�CCD�����жϣ�CCDλ���ж�
      
   /***   if(  (ObstacleFlag ==0) && (Direction == RIGHT) && (SignalAvgRow < 170) && (CCDLightCnt > CCD1LightLimit) && (CCDPosition > CCD1LowerLimit) && (CCDPosition <CCD1UpperLimit))
      {
            
            ObstacleFlag = 1;
            
            //�����ٶ�ȷ������Ĵ��ֵ
            
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
          
            
            //CCDλ�����ұߣ������Ǳ���
            
            if(CCDPosition < CCD1PositionCen ){      
                  
                  ServoObstacle=ForeServoPIDCen * (10 - cl) / 10 + ServoPIDMin * cl /10;
                  
            }
            else {                                  //CCDλ������ߣ����Ҵ�Ǳ���
                  
                  ServoObstacle=ForeServoPIDCen * (10 - cr) / 10 + ServoPIDMax * cr /10;
                  
            }
            
            BlockCnt=BlockCntRightDefault;
            
      }
      
      
      //��ת�����ж�����: ��־λΪ0����ֻ�е�һ�μ�⵽�ű��ϣ������Ƶ����жϣ���ֹ���ڽӽ�Ŀ��ƣ�CCD�����жϣ�CCDλ���ж�
      
      if(  (ObstacleFlag ==0) &&  (Direction == LEFT) && (SignalAvgRow < 170) && (CCDLightCnt > CCD2LightLimit) && (CCDPosition > CCD2LowerLimit) && (CCDPosition <CCD2UpperLimit))
      {
            
            ObstacleFlag = 1;
            
            //�����ٶ�ȷ������Ĵ��ֵ
            
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
            
            
            //CCDλ������ߣ����ұ��ϣ����Ҵ��
            if(CCDPosition < CCD2PositionCen ){       
                  
                  ServoObstacle=ForeServoPIDCen * (10 - dr) / 10 + ServoPIDMax * dr /10;
                  
                  
            }
            else {                                    //CCDλ�����ұߣ�������ϣ�������
                  
                  ServoObstacle=ForeServoPIDCen * (10 - dl) / 10 + ServoPIDMin * dl /10;
                  
            }
            
            BlockCnt=BlockCntLeftDefault;
            
      }
      
      
      
      
      if(BlockCnt>0){ 
            
            BlockCnt--;
            
//            if(Direction == RIGHT){                             //��ת·�����ϴ��
//                  
//                  
            if( SpeedNow > 300 )  {
              SpeedPre = SpeedSet;
              SpeedSet = 300;
              
            }
                  ServoPWM = ( ServoPWM * 3 +  ServoObstacle *  2 ) /5;
                  
                  FTM1_C0V = ServoPWM ;
                  
                  
//            }else{                                        //������ϴ��
//                  
//                  if( ServoObstacle < ForeServoPIDCen && BlockCnt < ( BlockCntBackDefaultRight / kr )){   //���ұ��ϵڶ��׶λ�����
//                        
//                        ServoObstacle = ServoObstacle * br /10 + ForeServoPIDCen * (10 - br) / 10 ;
//                        
//                  }
//                  
//                  if( ServoObstacle > ForeServoPIDCen && BlockCnt < ( BlockCntBackDefaultLeft / kl )){   //������ϵڶ��׶λ�����
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
            
            //BlockCnt������ж��Ƿ����ϰ�����־λ������
            
            BlockCnt=BlockCntRightDefault;
            
            
      }else if(BlockCnt == 0 && Direction == LEFT && SignalAvgRow < 180 && LightCntAvg  < 53 && CCDLightCnt > CCD2LightLimit && CCDPosition > CCD2LowerLimit && CCDPosition <CCD2UpperLimit){
            
            //BlockCnt������ж��Ƿ����ϰ�����־λ������
            
            BlockCnt = BlockCntLeftDefault;
            
      }else{
            
            ObstacleFlag=0;
            
      }  ***/
      
      
}