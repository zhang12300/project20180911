#include "common.h"
#include "include.h"
float sVariable[20]; //����������
float Variable[20];  //
float Control_Para[15];
float Voltage;
float RunTime;
int   Start_Cnt=0;
uint8 Para_Index_Limit=7;       //һҳ�����7���������
uint8 Send_img = 0;
uint8 Page_Index=0,Para_Index=1,Light_Tower_Index=0,Para_Checked=0,OLED_Refresh=0;
uint8 Uart_Send=0,SendPara,Dirc,stop_contorl,send_data_contorl=0;
uint8 HighSpeed = 0;
float Step[6]={0.0001,0.001,0.01,0.1,1.0,10.0};   //Ĭ�ϵ��ڲ���Ϊ0.01
unsigned char Step_Index=2;
//��Ӧ��ͬ��ҳ��
char Para_Name[7][12]={"Set_SPEED\0","FUZZY.P\0","FUZZY.D\0","PID_SPEED.P\0",
"PID_SPEED.I\0","PID_DIREC.P\0","PID_DIREC.D\0"};

char Para_Name1[7][12]={"Set_Speed\0","Set_Angle\0","Acc_Offset\0","Fuzzy_kp",
"Fuzzy_kd","STurnSpeed\0","BTurnAngle\0"};

void my_putchar(char temp)
{
	UART_Put_Char(UART_4,temp);
//      uart_putchar(UART0,temp); //����ʵ�ʵĴ��ں����޸�
}
/*����֪ͨ��λ���µ�һ�����ݿ�ʼ��Ҫ�������ݱ��뷢����*/
void Send_Begin()
{
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0x11);
}






void Variable_update()
{
  Variable[3]=Devifuse;
//  Variable[4]=CCD_Devifuse;
  Variable[4]=ServoPWM;
  //Variable[4]=SignalAvgRow;
//  Variable[5]=SignalPosition;
//  Variable[6]=CCDPosition;
    Variable[5]=SetSpeedLeft;
  Variable[6]=CarSpeedLeft;
  //Variable[7]=ServoPWM;
  Variable[7]=CarSpeedRight;
  Variable[8]=PID_SPEED.OutRight ;
  //Variable[8]= Max_White ;
  //Variable[9]= LightCnt ;
  Variable[9]= SetSpeedRight;
  Variable[10]= CCDLightCnt;
  
}
void Para_Update()
{ 
  SetSpeedRight=Control_Para[0];
  Fuzzy_Kp=Control_Para[1];
//  bais=(int)Control_Para[2];
  PID_SPEED.P=Control_Para[3];
  PID_SPEED.I=Control_Para[4];
  PID_TURN.P=Control_Para[5];
  PID_TURN.D=Control_Para[6]; 
}


void OLED_Draw_UI()  //��������
{ 
   uint8 i;
   if(Page_Index<=1) 
   {
//     Voltage=adc_once(ADC0_SE14,ADC_12bit);
     Voltage=Voltage*Vol_ratio; //ת��Ϊʵ�ʵ�ѹ
     OLED_P6x8Str(0,0,"Voltage=");                          //��ʾ��ص�ѹ
     OLED_PrintValueF(48, 0,Voltage,2);                     
     OLED_PrintValueF(72, 0,Step[Step_Index],5);            //��ʾ���ڲ���ֵ
     if(Para_Index==7)
     {
        reverse=1; 
         OLED_P6x8Str(116,0,"EE"); 
        reverse=0;
     }
     else  
     {
        OLED_P6x8Str(116,0,"EE"); 
     }
     OLED_Set_Pos(122,7);
     OLED_P6x8Char(Page_Index+48);                         //д��ҳ�����
   }
  /////////////////////////////////////////////////////////��0ҳ  PID����
  if(Page_Index==0)                
  {
    for(i=0;i<7;i++)
    {
      if(i==Para_Index && Para_Checked==false)
      {
       reverse=1;
       OLED_P6x8Str(0,i+1,Para_Name[i]);   //����������ת��ʾ
       reverse=0;
      }
      else 
        OLED_P6x8Str(0,i+1,Para_Name[i]);

          
      if(i==Para_Index && Para_Checked)
      {
        reverse=1;
        OLED_PrintValueF(72, i+1,Control_Para[i],5);
        reverse=0;
      }
      else  
        OLED_PrintValueF(72, i+1,Control_Para[i],5);
      
      OLED_Set_Pos(116,i+1);

    }
  }
    /////////////////////////////////////////////////////////��1ҳ ״̬��ʾ
  else if(Page_Index==1)
  {


    OLED_P6x8Str(0,6,"CarSpeedRight");
    OLED_PrintValueF(72, 6,CarSpeedRight,4);
    OLED_P6x8Str(0,2,"Distance");
    OLED_PrintValueF(72, 2,Distance,4);
    OLED_P6x8Str(0,3,"RunTime");
    OLED_PrintValueF(72, 3,RunTime,4);
    OLED_P6x8Str(0,4,"Average_Spd");
    OLED_PrintValueF(72, 4,AverageSpeed,4); 
    OLED_P6x8Str(0,5,"USDistance");
    OLED_PrintValueF(72, 5,USDistance, 4); 
    reverse=0;
    
  } 
  ////////////////////////////////////////////////////////////��2ҳ ��������ʾ
  else if(Page_Index==2) 
  {
    OLED_Draw_camera();
    OLED_P6x8Str(82,2,"LightCnt");
    OLED_PrintValueF(82, 3,LightCnt,4);
    OLED_P6x8Str(82,4,"Position");
    OLED_PrintValueF(82, 5,SignalPosition,4);
    OLED_PrintValueF(82, 6,SignalAvgRow,4);
//    OLED_PrintValueF(82, 7,Middle_Err,4);
  }
  ///////////////////////////////////////////////////////////��3ҳ  CCD��ʾ
  else if(Page_Index==3)
  {
    
  }
  
}


/*
 * �����뿪�ص�ֵ
 */
//void Read_Switch() 
//{
//  if(gpio_get(SW3)==0)  //���뿪��1����
//  {
//   Uart_Send=true;
//  }
//  else           
//  {
//    Uart_Send=false;
//  }
//
//  if(gpio_get(SW1)==0)   //���뿪��3����
//  {
//       if(Stop)
//       { 
//         Start_Cnt=1000;
//         Starting=true;
//         //�������ٶȿ��Ʊ�������
//         SpeedControlOutOld=0;
//         SpeedControlOutNew=0;
//         SpeedControlIntegral=0;  
//         PID_SPEED.OUT=0;
//         RunTime=0;
//         Distance=0;
//         ControlSpeed=0;
//       }
//  } 
//  else 
//  {
//    
//  }
//  
//  if(gpio_get(SW4)==0)  //���뿪��4����
//  {
//    Dirc=1;
//  }
//  else 
//  {
//    Dirc=0;
//  }
// 
//
//} 

void Read_Switch() 
{
  if(gpio_get(SW1)==0)  //���뿪��1����
  {
   //Uart_Send=true;
    if(SendPara == false)
    {
      SendPara = 1;
      OLED_Fill(0x00); 
      OLED_P6x8Str(50,3,"High Speed"); 
      Motor_Duty(Mot0, 400);
      Motor_Duty(Mot2, 400);
    } 
  }
  else           
  {
    //Uart_Send=false;
    if(SendPara == true)
    {
      SendPara = false;
      OLED_Fill(0x00); 
      Motor_Duty(Mot0, 300);
      Motor_Duty(Mot2, 300);
    } 
  }
  if(gpio_get(SW2)==0)   //���뿪��2���� ����ͼ����CCD
  {
    if (Send_img == false)
      {
        Send_img = true;
        OLED_Fill(0x00); 
        OLED_P6x8Str(50,3,"Send Img"); 
      }
  } 
  else 
  {
    if(Send_img == true)
    {
      Send_img = false;
      OLED_Fill(0x00);
    }
       
       
  }

  if(gpio_get(SW3)==0)   //���뿪��3����  //��ʾoled
  {
       if(OLED_Refresh==false)
        {
//         OLED_Init();
         LCD_Init();               //LCD��ʼ��
         OLED_Refresh=true;
        }      
  } 
  else 
  {
    if(OLED_Refresh==true)
    {
         OLED_Fill(0x00);
         OLED_Refresh=false;
    }     
         
  }
  
  if(gpio_get(SW4)==0)  //���뿪��4����
  {
   if(HighSpeed == false)
    {
      HighSpeed = 1;
      OLED_Fill(0x00); 
      OLED_P6x8Str(50,3,"High High Speed"); 
//      Motor_Duty(Mot0, 400);
//      Motor_Duty(Mot2, 400);
    } 
  }
  else           
  {
    //Uart_Send=false;
    if(HighSpeed == true)
    {
      HighSpeed = false;
      OLED_Fill(0x00); 
      Motor_Duty(Mot0, 300);
      Motor_Duty(Mot2, 300);
    } 
  }
 

} 


/*
 * ��ⰴ���Ƿ���
 */
//void Check_BottonPress()
//{
//  
//      //��ʾ����
//     if(BT_SHOW_IN==0)
//   {
//       time_delay_ms(30);
//      if(BT_SHOW_IN==0)
//      {
//          if(OLED_Refresh==false)
//        {
//         LCD_Init();
//         OLED_Refresh=true;
//        }
//        else
//        {
//          //Stop = 0;
//          LED_BLUE_OFF;
//          OLED_Refresh=false;
//          OLED_Fill(0x00);       
//        }
//      }
//      while(BT_SHOW_IN==0);  //ֱ�������ɿ�������
//      time_delay_ms(30);
//   } 
//   //����1 yes
//   if(BT_YES_IN==0&&OLED_Refresh) 
//   {
//       time_delay_ms(30);
//      if(BT_YES_IN==0&&OLED_Refresh)
//     {    
//       if(Para_Index==7) 
//       { 
//         Para_Index=0; 
//       }
//       else
//       {
//         if(Para_Checked==false&&((Page_Index==1)||(Page_Index==0))) Para_Checked=true;
//         else Para_Checked=false; 
//       }
//      }
//      while(BT_YES_IN==0); //ֱ�������ɿ�������
//   }
//   //����2 Left_L
//     if(BT_LEFT_IN==0)
//   {
//	   //ȥ��
//       time_delay_ms(30);
//      if(BT_LEFT_IN==0)
//      {
//        if(Para_Checked) 
//        {
//          if(Step_Index==5) 
//          Step_Index=0;   //���Ĳ���Ϊ10
//          else Step_Index++;
//        }
//        else 
//        { 
//          Para_Index=0;
//          if(Page_Index==0) Page_Index=3; //������û��ѡ�е�ʱ�򣬰����Ҽ���ҳ
//          else Page_Index--;
//          OLED_Fill(0);//���� 
//        }
//      }
//      while(BT_LEFT_IN==0);//ֱ�������ɿ�������
//   } 
//   //����6 Right_L
//     if(BT_RIGHT_IN==0&&OLED_Refresh)
//   {
//      //ȥ��
//       time_delay_ms(30);
//      if(BT_RIGHT_IN==0)
//      {
//        if(Para_Checked) 
//        {
//          if(Step_Index==0) 
//           Step_Index=0;//��С�Ĳ���Ϊ0.0001
//          else
//          {
//            Step_Index--;
//          }
//        }
//        else 
//        { 
//          Para_Index=0;
//          if(Page_Index==3) Page_Index=0;
//          else Page_Index++;
//         OLED_Fill(0);//���� 
//        }
//      }
//      while(BT_RIGHT_IN==0);      //ֱ�������ɿ�������
//   }
//   //����3 up
//     if(BT_UP_IN==0&&OLED_Refresh)
//   {
//       time_delay_ms(30);
//      if(BT_UP_IN==0)
//      {
//   
//          if(Para_Checked==false)
//          {
//           if(Para_Index==0) Para_Index=Para_Index_Limit;
//           else Para_Index-=1;
//          }
//          else
//          {
//              if(Page_Index==0&&Para_Index<=6)                    //�޸ĵ�0ҳ�Ĳ���
//            {
//              Control_Para[Para_Index]+=Step[Step_Index];
//            }
//            
//            if(Page_Index==1&&Para_Index<=6)                    //�޸ĵ�1ҳ�Ĳ���
//            {
//              Control_Para[Para_Index+7]+=Step[Step_Index];
//            } 
//            Para_Update();
//          }
//      }  
//      while(BT_UP_IN==0);//ֱ�������ɿ�������  
//   }
//   //����4 down
//     if(BT_DOWN_IN==0)
//   {
//     if(OLED_Refresh)
//     {
//       time_delay_ms(30);
//      if(BT_DOWN_IN==0)
//      {
//          if(Para_Checked==false)
//          {             
//            if(Para_Index==Para_Index_Limit)Para_Index=0;   //��ֹ��ų�����Χ
//            else  Para_Index+=1; 
//          }
//           else 
//           {
//              if(Page_Index==0&&Para_Index<=6)                    //�޸ĵ�0ҳ�Ĳ���
//            {
//              Control_Para[Para_Index]-=Step[Step_Index];
//            }
//             
//             if(Page_Index==1&&Para_Index<=6)                    //�޸ĵ�1ҳ�Ĳ���
//            {
//              Control_Para[Para_Index+7]-=Step[Step_Index];
//            }
//            Para_Update();
//          }
//      }
//     }
//     else
//     {      
//        /*if(Stop)
//       { 
//         Start_Cnt=1000;
//         Starting=true;
//         //�������ٶȿ��Ʊ�������
//         SpeedControlOutOld=0;
//         SpeedControlOutNew=0;
//         SpeedControlIntegral=0;  
//         PID_SPEED.OUT=0;
//         RunTime=0;
//         Distance=0;
//         ControlSpeed=0;
//       }*/
//     }
//
//      while(BT_DOWN_IN==0);  //ֱ�������ɿ�������
//   }
//}
//#define BT_SHOW    PTC7
//#define BT_RIGHT_LEFT   PTB20//PTC8
//#define BT_UP_DOWN      PTB21//PTC6

//#define BT_YES     PTB22
/
//
//#define SW1      PTC6//PTC12
//#define SW2      PTC7//PTC13
//#define SW3      PTC8//PTC14
//#define SW4      PTC9//PTC15
//
//
//#define SW1_IN   gpio_get(SW1)
//#define SW2_IN   gpio_get(SW2)
//#define SW3_IN   gpio_get(SW3)
//#define SW4_IN   gpio_get(SW4)
//
////#define BT_SHOW_IN  gpio_get(BT_SHOW)
//#define BT_LEFT_IN_RIGHT_IN   gpio_get(BT_RIGHT_LEFT)
//#define BT_UP_IN_DOWN_IN     gpio_get(BT_UP_DOWN)
//#define BT_YES_IN    gpio_get(BT_YES)
void Check_BottonPress()
{
   //����5 yes
   if(BT_YES_IN==0 && OLED_Refresh)      //KEY5  ȷ�ϼ�
   {
     //ȥ��
//       DELAY_MS(30);
      time_delay_ms(30);
      if(BT_YES_IN==0 && OLED_Refresh)
     {    
       if(Para_Index==7) 
       { 
         //EEPROM_Save();
         Para_Index=0; 
       }
       else
       {
 
         if(Para_Checked==false && ((Page_Index==1)||(Page_Index==0))) 
           Para_Checked=true;
         else 
           Para_Checked=false;       

       }
      }
      while(BT_YES_IN==0); //ֱ�������ɿ�������
   }
   //����1 Left_L
     if(BT_LEFT_IN_RIGHT_IN==0&&gpio_get(SW4)==0)           //KEY1  ��ҳ ���󲽳�
   {
      //ȥ��
//       DELAY_MS(30);
     time_delay_ms(30);
      if(BT_LEFT_IN_RIGHT_IN==0)
      {
        if(Para_Checked) 
        {
          if(Step_Index==5) 
          Step_Index=5;   //���Ĳ���Ϊ10
          else Step_Index++;
        }
        else 
        { 
          Para_Index=0;
          if(Page_Index==0) 
            Page_Index=3; //������û��ѡ�е�ʱ�򣬰����Ҽ���ҳ
          else 
            Page_Index--;
          OLED_Fill(0);//���� 
        }
      }
      while(BT_LEFT_IN_RIGHT_IN==0);//ֱ�������ɿ�������
   } 
   //����2 Right_L
     if(BT_LEFT_IN_RIGHT_IN==0 && OLED_Refresh&&gpio_get(SW4)==1)   //KEY2    �ҷ�ҳ ��С����
   {
      //ȥ��
//       DELAY_MS(30);
      time_delay_ms(30);
      if(BT_LEFT_IN_RIGHT_IN==0)
      {
        if(Para_Checked) 
        {
          if(Step_Index==0) 
           Step_Index=0;//��С�Ĳ���Ϊ0.0001
          else
          {
            Step_Index--;
          }
        }
        else 
        { 
          Para_Index=0;
          if(Page_Index==3) 
            Page_Index=0;
          else 
            Page_Index++;
         OLED_Fill(0);//���� 
        }
      }
      while(BT_LEFT_IN_RIGHT_IN==0);      //ֱ�������ɿ�������
   }
   //����3 up
     if(BT_UP_IN_DOWN_IN==0&&OLED_Refresh&&gpio_get(SW4)==0)     //KEY3
   {
//       DELAY_MS(30);
      time_delay_ms(30);
      if(BT_UP_IN_DOWN_IN==0)
      {

          if(Para_Checked==false)
          {
           if(Para_Index==0) 
             Para_Index=Para_Index_Limit;
           else 
             Para_Index-=1;
          }
          else
          {
              if(Page_Index==0 && Para_Index<=6)                    //�޸ĵ�0ҳ�Ĳ���
            {
              Control_Para[Para_Index]+=Step[Step_Index];
            }
            
            if(Page_Index==1 && Para_Index<=6)                    //�޸ĵ�1ҳ�Ĳ���
            {
              Control_Para[Para_Index+7]+=Step[Step_Index];
            } 
            Para_Update();
          }
      }  
      while(BT_UP_IN_DOWN_IN==0);//ֱ�������ɿ�������  
   }
   //����4 down
     if(BT_UP_IN_DOWN_IN==0&&gpio_get(SW4)==1)            //KEY4  ��������
   {
     if(OLED_Refresh)
     {
//       DELAY_MS(30);
      time_delay_ms(30);
      if(BT_UP_IN_DOWN_IN==0)
      {
          if(Para_Checked==false)
          {             
            if(Para_Index==Para_Index_Limit)
              Para_Index=0;   //��ֹ��ų�����Χ
            else  
              Para_Index+=1; 
          }
           else 
           {
              if(Page_Index==0 && Para_Index<=6)                    //�޸ĵ�0ҳ�Ĳ���
            {
              Control_Para[Para_Index]-=Step[Step_Index];
            }
             
             if(Page_Index==1 && Para_Index<=6)                    //�޸ĵ�1ҳ�Ĳ���
            {
              Control_Para[Para_Index+7]-=Step[Step_Index];
            }
            Para_Update();
          }
      }
     }
     else
     {      
        if(Stop)
       { 
         Start_Cnt=1000;
         Starting=true;
         //�������ٶȿ��Ʊ�������
         SpeedControlOutOldRight=0;
         SpeedControlOutNewRight=0;
         SpeedControlIntegralRight=0;  
         SpeedControlOutOldLeft=0;
         SpeedControlOutNewLeft=0;
         SpeedControlIntegralLeft=0; 
         PID_SPEED.OutRight=0;
         RunTime=0;
         Distance=0;
         ControlSpeed=0;
       }
     }

      while(BT_UP_IN_DOWN_IN==0);  //ֱ�������ɿ�������
   }
}





//void Send_Variable()
//{
//  uint8 i=0,ch=0;
//  float temp=0;
//  uint8 Variable_num=16;
//  my_putchar(0x55);
//  my_putchar(0xaa);
//  my_putchar(0xff);
//  my_putchar(0x01);
//  my_putchar(Variable_num);
// for(i=0;i<Variable_num;i++)
//  {
//    temp=Variable[i];
//    ch=BYTE0(temp);
//    my_putchar(ch);
//    ch=BYTE1(temp);
//    my_putchar(ch);
//    ch=BYTE2(temp);
//    my_putchar(ch);
//    ch=BYTE3(temp);
//    my_putchar(ch);
//  }
//     my_putchar(0x01);
//}

void Send_Variable()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Variable_num=10;    //ɽ�����8ͨ��   ����16
//  my_putchar(0x55);
//  my_putchar(0xaa);
//  my_putchar(0xff);
//  my_putchar(0x01);
  my_putchar(0x03);
  my_putchar(0xFC);
//my_putchar(Variable_num);
 for(i=3;i<=Variable_num;i++)  //Variable[]��float��32λ ֻ����7ͨ��
  {
    temp=Variable[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
   // my_putchar(0x01);
    my_putchar(0xFC);
    my_putchar(0x03);
}

void Send_CCD()
{
  uint8 i=0;
  uint8 num=128;    //ccd 128λ
//  my_putchar(0x55);
//  my_putchar(0xaa);
//  my_putchar(0xff);
//  my_putchar(0x01);
  my_putchar(0x02);
  my_putchar(0xFD);
//my_putchar(Variable_num);
 for(i=0;i<num;i++)  //Variable[]��float��32λ
  {
    my_putchar(ad1[i]);
  }
   // my_putchar(0x01);
    my_putchar(0xFD);
    my_putchar(0x02);
}



void Modify_Parameter(uint8 *buff)
{
   uint8 i=0,addr=0;
   float temp;
   uint8 Parameter_num=14; //14���ɸĲ���
  /*          �޸Ĳ�������         */
   for(i=0;i<Parameter_num;i++)
  {
       BYTE0(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE1(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE2(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE3(temp)=*(uint8*)(buff+addr);
       addr++;
       Control_Para[i]=temp;
   }
   
    Para_Update();
}



void Send_Parameter()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Parameter_num=14;  //14���ɸĲ���
  
 
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xff);
  my_putchar(0x02);
  my_putchar(Parameter_num);
  for(i=0;i<Parameter_num;i++)
  { 
     temp=Control_Para[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
    my_putchar(0X02);//֡β
}

void UART0_RX_IRQHandler()
{
  static uint8 recv;
  static uint8 data_cnt=0;
  static uint8 predata[10];
  static uint8 Recv_Buff[100];
  static uint8 Data_Receiving=false;
  
//  if(uart_query(UART0)==1)  uart_getchar (UART0,(char*)(&recv));  //����ʵ�ʵĴ������޸�
  /**********�������ڽ���������λ���Ĳ�������*********/
  if(Data_Receiving)
  {
      if(data_cnt<56)
      {
       Recv_Buff[data_cnt]= recv;
       data_cnt++;
      }
      else
      {
        data_cnt=0;    //�ﵽ֡��
        Data_Receiving=false;
        if(recv==2)  //֡β
        {
           Modify_Parameter(Recv_Buff);
           SendPara=1;      //�����ش���ȷ�ϲ����޸����
            beep=1; //����������
        }
      }
  }

  
  
    if( predata[1]==0x55&&predata[0]==0xAA)
    {
      
        switch(recv)         //�жϹ�����
         { 
            case 1:           //��ȡ���� 
               if(SendPara==0) SendPara=1;
                beep=1; //����������
              break;
            
            case 2:           //�޸Ĳ���
              data_cnt=0;
              Data_Receiving=true;
            case 3:           //�������
//              EEPROM_Save();
              beep=1; //����������
            break;        
           
            case 4:           //���ܿ���1
             
            break;    
            
            case 5:           //���ܿ���2
             
            break;     
            
            case 6:           //���ܿ���3
             
            break; 
            
            case 7:           //���ܿ���4
             
            break;        
            
            default:           //
             break;
          }
    }
  predata[1]=predata[0];
  predata[0]=recv;
}