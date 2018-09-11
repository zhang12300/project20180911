#include "include.h"

//�ٶ������
float SpeedControlOutNewRight;
float SpeedControlOutOldRight;
float SpeedControlIntegralRight=0,Hill_Slow_Ratio;
float SpeedControlOutNewLeft;
float SpeedControlOutOldLeft;
float SpeedControlIntegralLeft=0;
uint8  Set_Angle;   //����ǰ��Ƕ�
int   SpeedCount;
int   Speed_Filter_Times=5;    //�ٶ�ƽ�����
float CarSpeedLeft = 0,ControlSpeed=0,AverageSpeed,SetSpeedLeft=0,Distance=0, SetSpeedRight= 0, CarSpeedRight = 0;
//���������
float DirectionControlOutNew;
float DirectionControlOutOld;
float Turn_Speed=0;
int   DirectionCount;
float Delt_error,Middle_Err;
float Turn_Out;
float Turn_Angle_Integral;

/**������**/
int sever_middle=1320;
int sever_range=250;
float FrontServoKp = 8;		//10	    //p������������float  1
float FrontServoKd = 0.5;                        //0.05
float CCDServoKp = 6;    //10
float CCDServoKd = 0.3;
int16  ServoPIDMax = 1570;		//������ֵ   ��ת
int16  ServoPIDMin = 1070;		//�����Сֵ   ��ת

int Camera_threshhold = 10;   //һ��ͼƬ�ĵ��ű�Ƶ���������
int Camera_threshholdH = 600;  
int Camera_Center = 40;       //����ͷ��������
int CCD_Center = 64;
int CCD_Devifuse;
int CCD_PreDev;
int CCD_DeltaDev;
int16 ServoPWM;

int16  LeftTargetOffset = 1;           //15;	//�����ű�ʱ��ƫ��    
int16  LeftFixedTargetOffset = 8;//250;     //140
int16  RightTargetOffset = -1;
int16  RightFixedTargetOffset = -8;
uint8 Fixi=0;
//int16 FrontRightFixTable[19]={10,20,25,27,28,29,32,33,34,36,37,38,39,41,42,44,45,46,47};
int16 FrontRightFixTable[19]={7,8,10,12,14,15,16,17,19,21,22,24,26,28,30,31,32,33,35};
int16 Rightbuchang[19] = {1,2,5,6,8,10,10,12,14,16,16,17,18,21,22,23,24,24,25};
//int16 FrontLeftFixTable[17]={10,25,26,28,29,32,33,34,36,37,38,40,42,44,45,46,48};
int16 FrontLeftFixTable[19]={7,8,10,12,14,15,16,17,19,21,22,24,26,28,30,31,32,33,35};
int16 Leftbuchang[19] = {-1,-2,-5,-6,-8,-10,-15,-18,-20,-25,-22,-20,-21,-21,-22,-23,-25,-26,-30};
int16 CCDFixTable[19] = {1,2,5,6,7,9,10,12,14,16,17,18,20,21,22,23,24,25,26};
int16 CCDLbuchang[19] = {-4,-6,-10,-15,-20,-25,-32,-40,-40,-52,-50,-45,-45,-46,-47,-49,-51,-55,-58};
int16 CCDRbuchang[19] = {-4,-6,-10,-15,-20,-25,-32,-40,-40,-52,-50,-45,-45,-46,-47,-49,-51,-55,-58};
float ChaSu[49] = {1.768, 1.733, 1.700, 1.661, 1.625, 1.589, 1.553, 1.517, 1.481, 1.446, 1.409, 1.373, 1.265, 1.229, 1.193, 1.157, 1.121, 1.085, 1.049, 1.013, 0.977, 0.941, 0.905, 1,
                   0.866, 0.902, 0.938, 0.974, 1.010,1.046, 1.082, 1.118, 1.154, 1.190, 1.226,  1.262, 1.300, 1.334, 1.370, 1.406, 1.442, 1.479, 1.514, 1.550, 1.586, 1.622, 1.658, 1.694, 1.730};
int Devifuse, DeltaDev, PreDev;
int infrared_succeed = 0;
int twinkle_Flag = 0;
int twinkle_Flag2 = 0;
int twinkle_Flag3 = 0;
int TakeOff = 0;
int duzhuanFlag;
int infrared_Flag = 0;  //��ת��ʱFlag

//ģ����ϵ��
float  Delta_P;
float  Delta_D;
float  Fuzzy_Kp;
float  Fuzzy_Kd;
//PID���������
PID PID_TURN;
PIDSpeed PID_SPEED;

float  MotorOut;   //��������          
uint8   Starting,Stop;
uint8 Encoder_Disable=0;

void duzhuan()
{
        Motor_Duty(Mot0, 0);    
        Motor_Duty(Mot2, 0);
        Motor_Duty(Mot1, 300);
        Motor_Duty(Mot3, 300);
        ServoPWM = 1190;
        Servo_Duty(ServoPWM);
        DLY_ms(5500);
        Motor_Duty(Mot0, 300);    
        Motor_Duty(Mot2, 300);
        Motor_Duty(Mot1, 0);
        Motor_Duty(Mot3, 0);
        ServoPWM = 1320;
        Servo_Duty(ServoPWM);
        DLY_ms(5500);
        
        PID_SPEED.OutRight = 150;
}

void Get_Speed()                     //5msִ��һ��
{  
  int qd1_result;
  int qd2_result;
  qd1_result = -FTM_AB_Get(FTM2);   //Right
  qd2_result = FTM_AB_Get(FTM1);
  
//  FTM_QUAD_clean(FTM2);

//  Distance+=qd1_result/3100.0;  //ת��Ϊ����
  if(qd1_result >=0 && qd2_result >=0)
{
  CarSpeedLeft=CarSpeedLeft*0.1+0.9*qd2_result*250.0/3100;    //�������ת��ΪM/S
  CarSpeedRight=CarSpeedRight*0.1+0.9*qd1_result*250.0/3100;    //�������ת��ΪM/S
}
  if(CarSpeedRight > 2.0)
    TakeOff = 0;
  if(CarSpeedRight < 0.2 && PID_SPEED.OutRight > 300 && TakeOff == 0 && duzhuanFlag <= 30)
     duzhuanFlag++;
  else 
     duzhuanFlag = 0;
  if(duzhuanFlag > 30)
  {
    duzhuan();
    duzhuanFlag = 0;
  }
//   if(CarSpeedRight>4)
//     CarSpeedRight=4;
 
}

void DLY_ms(uint16 ms)  //��ʱ����
{                         
  uint16 a;
  while(ms)
  {
    a=13350;
    while(a--);
    ms--;
  }
  return;
}
//�ٶȿ���������
/****void Speed_Control(void)
{  
  static float PreError[20]={0};
  float  SpeedError;
  uint8 i;
  
 
   SpeedError=SetSpeed-CarSpeed; 
 
   
  //������20��ƫ����ܺ���Ϊ������
   SpeedControlIntegral=0;
   for(i=0;i<19;i++)
   {
     PreError[i]=PreError[i+1]; 
     SpeedControlIntegral+=PreError[i];
   }
    PreError[19]=SpeedError;
    SpeedControlIntegral+=PreError[19];
   
  //�ٶȸ���
  SpeedControlOutOld=SpeedControlOutNew;
 
  SpeedControlOutNew=PID_SPEED.P*SpeedError+PID_SPEED.I*SpeedControlIntegral;   //PI����
 
}  ****/
void Speed_Control(void)
{
  static float PreErrorRight[20]={0}, PreErrorLeft[20]={0};   
  float  SpeedError;
  uint8 i;
  
//  if(CCDLightCnt != 0 && CCDPosition != 255)   //ǰ��CCD���ź� �����������ͷ
//    {
//        if(LightCnt >= Camera_threshhold && LightCnt <= 1000)      //����ͷ���ź�  �����ű�Ƶ�Զ������
//        {
//           
//        }
//        else         //����ͷ���ź� CCD���źţ���CCDΪ׼         ����
//        {
//            SetSpeedRight = 2;
//        }
//    }
//    else   //ǰ��CCD���ź�   ���Ҳ�������
//    {
//        SetSpeedRight = 1;
//    }
  
//  if(ServoPWM < sever_middle)
//  {
//    i = (int)(ServoPWM - ServoPIDMin )/10;
//    SetSpeedLeft=SetSpeedRight*ChaSu[i];
//  }
//  else 
//  {
//    i = ( ServoPWM - ServoPIDMin)/10;
//    SetSpeedLeft=SetSpeedRight/ChaSu[i];
//  }
  
  SpeedError=SetSpeedRight-CarSpeedRight;   //��λm/s                �ҵ������
 
  //������20��ƫ����ܺ���Ϊ������
   SpeedControlIntegralRight=0;
   for(i=0;i<19;i++)
   {
     PreErrorRight[i]=PreErrorRight[i+1]; 
     SpeedControlIntegralRight+=PreErrorRight[i];
   }
    PreErrorRight[19]=SpeedError;
    SpeedControlIntegralRight+=PreErrorRight[19];
   
  //�ٶȸ���
  SpeedControlOutOldRight=SpeedControlOutNewRight;
 
  SpeedControlOutNewRight += (PID_SPEED.P*SpeedError+PID_SPEED.I*SpeedControlIntegralRight)*15;   //PI����
  
  if(SpeedControlOutNewRight > 500)
    SpeedControlOutNewRight = 500;
  else if(SpeedControlOutNewRight < -300)
    SpeedControlOutNewRight = -300;
  
  
//     SpeedError=SetSpeedLeft-CarSpeedLeft;   //��λm/s                ��������
// 
//  //������20��ƫ����ܺ���Ϊ������
//   SpeedControlIntegralLeft=0;
//   for(i=0;i<19;i++)
//   {
//     PreErrorLeft[i]=PreErrorLeft[i+1]; 
//     SpeedControlIntegralLeft+=PreErrorLeft[i];
//   }
//    PreErrorLeft[19]=SpeedError;
//    SpeedControlIntegralLeft+=PreErrorLeft[19];
//   
//  //�ٶȸ���
//  SpeedControlOutOldLeft=SpeedControlOutNewLeft;
// 
//  SpeedControlOutNewLeft += (PID_SPEED.P*SpeedError+PID_SPEED.I*SpeedControlIntegralLeft)*10;   //PI����
//  
//  if(SpeedControlOutNewLeft > 500)
//    SpeedControlOutNewLeft = 500;
//  else if(SpeedControlOutNewLeft < -300)
//    SpeedControlOutNewLeft = -300;
  
}
//�ٶȿ���
void Speed_Control_Output(void) 
{ 
//  float fValue; 
  //fValue = SpeedControlOutNewRight - SpeedControlOutOldRight; 
  //PID_SPEED.OutRight = fValue * (SpeedCount+1)/Speed_Filter_Times+SpeedControlOutOldRight;  
  PID_SPEED.OutRight = SpeedControlOutNewRight;
  PID_SPEED.OutLeft = SpeedControlOutNewLeft;
}







/********************�������������***************/
void Direction_Control(void)
{
//  static int Calculate_Length=0;
//  Turn_Speed=-0.01*Get_Z_Gyro();
//  
//   if(1)
//   {
//    Delta_P=Fuzzy(Middle_Err,Delt_error)*Fuzzy_Kp;
//    Delta_D=Fuzzy(Middle_Err,Delt_error)*Fuzzy_Kd;
//   }
//   
//  PID_TURN.pout=(PID_TURN.P+Delta_P)*Middle_Err;
//  PID_TURN.dout=(PID_TURN.D+Delta_D)*Turn_Speed;
//  Turn_Out= PID_TURN.pout- PID_TURN.dout;
//  Turn_Out=Turn_Out_Filter(Turn_Out);         //ת������˲� 
//  PID_TURN.OUT=Turn_Out*100;
//
//  if( PID_TURN.OUT > sever_range)          //������Ʒ�ֵ
//    PID_TURN.OUT=sever_range;
//   if( PID_TURN.OUT < -sever_range) 
//     PID_TURN.OUT=-sever_range;
//   FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle+PID_TURN.OUT);    //�����ֵ��0-180 �����仯
////   FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle);
  
    int16 Offset;
    int16 FixedOffset;
    int16 ServoPval;
    int16 ServoDval;
    int16 temp;
    int forward, back, left, right;
  
     //����ʱ
    if(infrared_succeed == 1 && USStatus == DistGetFinish)  
          USTrigger();
      
//    if(USDistance <= 60)
//    {
//        Servo_Duty(sever_middle - sever_range+125);
//        SetSpeedRight = 1.8;
//    }
//    else 
      if((CCDLightCnt != 0 && CCDPosition != 255) && twinkle_Flag <=10)   //���������    ǰ��CCD���ź� �����������ͷ
    {
        Stop = 0;
        SetSpeedRight = 2.2;
        twinkle_Flag = 0;
        LED_Ctrl(LED4, ON);
        LED_Ctrl(LED1, ON);
        LED_Ctrl(LED2, ON);
        LED_Ctrl(LED3, ON);
        infrared_Flag = 0;   // CCD���źţ���ת��ʱ����
   // LED_Ctrl(LED4, OFF);
        if((LightCnt >= Camera_threshhold && LightCnt <= Camera_threshholdH) && twinkle_Flag2 <= 8)             //����ͷ���ź� ������û�ĵ��Ĵ���С��8
        {
           twinkle_Flag2 = 0; //����ͷ��˸
           SetSpeedRight = 2.2;
           LED_Ctrl(LED4, OFF);
           LED_Ctrl(LED1, ON);
           LED_Ctrl(LED2, ON);
           LED_Ctrl(LED3, OFF);
           infrared_Flag = 0;   // ����ͷ���źţ���ת��ʱ����
             //       if(SignalPosition < Camera_Center)     //���
    //       {
              //Offset=LeftTargetOffset;            //�����ű�ʱ���ƫ��  1
              //FixedOffset=LeftFixedTargetOffset;   //8
   //        }
   //        else
   //        {
            //  Offset=RightTargetOffset;            //�����ű�ʱ��ƫ�� -1
            // FixedOffset=RightFixedTargetOffset;  //-8
   //        }
      
      //�켣�������
      
      
           if( SignalAvgRow != 0 )
           {          
             if(SignalPosition >= Camera_Center)   //�����ұ�
             {
                  for(Fixi= 0; Fixi<19; Fixi++ )
                  { 
                        if(SignalAvgRow <= FrontRightFixTable[Fixi])
                        {
                          FixedOffset = Leftbuchang[Fixi];        //ʵ�������ȥ��õ���������
                          break;
                        }
                  }
                    
              }
            
             else    //�������
             {
                   for(Fixi= 0; Fixi<19; Fixi++ )
                   {
                        if(SignalAvgRow<FrontLeftFixTable[Fixi])
                        {
                          FixedOffset = Leftbuchang[Fixi];  
                          break;
                        }   
                  } 
                  
              }
             if(Fixi>=18)
               Fixi>=0;
            }
      
      //ƫ������ȡ
//          Devifuse = SignalPosition - FixedOffset - Camera_Center;// + Offset * Fixi;  //���һ���ǹ켣����;
           Devifuse = SignalPosition + 27 - Camera_Center;// + Offset * Fixi;  //���һ���ǹ켣����;
           DeltaDev = Devifuse - PreDev;                      //΢������ȡ      
           PreDev = Devifuse;
      
      
      //P����
      
           ServoPval = (int16)((float)Devifuse * FrontServoKp);
      
      
      //D����
      
           ServoDval=(int16)((float)DeltaDev * FrontServoKd);
      
      
      //�������������
      
      
           temp = sever_middle - ServoPval - ServoDval;
      
            //����������޷�
            
           if(temp > ServoPIDMax)                
           {
              temp = ServoPIDMax;  
           }
           else if(temp < ServoPIDMin)
           {
             temp = ServoPIDMin;
           }
           else
           {    
       
           }
 
            
           ServoPWM = temp; 
//           FTM_PWM_Duty(FTM3,FTM_CH2,ServoPWM); 
           Servo_Duty(ServoPWM);
      
    
        }
        else if ((LightCnt < Camera_threshhold || LightCnt > Camera_threshholdH) && twinkle_Flag2 <= 8)        //����ͷû�źţ�������û�ĵ��Ĵ���С��8
        {
           twinkle_Flag2++;
           infrared_Flag = 1;  //��ת��ʱFlag   ����ͷ��ʧ
           
        }
        else         //����ͷ���ź� CCD���źţ���CCDΪ׼
        {
            twinkle_Flag2 = 0;
            //�ٶȿ���
            Stop = 0;
            SetSpeedRight = 1.8;

      //�켣�������    
          for(Fixi= 0; Fixi<19; Fixi++ )
          {
             if(CCDLightCnt < CCDFixTable[Fixi])
             {
               break;
             }   
          } 
        
            if(CCDPosition >= CCD_Center)    //�����ұ�
            {
               Offset = CCDRbuchang[Fixi];
            }
            else               //�������
            {               
              Offset = CCDLbuchang[Fixi];
            }
            CCD_Devifuse = CCDPosition - CCD_Center - Offset; 
            CCD_DeltaDev = CCD_Devifuse - CCD_PreDev;                      //΢������ȡ      
            CCD_PreDev = CCD_Devifuse;
       
      //P����
      
            ServoPval = (int16)((float)CCD_Devifuse * CCDServoKp);  //Kp= 20;
      
      
      //D����
      
           ServoDval=(int16)((float)CCD_DeltaDev * CCDServoKd);  //kd = 10
      
      
      //�������������
      
      
           temp = sever_middle - ServoPval - ServoDval;
      
            //����������޷�
            
           if(temp > ServoPIDMax)                
           {
              temp = ServoPIDMax;  
           }
           else if(temp < ServoPIDMin)
           {
             temp = ServoPIDMin;
           }
           else
          {    
      
          }
 
            
           ServoPWM = temp; 
//           FTM_PWM_Duty(FTM3,FTM_CH2,ServoPWM); 
           Servo_Duty(ServoPWM);
        }
    }
    else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=10)   //ǰ10��CCDû���ĵ�ͼ��
    {
         twinkle_Flag++;
         infrared_Flag = 2;  //��ת��ʱFlag  CCD��ʧ
         Stop = 0;
       //  return 0;
    }
    else   //ǰ��CCD���ź�
    {
         Stop = 0;
         SetSpeedRight = 3.2;
         LED_Ctrl(LED1, OFF);
         LED_Ctrl(LED2, OFF);
         LED_Ctrl(LED3, OFF);
         LED_Ctrl(LED4, ON);
    //    infrared_succeed = infrared_pro();   //�ɹ�����1
        if(infrared_succeed == 1 )//&& twinkle_Flag3 <= 2)         //�������ź�      ��������С��2
        {
          twinkle_Flag = 0;
          forward = 0;
          back = 0;
          left = 0;
          right = 0;
          
          
          if(inf3_data == 0)   //ǰ�����ź�
          {
            forward = forward + 2;
          }
          if(inf2_data == 0)   //��ǰ
          {
            forward++;
            left++;
          }
          if(inf4_data == 0)   //��ǰ
          {
            forward++;
            right++;
          }
          if(inf1_data == 0)   //��
          {
            left = left + 2;
          }
          if(inf5_data == 0)   //��
          {
            right = right + 2;
          }
          if(inf0_data == 0)   //���
          {
            back++;
            left++;
          }
          if(inf6_data == 0)   //�Һ�
          {
            back++;
            right++;
          }
          if(inf7_data == 0)  //��
          {
            back = back + 2; //��ת���� ����
          }
          
          if(inf3_data == 0 && inf7_data == 0);
          else if(inf1_data == 0 && inf5_data == 0);
          else if(forward > back && left == right)       //ǰ��
          {
//            FTM_PWM_Duty(FTM3,FTM_CH2,sever_middle);     //ֱ��
            Servo_Duty(sever_middle);
            ServoPWM = sever_middle;
          }
          else if(forward < back && left == right)  //��
          {
//            FTM_PWM_Duty(FTM3,FTM_CH2,sever_middle - sever_range); //��ת���� ����
            Servo_Duty(sever_middle - sever_range);
            ServoPWM = sever_middle - sever_range;
          }
          else if(forward == back && left > right)      //����
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 60); 
            if(infrared_Flag != 0)
            {
              DLY_ms(1800);
            }
            Servo_Duty(sever_middle + sever_range - 60);
            ServoPWM = sever_middle + sever_range - 60;
          }
          else if(forward == back && left < right)     //����
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 60); 
            Servo_Duty(sever_middle - sever_range + 60);
            ServoPWM = sever_middle - sever_range + 60;
          }
          else if(forward > back && left > right)   //��ǰ
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 130); 
              Servo_Duty(sever_middle + sever_range - 130);
              ServoPWM = sever_middle + sever_range - 130;
          }
          else if(forward > back && left < right)   //��ǰ
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 130); 
            Servo_Duty(sever_middle - sever_range + 130);
            ServoPWM = sever_middle - sever_range + 130;
          }
          else if(forward < back && left > right)   //���
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range);
            if(infrared_Flag != 0)
            {
              DLY_ms(1800);
            }
            Servo_Duty(sever_middle + sever_range);
            ServoPWM = sever_middle + sever_range;
          }
          else if(forward < back && left < right)   //�Һ�
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range);
            Servo_Duty(sever_middle - sever_range);
            ServoPWM = sever_middle - sever_range;
          }
          else if(forward == back && left == right)
          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle);
            Servo_Duty(sever_middle);
            ServoPWM = sever_middle;
          }
             
        }  
//        else if(infrared_succeed == 0 && twinkle_Flag3 <= 2)    //����û�ź�  ��������С��2
//        {
//          twinkle_Flag3++;
//          //return 0;
//        }
        else  //û�ź� ��ת
        {
           //FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - 250);    //ͣ��
//           Servo_Duty(sever_middle - 250);
//           ServoPWM = sever_middle - 250;
           //Stop = 1;
           
        }
           
    } 
    
    //  ����ͷ��
   /** if((CCDLightCnt != 0 && CCDPosition != 255)) //&& twinkle_Flag <=20)   //���������    ǰ��CCD���ź� �����������ͷ
    {
        Stop = 0;
        twinkle_Flag = 0;
        if((LightCnt >= Camera_threshhold && LightCnt <= Camera_threshholdH))// && twinkle_Flag2 <= 2)             //����ͷ���ź� ������û�ĵ��Ĵ���С��5
        {
           twinkle_Flag2 = 0; //����ͷ��˸
    //       if(SignalPosition < Camera_Center)     //���
    //       {
              //Offset=LeftTargetOffset;            //�����ű�ʱ���ƫ��  1
              //FixedOffset=LeftFixedTargetOffset;   //8
   //        }
   //        else
   //        {
            //  Offset=RightTargetOffset;            //�����ű�ʱ��ƫ�� -1
            // FixedOffset=RightFixedTargetOffset;  //-8
   //        }
      
      //�켣�������
      
      
           if( SignalAvgRow != 0 )
           {          
             if(SignalPosition >= Camera_Center)   //�����ұ�
             {
                  for(Fixi= 0; Fixi<19; Fixi++ )
                  { 
                        if(SignalAvgRow <= FrontRightFixTable[Fixi])
                        {
                          FixedOffset = Leftbuchang[Fixi];        //ʵ�������ȥ��õ���������
                          break;
                        }
                  }
                  FixedOffset = -25;   
              }
            
             else    //�������
             {
                   for(Fixi= 0; Fixi<19; Fixi++ )
                   {
                        if(SignalAvgRow<FrontLeftFixTable[Fixi])
                        {
                          FixedOffset = Leftbuchang[Fixi];  
                          break;
                        }   
                  } 
                  FixedOffset = -25;
              }
             if(Fixi>=18)
               Fixi>=0;
            }
      
      //ƫ������ȡ
           Devifuse = SignalPosition - FixedOffset - Camera_Center;// + Offset * Fixi;  //���һ���ǹ켣����;
           DeltaDev = Devifuse - PreDev;                      //΢������ȡ      
           PreDev = Devifuse;
      
      
      //P����
      
           ServoPval = (int16)((float)Devifuse * FrontServoKp);
      
      
      //D����
      
           ServoDval=(int16)((float)DeltaDev * FrontServoKd);
      
      
      //�������������
      
      
           temp = sever_middle - ServoPval - ServoDval;
      
            //����������޷�
            
           if(temp > ServoPIDMax)                
           {
              temp = ServoPIDMax;  
           }
           else if(temp < ServoPIDMin)
           {
             temp = ServoPIDMin;
           }
           else
           {    
       
           }
 
            
           ServoPWM = temp; 
           FTM_PWM_Duty(FTM1,FTM_CH1,ServoPWM); 
      
    
        }
//        else if ((LightCnt < Camera_threshhold || LightCnt > Camera_threshholdH) && twinkle_Flag2 <= 2)        //����ͷû�źţ�������û�ĵ��Ĵ���С��5
//        {
//           twinkle_Flag2++;
//        }
        else         //����ͷ���ź� CCD���źţ���CCDΪ׼
        {
            twinkle_Flag2 = 0;
            if(CCDPosition >= CCD_Center)    //�����ұ�
            {
                Offset = -15;
               //Offset = Leftbuchang[Fixi]-15;
            }
            else               //�������
            { 
               Offset = -15;
              //Offset = Leftbuchang[Fixi]-15;
            }
            CCD_Devifuse = CCDPosition - CCD_Center - Offset; 
            CCD_DeltaDev = CCD_Devifuse - CCD_PreDev;                      //΢������ȡ      
            CCD_PreDev = CCD_Devifuse;
       
      //P����
      
            ServoPval = (int16)((float)CCD_Devifuse * CCDServoKp);  //Kp= 20;
      
      
      //D����
      
           ServoDval=(int16)((float)CCD_DeltaDev * CCDServoKd);  //kd = 10
      
      
      //�������������
      
      
           temp = sever_middle - ServoPval - ServoDval;
      
            //����������޷�
            
           if(temp > ServoPIDMax)                
           {
              temp = ServoPIDMax;  
           }
           else if(temp < ServoPIDMin)
           {
             temp = ServoPIDMin;
           }
           else
          {    
      
          }
 
            
           ServoPWM = temp; 
           FTM_PWM_Duty(FTM1,FTM_CH1,ServoPWM); 
        }
    }
//    else if((CCDLightCnt == 0 || CCDPosition == 255) && twinkle_Flag <=20)   //ǰ20��û���ĵ�ͼ��
//    {
//         twinkle_Flag++;
//         Stop = 0;
//       //  return 0;
//    }
    else   //ǰ��CCD���ź�
    {
        Stop = 0;
        twinkle_Flag = 0;
    //    infrared_succeed = infrared_pro();   //�ɹ�����1
        if(infrared_succeed == 1 )//&& twinkle_Flag3 <= 2)         //�������ź�      ��������С��2
        {
          twinkle_Flag3 = 0;
          forward = 0;
          back = 0;
          left = 0;
          right = 0;
          
          if(inf3_data == 0)   //ǰ�����ź�
          {
            forward = forward + 2;
          }
          if(inf2_data == 0)   //��ǰ
          {
            forward++;
            left++;
          }
          if(inf4_data == 0)   //��ǰ
          {
            forward++;
            right++;
          }
          if(inf1_data == 0)   //��
          {
            left = left + 2;
          }
          if(inf5_data == 0)   //��
          {
            right = right + 2;
          }
          if(inf0_data == 0)   //���
          {
            back++;
            left++;
          }
          if(inf6_data == 0)   //�Һ�
          {
            back++;
            right++;
          }
          if(inf7_data == 0)  //��
          {
            back = back + 2; //��ת���� ����
          }
          
          if(forward >= back && left == right)
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle);   //ֱ��
          else if(forward < back && left == right)
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); //��ת���� ����
          else if(forward == back && left >= right)      //��
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range); 
          else if(forward == back && left < right)     //��
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
          else if(forward >= back && left >= right)   //��ǰ
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 100); 
          else if(forward >= back && left < right)   //��ǰ
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 100); 
          else if(forward < back && left >= right)   //���
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range); 
          else if(forward < back && left < right)   //�Һ�
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
             
        }  
//        else if(infrared_succeed == 0 && twinkle_Flag3 <= 2)    //����û�ź�  ��������С��2
//        {
//          twinkle_Flag3++;
//          //return 0;
//        }
        else  //û�ź� ��ת
        {
           //FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle);    //ͣ��
           Stop = 1;
           
        }
           
    }   **/
     
 /** //   CCD��
    if((CCDLightCnt != 0 && CCDPosition != 255))   //���������    ǰ��CCD���ź� �����������ͷ
    {
        //�ٶȿ���
        Stop = 0;
        SetSpeedRight = 2;

      //�켣�������    
        for(Fixi= 0; Fixi<19; Fixi++ )
        {
          if(CCDLightCnt < CCDFixTable[Fixi])
          {
            break;
          }   
        } 
        
            if(CCDPosition >= CCD_Center)    //�����ұ�
            {
               Offset = CCDRbuchang[Fixi];
            }
            else               //�������
            {               
              Offset = CCDLbuchang[Fixi];
            }
            CCD_Devifuse = CCDPosition - CCD_Center - Offset; 
            CCD_DeltaDev = CCD_Devifuse - CCD_PreDev;                      //΢������ȡ      
            CCD_PreDev = CCD_Devifuse;
       
      //P����
      
            ServoPval = (int16)((float)CCD_Devifuse * CCDServoKp);  //Kp= 20;
      
      
      //D����
      
           ServoDval=(int16)((float)CCD_DeltaDev * CCDServoKd);  //kd = 10
      
      
      //�������������
      
      
           temp = sever_middle - ServoPval - ServoDval;
      
            //����������޷�
            
           if(temp > ServoPIDMax)                
           {
              temp = ServoPIDMax;  
           }
           else if(temp < ServoPIDMin)
           {
             temp = ServoPIDMin;
           }
           else
          {    
      
          }
 
            
           ServoPWM = temp; 
           FTM_PWM_Duty(FTM1,FTM_CH1,ServoPWM); 
        }
    
    else   //ǰ��CCD���ź�
    {
        if(infrared_succeed == 1 )      //�������ź�      ��������С��2
        {
             
//          if(inf3_data == 0)   //ǰ�����ź�
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle); 
//          }
//          else if(inf2_data == 0)   //��ǰ
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 100); 
//          }
//          else if(inf4_data == 0)   //��ǰ
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 100); 
//          }
//          else if(inf1_data == 0)   //��
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range); 
//          }
//          else if(inf5_data == 0)   //��
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
//          }
//          else if(inf0_data == 0)   //���
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range); 
//          }
//          else if(inf6_data == 0)   //�Һ�
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
//          }
//          else if(inf7_data == 0)  //��
//          {
//            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); //��ת���� ����
//          }
          
          
          //�ٶȿ���
          Stop = 0;
          SetSpeedRight = 3.5;
          
          forward = 0;
          back = 0;
          left = 0;
          right = 0;
          
          if(inf3_data == 0)   //ǰ�����ź�
          {
            forward = forward + 2;
          }
          if(inf2_data == 0)   //��ǰ
          {
            forward++;
            left++;
          }
          if(inf4_data == 0)   //��ǰ
          {
            forward++;
            right++;
          }
          if(inf1_data == 0)   //��
          {
            left = left + 2;
          }
          if(inf5_data == 0)   //��
          {
            right = right + 2;
          }
          if(inf0_data == 0)   //���
          {
            back++;
            left++;
          }
          if(inf6_data == 0)   //�Һ�
          {
            back++;
            right++;
          }
          if(inf7_data == 0)  //��
          {
            back = back + 2; //��ת���� ����
          }
          
          if(forward >= back && left == right)
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle);   //ֱ��
          else if(forward < back && left == right)
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 130); //��ת���� ����
          else if(forward == back && left >= right)      //��
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 130); 
          else if(forward == back && left < right)     //��
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
          else if(forward >= back && left >= right)   //��ǰ
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range - 180); 
          else if(forward >= back && left < right)   //��ǰ
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range + 180); 
          else if(forward < back && left >= right)   //���
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle + sever_range); 
          else if(forward < back && left < right)   //�Һ�
            FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle - sever_range); 
             
        }
        else  //û�ź� ��ת
        {
           //FTM_PWM_Duty(FTM1,FTM_CH1,sever_middle);    //ͣ��
           Stop = 1;
           
        }
           
    }  **/  
    
}

//���pwmֵ���
//void Moto_Out() 
//{
// //�ٶȿ�������޷�
// if(PID_SPEED.OUT>0.8)//�������ǰ�㣬��ģ���ٶȿ������Ϊ������֮Ϊ��
// PID_SPEED.OUT=0.8;
// if(PID_SPEED.OUT<-0.8)
// PID_SPEED.OUT=-0.8;
//  MotorOut=PID_SPEED.OUT;
// 
// //��ֵ�޷�����ֹ���ٹ���
// 
//  
//  if(MotorOut>0.99)MotorOut=0.99;                     
//  if(MotorOut<-0.99)MotorOut=-0.99; 
// 
//
// if(Stop)                                //���ֹͣ���������
// {
//    MotorOut=0;
//    LED_BLUE_ON;
// }
//
// 
// 
//   if(MotorOut>=0) //��ת
//  {
//     FTM_PWM_Duty(FTM0,FTM_CH4,MotorOut*10000);//ռ�ձȾ���Ϊ10000 
//     FTM_PWM_Duty(FTM0,FTM_CH5,0);
//     FTM_PWM_Duty(FTM0,FTM_CH6,MotorOut*10000);//ռ�ձȾ���Ϊ10000 
//     FTM_PWM_Duty(FTM0,FTM_CH7,0);
//  }
//  else   //��ת
//  {
//     FTM_PWM_Duty(FTM0,FTM_CH6,0);
//     FTM_PWM_Duty(FTM0,FTM_CH7,-MotorOut*10000);
//  }
//
//}

//------------------------------------------------------------------------------
//��������MotorControl
//��  �ܣ����ҵ��PWM����
//��  ����motor_leftΪ����PWM��motor_rightΪ�ҵ��PWM
//��  �أ���
//˵  ����PWMռ�ձȼ��㷽��CnV/MOD
//------------------------------------------------------------------------------
void MotorControl(uint16 left,uint16 right)
{    
      
      if(left>500){
            left=500;
      }
      else if(left<-300){
            left=-300;
      }
      else{
      }
      
      if(right>500){
            right=500;
      }
      else if(right<-300){
           right=-300;
      }
      else{
      }
      
      
//    //�������� 
       if(TakeOff == 1)
    {
        Motor_Duty(Mot0, 500);
//        Motor_Duty(Mot2, 500);
    }
//    else if(left<0)
//    {
////        FTM_PWM_Duty(FTM0,FTM_CH4,0);//ռ�ձȾ���Ϊ10000 
////        FTM_PWM_Duty(FTM0,FTM_CH5,-left);
//        Motor_Duty(Mot0, 0);
//        Motor_Duty(Mot1, -left);
//    }
//    else
//    {
////        FTM_PWM_Duty(FTM0,FTM_CH4,left);//ռ�ձȾ���Ϊ10000 
////        FTM_PWM_Duty(FTM0,FTM_CH5,0);
//        Motor_Duty(Mot0, left);
//        Motor_Duty(Mot1, 0);
//    }
    //�ҵ������
    if(TakeOff == 1)
    {
//        Motor_Duty(Mot0, 500);
        Motor_Duty(Mot2, 500);
    }
    else if(right<0)
    {
//        FTM_PWM_Duty(FTM0,FTM_CH0,0);//ռ�ձȾ���Ϊ10000 
//        FTM_PWM_Duty(FTM0,FTM_CH1,-right);
//        FTM_PWM_Duty(FTM0,FTM_CH2,0);//ռ�ձȾ���Ϊ10000 
//        FTM_PWM_Duty(FTM0,FTM_CH3,-right);
        Motor_Duty(Mot0, -right);
        Motor_Duty(Mot2, -right);
        Motor_Duty(Mot1, 0);  
        Motor_Duty(Mot3, 0);
//        FTM_PWM_Init(FTM0,FTM_CH0,1000,  -right);//Mot0-PTC1
//        FTM_PWM_Init(FTM0,FTM_CH1,1000,  0);//Mot1-PTC2 
//        FTM_PWM_Init(FTM0,FTM_CH2,1000,  -right);//Mot2-PTC3
//        FTM_PWM_Init(FTM0,FTM_CH3,1000,  0);//Mot3-PTC4 
    }
    else
    {
//        FTM_PWM_Duty(FTM0,FTM_CH0,right);//ռ�ձȾ���Ϊ10000 
//        FTM_PWM_Duty(FTM0,FTM_CH1,0);
//        FTM_PWM_Duty(FTM0,FTM_CH2,right);//ռ�ձȾ���Ϊ10000 
//        FTM_PWM_Duty(FTM0,FTM_CH3,0);
        Motor_Duty(Mot0, right);    
        Motor_Duty(Mot2, right);
        Motor_Duty(Mot1, 0);
        Motor_Duty(Mot3, 0);
//        FTM_PWM_Init(FTM0,FTM_CH0,1000,  right);//Mot0-PTC1
//        FTM_PWM_Init(FTM0,FTM_CH1,1000,  0);//Mot1-PTC2 
//        FTM_PWM_Init(FTM0,FTM_CH2,1000,  right);//Mot2-PTC3
//        FTM_PWM_Init(FTM0,FTM_CH3,1000,  0);//Mot3-PTC4 
    }
}







////��������
//float deltaSpeedTarget[7] = {
//	-0.5,	-0.1,	0.1,	0.2,	0.3,	0.35,	0.45
//	//
//};
//float deltaKp[5] = {
//	1,1,0.8,0.5	// xx%
//};
//float deltaServoKp[7] = {
//		0.6,0.7,0.9,0.9,1.1,1.1,1.0
//	//	  1,	1,	1,	0.9,	1.05,	1.15,	1.15
//	//0~10	20~50	50~80	80~110	110~140	140~170	170~100000000
//};
//
//float deltaServoDout[6] = {
//	0.6,	0.7,	1.0,	1.05,	1.06,	1.07
//	//0~20	20~50	50~80	80~110	110~140	140~170	170~100000000
//};
//float deltaServoDback[6] = {
//	0.9,0.9,	1,	1,	1.05,	1.05
////        1,	1.01,	1.05,	1.05,	1.06,	1.07
//};
//
//
//int errGrade,errFu;
//int sDGrade,sDFu;
////�ٶ������
//float temp;
//float SpeedControlOutNew;
//float SpeedControlOutOld;
//float SpeedControlIntegral=0,Hill_Slow_Ratio;
//uint8  Set_Angle;   //����ǰ��Ƕ�
//int   SpeedCount;
//int   Speed_Filter_Times=30;    //�ٶ�ƽ�����
//float CarSpeed=0,ControlSpeed=0,AverageSpeed,SetSpeed=0,Distance=0;
////���������
//float DirectionControlOutNew;
//float DirectionControlOutOld;
//float Turn_Speed=0;
//int   DirectionCount;
//float Delt_error,Middle_Err;
//int Err_Slope_mul50;
//float SpeedDevi;
//float SpeedDeviD;
//float Turn_Out=0;
//float Turn_Angle_Integral;
//
///**������**/
//int sever_middle=440;
//int sever_range=93;
////ģ����ϵ��
//float  Delta_P;
//float  Delta_D;
//float  Fuzzy_Kp;
//float  Fuzzy_Kd;
//uint8 devi_level;
////PID���������
//PID PID_SPEED,PID_TURN;
//
//float  MotorOut;   //��������          
//uint8   Starting,Stop;
//uint8 Encoder_Disable=0;
///*float P_adjust[]={0,0.015,-0.02,0.15,
//0.015,0.015,0,0.0                    };     //+jiansu*/
//float P_adjust[]={0,-0.012,-0.013,-0.016,
//0.055,0.045,0.04,0.0                    };     //+jiansu
//float D_adjust[]={0,0.01,-0.007,0,
//0,0.01,0,0                    };           //+jiansu
//uint8 level;
//
//void Get_Speed()                     //5msִ��һ��
//{  
//	static int qd1_result;
//	qd1_result =- FTM_AB_Get(FTM2); 
//	
//	Distance += qd1_result/12400.0;  //ת��Ϊ����                      1m3100������
//	CarSpeed=CarSpeed*0.1+0.9*qd1_result*250.0/3100/4;    //�������ת��ΪM/S         1000�����ڣ�250 ��Ӧ4ms
//	if(CarSpeed>10)Stop=1;
//}
//float SpeedSpecialDeal(float oriSpeed)
//{
//         if(Stop==1)
//        {
//           return 0;
//        }
//        else if(RoadType==5)
//        {
//          return oriSpeed-0.3;
//        }
//        else if((RoadType==3 || RoadType==2)&& circle_stage==0)
//        {
//          if(turn_flag==3)return 2.9;
//          else return 2.6;
//        }
//        else if((RoadType==3 || RoadType==2)&& circle_stage==2)
//        {
//          if(turn_flag==3)return 3.15;
//          else return 2.7;
//        }
//        else if((RoadType==3 || RoadType==2)&& circle_stage==3)
//        {
//          return 3.0;
//        }
//        else if(RoadType==1)
//        {
//          return 2.8;
//        }
//        else if(RoadType==0 && GO>55 && GO!=255 && (NO<6||NO==255))
//        {
//          if(CarSpeed<2.3)return oriSpeed+0.75;
//          else if(CarSpeed<2.5)return oriSpeed+0.40;
//          else if(CarSpeed<2.7)return oriSpeed+0.2;
//          else return oriSpeed;
//        }
//		
//		if(RoadType == 4)
//		{
//			return 3.5;
//		}
//	return oriSpeed;
//}
//float speedTarget;
//float SpeedE;
//float SpeedI = 0;
//float SpeedD;
//float Speed_kP,Speed_kI,Speed_kD;
//static float PreErr[20] = {0};
//void Speed_Control(void)
//{
//	int i;	
//	//�õ�Ŀ���ٶ�
//	speedTarget = SetSpeed - (sDFu * deltaSpeedTarget[sDGrade+1] + (1000-sDFu) * deltaSpeedTarget[sDGrade])/1000;
//	//Ŀ���ٶȵ����⴦��
//	speedTarget = SpeedSpecialDeal(speedTarget);
//	///////////////////////////////////////////////
//	//PID�㷨��ʼ
//	///////////////////////////////////////////////
//	//P����
//	SpeedE = speedTarget - CarSpeed;
//	float temp = ABS(SpeedE);
//	//kp
//	if(temp < 0.05)
//	{
//		Speed_kP = PID_SPEED.P * deltaKp[4];
//	}
//	else if(temp < 0.1)
//	{
//		Speed_kP = PID_SPEED.P * deltaKp[3];
//	}                 
//	else if(temp < 0.15)                     
//	{
//		Speed_kP = PID_SPEED.P * deltaKp[2];
//	}                                         
//	else if(temp < 0.2)                     
//	{                                         
//		Speed_kP = PID_SPEED.P * deltaKp[1];
//	}      
//	else
//	{
//		Speed_kP = PID_SPEED.P * deltaKp[0];
//	}
//	
//	//I����
//	SpeedI = 0;
//	if(Stop == 0)
//	{
//		//����20���������ڼ���I��D
//		Push_And_Pull(PreErr,20,SpeedE);		
//		for(i = 0; i < 20; i++)
//		{
//			SpeedI += PreErr[i];
//		}
//	}
//	//SpeedI�޷�
//	if(SpeedI > 9) SpeedI = 9;
//	else if(SpeedI < -4) SpeedI = -4;
//	//ki
//	Speed_kI = PID_SPEED.I;
//	
//	//D����
////	SpeedD = Slope_Calculate(0,7,PreErr);
////	//SpeedD�޷�
////	if(SpeedD > 5) SpeedD = 5;
////	else if(SpeedD < -5) SpeedD = -5;
////	//kD
////	Speed_kD = PID_SPEED.D * MIN(CarSpeed,2.5);
//	
//	
//	//D����������Delt_Err����
//	SpeedD = SpeedDeviD;
//	Speed_kD = PID_SPEED.D;
//	
//	//PI����
//	SpeedControlOutOld=SpeedControlOutNew;
//	SpeedControlOutNew=Speed_kP*SpeedE + Speed_kI*SpeedI + Speed_kD*SpeedD + 0.1;//0.1��������һЩĦ����
//}
////�ٶȿ���������
////void Speed_Control(void) //100ms����һ��
////{
////	
////  static float PreError[20]={0};
////  float  SpeedError;
////  uint8 i;
////  level=3;
////
////  if(Middle_Err>17)
////  {
////    if(CarSpeed>2.55)level=4;
////    else if(CarSpeed>2.45)level=5;
////    else if(CarSpeed>2.35)level=6;
////    else level =0;
////  }
////  else if(Middle_Err>4&&Middle_Err<=17)
////  {
////    if(CarSpeed>2.5)level=4;
////    else if(CarSpeed>2.35)level=5;
////    else if(CarSpeed>2.2)level=6;
////    else level =0;
////  }
////  else if(Middle_Err>-3&&Middle_Err<=3)
////  {
////    if(CarSpeed>3.00)level=4;
////    if(CarSpeed>2.9)level=5;
////    else if(CarSpeed>2.75)level=6;
////    else if(CarSpeed>2.65)level=1;
////    else if(CarSpeed>2.50)level=2;
////    else level=3;
////  }
////  else if(Middle_Err>-17&&Middle_Err<=-4)
////  {
////    if(CarSpeed>2.5)level=4;
////    else if(CarSpeed>2.35)level=5;
////    else if(CarSpeed>2.2)level=6;
////    else level =0;
////  }
////  else if(Middle_Err<=-17)
////  {
////    if(CarSpeed>2.55)level=4;
////    else if(CarSpeed>2.45)level=5;
////    else if(CarSpeed>2.35)level=6;
////    else level =0;
////  }
////  /*if(CarSpeed>2.45)level+=4;
////  if(CarSpeed>2.70 && (Middle_Err>3 || Middle_Err<-3))level=3;*/
////  temp=P_adjust[level];
////
////  if(CarSpeed<1.8 && temp>0) temp=0;
////  if(CarSpeed>2.75 && temp<0) temp=0;
////  //P�޷�
////  if(temp>0.055)temp=0.055;
////  else if(temp<-0.014)temp=-0.014;
////  if(Stop==1)
////  {
////    if(CarSpeed>1.5)SpeedError=-3.5; 
////    else SpeedError=-6; 
////  }
////  else if(CarSpeed>3.0)
////    SpeedError=-1;
////  else if(CarSpeed>2.35 && middle_right_q+middle_left_q>20 && ABS(Middle_Err)<6)
////    SpeedError=-1;              //5.18
////  else if(CarSpeed>2.40 && middle_right_q+middle_left_q>16 && ABS(Middle_Err)<3)
////    SpeedError=-1;              //5.18
////  else if(CarSpeed>2.45 && middle_right_q+middle_left_q>20 && ABS(Middle_Err)<6)
////    SpeedError=0;
////  else if(RoadType==4&& ABS(Middle_Err)<2.3 && CarSpeed<2.7)
////  {
////    temp=-0.0170;        //yuanwei 0.012
////    SpeedError=SetSpeed-CarSpeed-temp*30; 
////  }
////  else if (RoadType==2||RoadType==3)
////  {
////    if(CarSpeed>2.30)temp=0.06;
////    else if(CarSpeed>2.20)temp=0.04;
////    else if(CarSpeed>2.10)temp=0.02;
////    else if(CarSpeed>2.0)temp=0.01;
////    else temp=-0.006;
////    SpeedError=SetSpeed-CarSpeed-temp*40; 
////  }
////  else if(level==4 && CarSpeed>2.6)
////    SpeedError=-1;
////  else
////    SpeedError= SetSpeed-temp*50-CarSpeed; 
////  
////   
////  //������20��ƫ����ܺ���Ϊ������
////   SpeedControlIntegral=0;
////   if(Stop==0)
////   {
////     for(i=0;i<19;i++)
////     {
////       PreError[i]=PreError[i+1]; 
////       SpeedControlIntegral+=PreError[i];
////     }
////      PreError[19]=SpeedError;
////      SpeedControlIntegral+=PreError[19];
////   }
////  //�ٶȸ���
////  SpeedControlOutOld=SpeedControlOutNew;
////  
////  SpeedControlOutNew=PID_SPEED.P*SpeedError+PID_SPEED.I*SpeedControlIntegral;   //PI����
//// 
////}
////�ٶȿ���
//void Speed_Control_Output(void) //2ms����һ��
//{ 
//	float fValue; 
//	fValue = SpeedControlOutNew - SpeedControlOutOld; 
//	PID_SPEED.OUT = fValue * (SpeedCount+1)/Speed_Filter_Times+SpeedControlOutOld;  
//}
//void Direction_SpecialDeal(void)
//{
//	if(RoadType==5)
//	{
//		PID_TURN.pout*=0.8;
//		PID_TURN.dout*=0.5;
//	}
//	else if(RoadType==3 && (circle_stage==1||circle_stage==3))
//	{
//		PID_TURN.dout = 0;
//	}
//	else if(RoadType==3 && circle_stage==2)
//	{
//		if(turn_flag==1)
//                {
//                  PID_TURN.pout *= 0.7;
//                  PID_TURN.dout*=0.6;
//                }
//	}
//	//D���޷�
//	if(PID_TURN.dout > 0.8) PID_TURN.dout = 0.8;
//	else if(PID_TURN.dout < -0.8) PID_TURN.dout = -0.8;
//}
///********************�������������***************/
//void Direction_Control(void)
//{
//	//P����
//	Delta_P = (errFu * deltaServoKp[errGrade+1] + (1000-errFu) * deltaServoKp[errGrade])/1000;
//	PID_TURN.pout=(PID_TURN.P*Delta_P)*Middle_Err;
//	//D����
//	if(Middle_Err > 0 && Delt_error > 0 || Middle_Err < 0 && Delt_error < 0)//����
//	{
//		Delta_D = deltaServoDout[errGrade];
//	}
//	else//����
//	{
//		Delta_D = deltaServoDback[errGrade];
//	}
//	PID_TURN.dout=(PID_TURN.D*Delta_D)*Delt_error;       //�÷��� kk
//	
//	Direction_SpecialDeal();
//	//����ֵ
//	Turn_Out= PID_TURN.pout- PID_TURN.dout;
//	
//	//ת������˲�
//	Turn_Out=Turn_Out_Filter(Turn_Out);
//	PID_TURN.OUT=Turn_Out*100;
//	//����޷�
//	if( PID_TURN.OUT>sever_range) PID_TURN.OUT=sever_range;
//	else if( PID_TURN.OUT<-sever_range) PID_TURN.OUT=-sever_range;
//	
//	Servo_Duty((u32)(sever_middle+PID_TURN.OUT));
////	FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle+PID_TURN.OUT);    //�����ֵ��0-180 �����仯
//}
////void Direction_Control(void)
////{
////	float special=0;
////	static int Calculate_Length=0;
////	Turn_Speed=-0.01*Get_Z_Gyro();
////	if(1)
////	{
////		Delta_P=Fuzzy(Middle_Err,Delt_error)*Fuzzy_Kp;
////		Delta_D=Fuzzy(Middle_Err,Delt_error)*Fuzzy_Kd;
////	}
////	if(RoadType==1)//ʮ�ֵĴ������
////	{
////		special=0.005;
////	}
////	else
////	{
////		special=0.0;
////	}
////	PID_TURN.pout=(PID_TURN.P+Delta_P-special)*Middle_Err;
////	PID_TURN.dout=(PID_TURN.D+Delta_D-special)*Delt_error;       //�÷��� kk
////	Turn_Out= PID_TURN.pout- PID_TURN.dout;
////	
////	Turn_Out=Turn_Out_Filter(Turn_Out);         //ת������˲�
////	
////	PID_TURN.OUT=Turn_Out*100;
////	//out�޷�
////	if( PID_TURN.OUT>sever_range) PID_TURN.OUT=sever_range;
////	else if( PID_TURN.OUT<-sever_range) PID_TURN.OUT=-sever_range;
////	
////	FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle+PID_TURN.OUT);    //�����ֵ��0-180 �����仯
////	//   FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle);
////}
//
////���pwmֵ���
//void Moto_Out() 
//{     
//	if(CarSpeed < 1.5 && PID_SPEED.OUT > 0.7)
//		PID_SPEED.OUT = 0.7;
//	//�ٶȿ�������޷�
//	if(PID_SPEED.OUT>0.8)
//		PID_SPEED.OUT=0.8;
//	if(PID_SPEED.OUT<-0.8)
//		PID_SPEED.OUT=-0.8;
//	MotorOut=-PID_SPEED.OUT;
//	
//	//��ֵ�޷�����ֹ���ٹ���
//	if(MotorOut>0.99)MotorOut=0.99;                     
//	if(MotorOut<-0.99)MotorOut=-0.99; 
//	
//	if(Stop)                                //���ֹͣ���������
//	{
//		if(CarSpeed<0.8)MotorOut=0;
//		else 
//			LED_BLUE_ON;
//	}
//
//	
//	if(MotorOut>=0) //��ת
//	{
//		Motor_Duty(Mot0, (u32)MotorOut*1000);
//		Motor_Duty(Mot1, 0);
////		FTM_PWM_Duty(FTM0,FTM_CH0,MotorOut*10000);//ռ�ձȾ���Ϊ10000 
////		FTM_PWM_Duty(FTM0,FTM_CH2,0);
//	}
//	else   //��ת
//	{
//		Motor_Duty(Mot0, 0);
//		Motor_Duty(Mot1, (u32)-MotorOut*1000);
////		FTM_PWM_Duty(FTM0,FTM_CH0,0);
////		FTM_PWM_Duty(FTM0,FTM_CH2,-MotorOut*10000);
//	}
//	
//}
//
//
//float  Turn_Out_Filter(float turn_out)    //ת���������˲�      
//{
//	float Turn_Out_Filtered; 
//	static float Pre1_Error[4]; 
//	Pre1_Error[3]=Pre1_Error[2];
//	Pre1_Error[2]=Pre1_Error[1];
//	Pre1_Error[1]=Pre1_Error[0];
//	Pre1_Error[0]=turn_out;
//	Turn_Out_Filtered=Pre1_Error[0]*0.8+Pre1_Error[1]*0.15+Pre1_Error[2]*0.05;
//	return Turn_Out_Filtered;
//}
//float  Middle_Err_Filter(float middle_err)    //����ƫ���˲�      
//{
//	float Middle_Err_Fltered; 
//	static float Pre3_Error[4]; 
//	Pre3_Error[3]=Pre3_Error[2];
//	Pre3_Error[2]=Pre3_Error[1];
//	Pre3_Error[1]=Pre3_Error[0];
//	Pre3_Error[0]=middle_err;
//	Middle_Err_Fltered=Pre3_Error[0]*0.4+Pre3_Error[1]*0.3+Pre3_Error[2]*0.2+Pre3_Error[3]*0.1;
//	return Middle_Err_Fltered;
//}
//void Err_Fuzzy(void)
//{
//	//Middle_Err�ּ�
//	int absErr = (int)ABS(Middle_Err);
//	if(absErr < 5)//0~10//��ȫֱ��
//	{
//		errGrade = 0;
//		errFu = absErr * 1000 / 5;
//	}
//	else if(absErr < 10)//10~30//ֱ��΢΢ƫ��
//	{
//		errGrade = 1;
//		errFu = (absErr - 5) * 1000 / 5;
//	}
//	else if(absErr < 20)//30~60//ֱ���ϴ�ƫ�ƣ���Ҫ����
//	{
//		errGrade = 2;
//		errFu = (absErr - 10) * 1000 / 10;
//	}
//	else if(absErr < 30)//60~100//��������
//	{
//		errGrade = 3;
//		errFu = (absErr - 20) * 1000 / 10;
//	}
//	else if(absErr < 40)//100~170//��������
//	{
//		errGrade = 4;
//		errFu = (absErr - 30) * 1000 / 10;
//	}
//	else if(absErr < 50)//170~230//������
//	{
//		errGrade = 5;
//		errFu = (absErr - 40) * 1000 / 10;
//	}
//	else//230~100000000
//	{
//		errGrade = 5;
//		errFu = 1000;
//	}
//	
//	absErr = (int)ABS(SpeedDevi);
//	if(absErr < 5)//0~10//��ȫֱ��
//	{
//		sDGrade = 0;
//		sDFu = absErr * 1000 / 5;
//	}
//	else if(absErr < 10)//10~30//ֱ��΢΢ƫ��
//	{
//		sDGrade = 1;
//		sDFu = (absErr - 5) * 1000 / 5;
//	}
//	else if(absErr < 20)//30~60//ֱ���ϴ�ƫ�ƣ���Ҫ����
//	{
//		sDGrade = 2;
//		sDFu = (absErr - 10) * 1000 / 10;
//	}
//	else if(absErr < 30)//60~100//��������
//	{
//		sDGrade = 3;
//		sDFu = (absErr - 20) * 1000 / 10;
//	}
//	else if(absErr < 40)//100~170//��������
//	{
//		sDGrade = 4;
//		sDFu = (absErr - 30) * 1000 / 10;
//	}
//	else if(absErr < 50)//170~230//������
//	{
//		sDGrade = 5;
//		sDFu = (absErr - 40) * 1000 / 10;
//	}
//	else//230~100000000
//	{
//		sDGrade = 5;
//		sDFu = 1000;
//	}
//}
//void Get_Control_Line(void)
//{
//	
//}