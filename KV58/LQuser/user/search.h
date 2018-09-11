#ifndef __SEARCH_H__
#define __SEARCH_H__
#define LINE_Far 120
extern uint8  RoadType,turn_point,circle_stage;
extern float slope_qj;
extern float Previous_Error[20];
void Search();
void get_edge();   
void sendimg();
void Push_And_Pull(float *buff,int len,float newdata);
extern int Loc[3][LINE_Far];
extern float Middle_Err_Sum_Far,Middle_Err_Sum,Middle_Err_Sum_Near,Middle_Err_Sum_Middle;
extern int rightround_state;
extern uint8 count_right,count_left,curve_liner_left,curve_liner_right,curve_linel_left,curve_linel_right,straight_right,straight_left,white_left,white_right,turn_flag;
extern int SlopeLmax,SlopeLmin,SlopeRmax,SlopeRmin,search_end_line;
extern uint8 il,ir;   //左右拐点wk
extern uint8 control_line,stop_line;
extern uint8 control_line_near,control_line_far;
extern uint8 bais;
extern int curve_left,curve_right;
extern uint8 failcount,times_count;
extern float close_slope;
extern float flope_temp;
extern int search_end_line;
extern uint8 middle_right_q,middle_left_q,middle_straight_q;
extern uint8 middle_continue;
extern uint8 S_flag,first_white_right;
extern int AllWhileStartLine,AllWhileEndLine;
extern uint8 continue_line_left,continue_line_right;
extern uint8 end_line,left_end_line,right_head_line,right_end_line,left_head_line;
extern int slope_q[3][120]; 
extern uint8 str_L,str_L1,str_L2,str_R,str_R1,str_R2,LL,LL1,LL2,LR,LR1,LR2,RR,RR1,RR2,RL,RL1,RL2;
extern uint8 lose_brick;
extern float slope_speed;
extern int GO,NO;   //速度控制
extern uint8 N0,N1,N2,Np; 

#endif