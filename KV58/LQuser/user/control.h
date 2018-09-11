#ifndef _CONTROL_H_
#define _CONTROL_H_
typedef struct PID{uint16 P,pout,I,iout,D,dout,OUT;}PID;
typedef struct PIDSpeed{uint16 P,pout,I,iout,D,dout, OutLeft, OutRight;}PIDSpeed;
extern  PID PID_TURN;
extern  PIDSpeed PID_SPEED;

extern int Speed_Filter_Times;
extern int SpeedCount;
extern int Camera_threshhold;
extern int Camera_threshholdH;
extern int Camera_Center;

extern float CarSpeedLeft,ControlSpeed,Hill_Slow_Ratio, CarSpeedRight;
extern float SetSpeedLeft, SetSpeedRight;
extern uint8 Set_Angle;
extern float AverageSpeed;
extern float Distance;
extern float SpeedControlOutOldRight,SpeedControlOutNewRight;
extern float SpeedControlIntegralRight;
extern float SpeedControlOutOldLeft,SpeedControlOutNewLeft;
extern float SpeedControlIntegralLeft;
extern float MotorOut;
extern int TakeOff;
//模糊化相关
extern float  Delta_P;
extern float  Delta_D;
extern float  Fuzzy_Kp;
extern float  Fuzzy_Kd;
//方向控制相关
extern int    DirectionCount;
extern float  Delt_error,Middle_Err;
extern float  Turn_Speed,Turn_Out,Turn_Angle_Integral;
extern float FrontServoKp;
extern float FrontServoKd;
extern float CCDServoKp;
extern float CCDServoKd;
extern int16  ServoPIDMax ;	
extern int16  ServoPIDMin ;



extern int16 LeftTargetOffset;
extern int16 RightTargetOffset;
extern int16 LeftFixedTargetOffset;
extern int16 RightFixedTargetOffset;
extern int16 ServoPWM;          //舵机占空比
extern int Devifuse;
extern int infrared_succeed;
extern int twinkle_Flag;
extern int twinkle_Flag2;
extern int twinkle_Flag3;
extern int DeltaDev;
extern int PreDev;
extern int CCD_Devifuse;
extern int CCD_PreDev;
extern int CCD_DeltaDev;
extern int duzhuanFlag;



/**舵机相关**/
extern int sever_middle;
extern int sever_range;

extern uint8 Starting,Stop;

void Get_Attitude();
void Get_Speed();
void Strong_Turn();
//void Moto_Out();
void MotorControl(uint16 left,uint16 right);
void Speed_Control();
void Speed_Control_Output();
void Direction_Control();
void DLY_ms(uint16 ms);
void duzhuan();

float  Middle_Err_Filter(float middle_err);  
float  Turn_Out_Filter(float turn_out);
#endif

//#ifndef _CONTROL_H_
//#define _CONTROL_H_
//typedef struct PID{float P,pout,I,iout,D,dout,OUT;}PID;
//extern  PID PID_SPEED,PID_TURN;
//extern int errGrade,errFu;
//extern int sDGrade,sDFu;
//extern float temp;
//extern int Speed_Filter_Times;
//extern int SpeedCount;
//extern float CarSpeed,ControlSpeed,Hill_Slow_Ratio;
//extern float SetSpeed;
//extern uint8 Set_Angle;
//extern float AverageSpeed;
//extern float Distance;
//extern float SpeedControlOutOld,SpeedControlOutNew;
//extern float SpeedControlIntegral;
//extern float MotorOut;
////模糊化相关
//extern float  Delta_P;
//extern float  Delta_D;
//extern float  Fuzzy_Kp;
//extern float  Fuzzy_Kd;
////方向控制相关
//extern int    DirectionCount;
//extern float  Delt_error,Middle_Err;
//extern int Err_Slope_mul50;
//extern float SpeedDevi;
//extern float SpeedDeviD;
//extern float  Turn_Speed,Turn_Out,Turn_Angle_Integral;
//extern float speedTarget;
//extern float SpeedE;
//extern float SpeedI;
//extern float SpeedD;
//extern float Speed_kP,Speed_kI;
//
////电机相关
//extern uint8 level;
//
///**舵机相关**/
//extern int sever_middle;
//extern int sever_range;
//
//extern uint8 Starting,Stop;
//
//void Get_Attitude();
//void Get_Speed();
//void Strong_Turn();
//void Moto_Out();
//void Speed_Control();
//void Speed_Control_Output();
//void Direction_Control();
//
//float  Middle_Err_Filter(float middle_err);  
//float  Turn_Out_Filter(float turn_out);
//void Err_Fuzzy(void);
//#endif
