#include "include.h"    

void sendimg()
{
   uint8 ch=0;
  float temp=0;
  uint16 i=0,num;
  
  my_putchar(0x01);      //山外的发送格式
  my_putchar(0xfe);
  for(i=0;i< CAMERA_SIZE;i++)
 {
     my_putchar(imgbuff[i]);
 }
  my_putchar(0xfe);
  my_putchar(0x01);  
  
  /**my_putchar(0x55);   //名优科创的发送格式
  my_putchar(0xaa);
  my_putchar(0xff);
  my_putchar(0xa2);
  my_putchar(RoadType); //小车状态
  
  num=cont+2+180+36;  
  //统计将要传输的数据量 2是因为要传输关键字即0xf0和0xf2
  //180是边线的位 36是变量的位 如果不传输就不要加上！
  
  my_putchar(BYTE0(num)); 
  my_putchar(BYTE1(num));
 for(i=0;i< cont;i++)
 {
     my_putchar(img_edg[i]);
 }
 my_putchar(0xf0);  //代表图像数据发完了    **/
 /******************星号围起来的可以不传输*******************/
// for(i=0;i<180;i++)
// {
//  my_putchar( LMR[i/60][i%60]);
// }
//  for(i=0;i<9;i++)
//  {
//    temp=sVariable[i];
//    ch=BYTE0(temp);
//    my_putchar(ch);
//    ch=BYTE1(temp);
//    my_putchar(ch);
//    ch=BYTE2(temp);
//    my_putchar(ch);
//    ch=BYTE3(temp);
//    my_putchar(ch);
//  }
// /*****************************************************/
// my_putchar(0xf2); //代表整个数据都发完了
 
}

//#define LIM 255
//#define LINE_Far 120
//#define GAP_THRE 20
//uint8 bais;
//int GO,NO;   //速度控制
//uint8 N0,N1,N2,Np; 
//float slope_speed;
//float flope_temp;
//uint8 lose_brick;
//uint8 con_brick;
//uint8 str_L,str_L1,str_L2,str_R,str_R1,str_R2,LL,LL1,LL2,LR,LR1,LR2,RR,RR1,RR2,RL,RL1,RL2;
//float slope_qj;
//int slope_q[3][120];    //储存斜率
//uint8 end_line;  //有效行末行
//uint8 line=30; //控制行
//uint8 line_c;
//uint8  RoadType=0;   //右圆环2   左圆环3  十字1  直道4
//float Previous_Error[20];
//int Loc[3][LINE_Far];
//float character_distance;//赛道特征点的位置
//uint8 continue_line_left=0,continue_line_right=0,left_end_line;
//uint16 edgposition[CAMERA_H];
//int devi_far;
//uint8 continue_straight_line_left=0, continue_straight_line_right=0,left_head_line,right_head_line,right_end_line;
//int rightround_state=0;
//int round_clear[3]={0,0,0};
//int search_end_line;
//uint16 cont;
//uint8 control_line,stop_line=0;
//uint8 control_line_near,control_line_far;
//uint8 straight_count=0;
//float close_slope;
//int close_slope_temp;
//static float SpeedDevi_His[10] = {0};
//uint8 il,ir;   //左右拐点wk
//uint8 xierushizi=0;
//uint8 failcount=0;
//uint8 middle_continue,left_continue,right_continue;
//uint8 times_count=0;
//int curve_left,curve_right;
//uint8 last_control_line=255;
//uint8 S_flag=0,first_white_right;
//uint8 stage2_count=0;
//int map_y[60]={-778	,-1321	,-4745	,2815	,1062	,645	,458	,352	,284	,236 /*10*/	,201	,174	,153	,136	,119 /* 121*/	,109	,99	,90	,82	,75 /*20*/	,69	,64	,59	,54	,51	,47	,44	,41	,38	,35 /*30*/	,33	,30	,28	,26	,25	,23	,21	,20	,18	,17 /*40*/	,16	,14	,13	,12	,11	,10	,9	,8	,7	,7 /*50*/	,6	,5	,4	,3	,3	,2	,2	,1	,0	,0};
//uint8 fuzzy_line[9]={30,25,21,17,15,14,13,12,11};
//uint8 half_width[60] = {7,7,7,7,7,8,9,10,11,12,13,14,15,16,17,18,18,19,19,20,
//20,21,21,22,22,23,24,24,25,25,26,26,27,28,28,29,29,30,30,
//31,31,31,32,32,33,33,34,34,34,35,35,35,36,36,37,37,37,37,38,38};
//int AllWhileStartLine,AllWhileEndLine;
//uint8 turn_point=60;   //拐点对应的行数wk
//uint8 circle_stage=0;
//int slopeL[60],slopeR[60];
//uint8 count_right,count_left,slopeL_index,slopeR_index,curve_liner_left,curve_liner_right,curve_linel_left,curve_linel_right,straight_right,straight_left,white_left,white_right,turn_flag;
//int SlopeLmax,SlopeLmin,SlopeRmax,SlopeRmin;
//float Middle_Err_Sum,Middle_Err_Sum_Near,Middle_Err_Sum_Middle,Middle_Err_Sum_Far;
//uint8 middle_right,middle_left,middle_straight,middle_right_q,middle_left_q,middle_straight_q;
//uint8 Black_record[10]={40,40,40,40,40,40,40,40,40,40};
//float ARCTANG[80] = {0	,1.1458	,2.2906	,3.4336	,4.5739	,5.7106	,6.8428	,7.9696	,9.0903	,10.204	,11.3099	,12.4074	,13.4957	,14.5742	,15.6422	,16.6992	,17.7447	,18.778	,19.7989	,20.8068	,21.8014	,22.7824	,23.7495	,24.7024	,25.641	,26.5651	,27.4744	,28.369	,29.2488	,30.1137	,30.9638	,31.7989	,32.6192	,
//33.4248	,34.2157	,34.992	,35.7539	,36.5014	,37.2348	,37.9542	,38.6598	,39.3518	,40.0303	,40.6955	,41.3478	,41.9872	,42.6141	,43.2285	,43.8309	,44.4213	,45	,45.5673	,46.1233	,46.6683	,47.2026	,47.7263	,48.2397	,48.743	,49.2364	,49.7201	,50.1944	,50.6595	,51.1155	,51.5627	,52.0013	,
//52.4314	,52.8533	,53.2672	,53.6732	,54.0715	,54.4623	,54.8458	,55.2222	,55.5915	,55.9541	,56.3099	,56.6593	,57.0023	,57.3391	,57.6698
//};
//void Push_And_Pull(float *buff,int len,float newdata)
//{
//	int i;
//	for(i=len-1;i>0;i--)
//	{
//		*(buff+i)=*(buff+i-1);
//	}
//	*buff=newdata; 
//}
//void Push_And_Pull_int(int *buff,int len,int newdata)
//{//0最新
//	int i;
//	for(i=len-1;i>0;i--)
//	{
//		*(buff+i)=*(buff+i-1);
//	}
//	*buff=newdata; 
//}
//float  delta_error_Filter(float delta)    //转向控制输出滤波      
//{
//	float delta_Filtered; 
//	static float Pre_Error[4]; 
//	Pre_Error[3]=Pre_Error[2];
//	Pre_Error[2]=Pre_Error[1];
//	Pre_Error[1]=Pre_Error[0];
//	Pre_Error[0]=delta;
//	delta_Filtered=Pre_Error[0]*0.5+Pre_Error[1]*0.2+Pre_Error[2]*0.2+Pre_Error[3]*0.1;
//	return delta_Filtered;
//}
//
//float Slope_Calculate_Uint8(uint8 begin,uint8 end,int *p)    //最小二乘法拟合斜率
//{
//	float xsum=0,ysum=0,xysum=0,x2sum=0;
//	uint8 i=0;
//	int temp=40;
//	float result=0;
//	static float resultlast;
//	p=p+begin;
//	temp=*p;
//	for(i=begin;i<end;i++)
//	{
//		xsum+=i;
//		ysum+=*p-temp;
//		xysum+=i*(*p-temp);
//		x2sum+=i*i;
//		p=p+1;
//	}
//	if((end-begin)*x2sum-xsum*xsum) //判断除数是否为零 
//	{
//		result=((end-begin)*xysum-xsum*ysum)/((end-begin)*x2sum-xsum*xsum);
//		resultlast=result;
//	}
//	else
//	{
//		result=resultlast;
//	}
//	return result;
//}
//
//
//void sendimg()
//{
//	uint8 ch=0;
//	float temp=0;
//	uint16 i=0,num,j;
//	my_putchar(0x55);
//	my_putchar(0xaa);
//	my_putchar(0xff);
//	my_putchar(0xa2);
//	my_putchar(RoadType); //小车状态
//	
//	num=cont+2+180+36;  
//	//统计将要传输的数据量 2是因为要传输关键字即0xf0和0xf2   (0xf2 所有数据结束，0xf0图像数据结束，180=60*3)
//	//180是边线的位 36是变量的位 如果不传输就不要加上！
//	
//	my_putchar(BYTE0(num)); 
//	my_putchar(BYTE1(num));
//	for(i=0;i< cont;i++)
//	{
//		my_putchar(img_edg[i]);
//	}
//	my_putchar(0xf0);  //代表图像数据发完了
//	/******************星号围起来的可以不传输*******************/
//	// for(i=179;i>=0;i--)
//	// {
//	////  if(Loc[i*2/LINE_Far][i*2%LINE_Far]/2>=-40 && Loc[i*2/LINE_Far][i*2%LINE_Far]/2<=40)
//	//  my_putchar( Loc[(179-i)*2/LINE_Far][i*2%LINE_Far]/2+40);
//	// }
//	for(i=0;i<3;i++)
//	{
//		for(j=60;j>0;j--)
//		{
//			if(Loc[i][(j-1)*2]<=80 && Loc[i][(j-1)*2]>=-80)
//				my_putchar(Loc[i][(j-1)*2]/2+40);
//			else 
//				my_putchar(0);
//		}
//	}
//	for(i=0;i<9;i++)
//	{
//		temp=sVariable[i];
//		ch=BYTE0(temp);
//		my_putchar(ch);
//		ch=BYTE1(temp);
//		my_putchar(ch);
//		ch=BYTE2(temp);
//		my_putchar(ch);
//		ch=BYTE3(temp);
//		my_putchar(ch);
//	}
//	/*****************************************************/
//	my_putchar(0xf2); //代表整个数据都发完了
//	
//}
//uint8 absint(uint8 a,uint8 b)
//{
//	return (a<b)?(b-a):(a-b);
//}
//
//void get_edge_left(uint8 line,uint8 start_point)   //0黑
//{
//	uint8 x,i,j,n,temp;
//	x=10*line;
//	j=start_point/8;
//	
//	
//	for(;j>=0;j--)
//	{
//		if(imgbuff_process[x+j]==0xff)
//		{
//			continue;
//		}
//		else if(imgbuff_process[x+j]==0)
//		{
//			LMR[0][line]=j*8;
//			break;
//		}
//		else
//		{
//			for(n=0;n<=7;n++)
//			{
//				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
//				if(temp==1) 
//				{
//					continue;
//				}
//				else 
//				{
//					LMR[0][line]=j*8+7-n;
//					break;
//				}
//			} 
//			
//		}
//	}
//	
//}
//
//void get_edge_right(uint8 line,uint8 start_point)   //0黑
//{
//	uint8 x,i,j,n,temp;
//	x=10*line;
//	j=start_point/8;
//	
//	for(;j<10;j++)
//	{
//		if(imgbuff_process[x+j]==0xff)
//		{
//			continue;
//		}
//		else if(imgbuff_process[x+j]==0)
//		{
//			LMR[0][line]=j*8;
//		}
//		else
//		{
//			for(n=7;n>=0;n--)
//			{
//				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
//				if(temp==1) 
//				{
//					continue;
//				}
//				else 
//				{
//					LMR[2][line]=j*8+7-n;
//				}
//			} 
//			
//		}
//	}
//	
//}
//
//
//
//void get_edge()   //尽量减少乘法运算
//{
//	static int16 i=0,j=0,last=0,x=0,y=0,n=0;
//	uint8 temp=0,find=0;
//	cont=0;
//	uint8 flag_ban=0;
//	uint8 flag_bw=0;
//	uint8 qipao=0;
//	for(i=0;i<60;i++)
//	{
//		last=0; 
//		x=i*10;
//		find=0;
//		edgposition[i]=0;
//		flag_bw=0;
//		
//		for(j=0;j<10;j++)
//		{
//			if(imgbuff_process[x+j]==0xff)
//			{
//				if(j>=3 && j<=6)flag_bw++;
//				if(last==0)
//				{
//					y=j<<3;
//					if(find==0)
//					{
//						edgposition[i]=cont;
//					}
//					img_edg[cont++]=y;   //左移动5相当于乘以32 左移动3相当于乘以8 
//					find=1;
//				}
//				last=1;
//				continue;
//			}
//			if(imgbuff_process[x+j]==0)
//			{
//				if(j>=3 && j<=6)flag_bw++;
//				if(last==1)
//				{          
//					y=j<<3;
//					if(find==0)
//					{
//						edgposition[i]=cont;
//					}
//					img_edg[cont++]=y;   //左移动5相当于乘以32 左移动3相当于乘以8  
//					find=1;
//				}
//				last=0;
//				continue;
//			}
//			
//			for(n=7;n>=0;n--)
//			{
//				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
//				if(temp!=last) //与上一个值不相同 出现了跳变沿            
//				{
//					y=j<<3;  
//					if(find==0)
//					{
//						edgposition[i]=cont;
//					}
//					img_edg[cont++]=y+7-n;   //左移动5相当于乘以32 左移动3相当于乘以8 
//					find=1;
//				}
//				last=temp;                //存储该点的值
//			} 
//		} 
//		img_edg[cont++]=0xff;   //左移动5相当于乘以32 左移动3相当于乘以8
//		if(i<50 && i>30 && flag_bw==0 && cont-edgposition[i]>17 ) 
//		{
//			if(Distance>25)Stop=1;
//			qipao++;
//		}
//		
//	}
//	if(qipao>=1)stop_line=1;
//	else stop_line=0;
//	
//}
///*img_edg是一个一维数组 记录了摄像头每行的跳变沿的坐标值  每行跳变沿 由上升沿开始（由黑变白）然后接下降沿（由白变黑） 
//0xff用于指示该行的跳变沿完了，开始记录下一行
//如果每行图像以白色部分开始，那么该行跳变沿起始位置为0
//如果该行全黑 那么该行记录为0xff
//如果该行为全白 记录为 0 0xff
//
//
//oxff代表本行坐标值结束，进入下一行
////edgposition[i]代表第i行的 跳变沿 在 img_edg 中坐标起点
//
//*/
//void fix_break_line() //修复断开的线
//{
//	
//}
//void slope_curve_get(void)
//{
//	uint8 count=0,i;
//	for(i=59;i>0;i=i-2)
//	{
//		if(LMR[0][i]!=0 && LMR[0][i-2]!=0)
//		{
//			count=0;
//			slopeL[slopeL_index++]=(LMR[0][i-2]-LMR[0][i])*100;
//		}
//		else 
//			count++;
//		
//		if(count>10)break;
//	}
//	
//	
//	for(i=59;i>0;i=i-2)
//	{
//		if(LMR[2][i]!=0 && LMR[2][i-2]!=0)
//		{
//			slopeR[slopeR_index++]=(LMR[0][i-2]-LMR[0][i])*100;
//		}
//		else 
//			count++;
//		if(count>5 && slopeR_index>6)break;
//	}
//	
//	
//	
//}
//
//uint8 find_circle(uint8 *src,uint8 startline)    //寻找环状黑线
//{
//	uint8 i;
//	uint8 turn_left=0,turn_right=0;
//	uint8 countl=0,countr=0,count=0;;
//	for(i=startline;i>startline-24;i=i-2)
//	{
//		if(src[i-2]<src[i])
//		{
//			countr=0;
//			countl++;
//			if(countl==1 && turn_right==1)
//			{
//				turn_right=2;      
//			}
//			else if(countl==5 && turn_right==0)
//			{
//				turn_left=1;
//			}
//		}
//		if(src[i-2]>src[i])
//		{
//			countl=0;
//			countr++;
//			if(countr==1 && turn_left==1)
//			{
//				turn_left=2;      //先左后右
//			}
//			else if(countr==5 && turn_left==0)
//			{
//				turn_right=1;
//			}
//		}   
//		
//		if(src[i-2]==0||src[i-2]==80)
//		{
//			break;
//		}
//	}
//	
//	if(turn_left==2 && turn_right!=2) return 1;
//	else if(turn_left!=2 && turn_right==2) return 2;
//	else return 0;
//	
//}
//
//void fix_line(uint8 *src,uint8 startline)
//{
//	uint8 i;
//	int slope;
//	slope=(src[startline+4]-src[startline+6]+src[startline+3]-src[startline+5]);
//	for(i=startline;i>0;i--)
//	{
//		src[i]=src[i+4]+slope;
//		if(src[i]>75||src[i]<5)break;
//	}
//	
//}
//
//void insert(uint8 lr,uint8 start,uint8 end)
//{
//	uint8 i;
//	float slope;
//	slope=(Loc[lr][end]-Loc[lr][start])*1.0/(end-start);
//	for(i=start+1;i<end;i++)
//	{
//		Loc[lr][i]=(int)(Loc[lr][start]+slope*(i-start));
//	}
//}
//uint8 break_point_find(uint8 *src)   //寻找拐点 wk
//{
//	uint8 i;
//	int deta=0;
//	int deta_pre=255;
//	int deta_pre2=255;
//	int deta_pre3=255;
//	uint8 count=0;
//	for(i=56;i>0;i-=2)
//	{
//		if(src[i]!=0 && src[i]!=80 && src[i+2]!=0 && src[i+2]!=80 && absint(src[i],src[i+2])<10)
//		{
//			count=0;
//			deta_pre3=deta_pre2;
//			deta_pre2=deta_pre;
//			deta_pre=deta;
//			deta=(src[i]-src[i+2])*10;
//			if(deta_pre2!=255)
//			{
//				if(deta_pre2*deta<-390)    //break_point_find修改，前面有*10 wk
//					return i+2;
//			}
//			if(deta_pre3!=255)
//			{
//				if(deta_pre3*deta<-390)    //break_point_find修改，前面有*10 wk
//					return i+4;
//			}
//		}
//		else
//		{
//			count++;
//		}
//		if(count==2)
//		{
//			deta_pre2=255;
//			deta_pre=255;
//			deta=0;    
//		}  
//		if(count>18 || i < 20)
//		{
//			break;
//		}
//	}
//	return 60;
//}
//
//
//void Search()
//{
//	//从底部往上搜线
//        uint8 fix_flag=0;
//	uint8 start_brick=255,stop_brick=255;
//	uint8 brick_dir=255;  //0左 1右
//	static uint8 ruwan_flag;
//	static uint8 search_time;
//        static uint8 wait_time;
//	float slope;
//	static int i,j,find;
//	uint8 left_cont=0,right_cont=0;
//	static float Middle_Temp=0;
//	uint8 L_end_line=0,R_end_line=0;
//	int leftfind=0,rightfind=0;
//	int slopeL_last=255,slopeR_last=255;
//	static int break_line_left=0,break_line_right=0;
//	uint8 temp=0;
//	uint8 slope_line=0;
//	int temp_slope;
//	uint8 half=25; //赛道半宽
//	uint8 zuo_break,you_break;
//	//int continue_straight_line_left=0, continue_straight_line_right=0;
//	for(i=0;i<60;i++)  //清空数组
//	{  
//		LMR[0][i]=0; //左边线数列
//		LMR[1][i]=40;  //中线数列
//		LMR[2][i]=80; //右边线数列
//	}
//	for(i=0;i<30;i++)
//	{
//		slope_q[0][i]=255;
//		slope_q[1][i]=255;
//		slope_q[2][i]=255;
//	}
//	for(i=0;i<LINE_Far;i++)  //清空数组
//	{ 
//		Loc[0][i]=-LIM;
//		Loc[1][i]=LIM;
//		Loc[2][i]=LIM;
//	}
//	search_time++;
//	con_brick=0;
//	end_line=0;
//	first_white_right=60;
//	S_flag=0;
//	zuo_break=0;
//	you_break=0;
//	curve_left=curve_right=0;
//	devi_far=0;
//	middle_continue=60;
//	left_continue=60;
//	right_continue=60;
//	AllWhileStartLine=AllWhileEndLine=0;
//	middle_right=middle_left=middle_straight=0;
//	middle_right_q=middle_left_q=middle_straight_q=0;
//	close_slope=0;
//	search_end_line=0;
//	count_right=count_left=0;
//	curve_liner_left=curve_liner_right=curve_linel_left=curve_linel_right=straight_right=straight_left=white_left=white_right=0;
//	SlopeLmax=SlopeRmax=-255;
//	SlopeLmin=SlopeRmin=255;
//	slopeL_index=0;
//	slopeR_index=0;
//	str_L=0,str_L1=0,str_L2=0,str_R=0,str_R1=0,str_R2=0,LL=0,LL1=0,LL2=0,LR=0,LR1=0,LR2=0,RR=0,RR1=0,RR2=0,RL=0,RL1=0,RL2=0;
//	leftfind=0;
//	rightfind=0;
//	break_line_left=0;
//	break_line_right=0;
//	continue_line_left=0;
//	continue_line_right=0;
//	left_head_line=255;
//	right_head_line=255;
//	left_end_line=255;
//	right_end_line=255;
//	Middle_Err_Sum_Near=0;
//	Middle_Err_Sum_Far=0;
//	Middle_Err_Sum=0;
//	for(i=59;i>13;i--) //从第59行开始搜线 至11行
//	{
//		if(edgposition[i]==0) //全黑行 置为丢线
//		{
//			break;
//		}
//		j=edgposition[i];//该行跳变沿开始的位置  j代表黑变白 即左边线 j+1代表变黑 即右边线 
//		if(i==59)  //底部开始行
//		{   
//			while(img_edg[j]!=255)
//			{  
//				if((img_edg[j]<Black_record[9])&&(img_edg[j+1]>Black_record[9]))  //左边沿小于55 右边沿大于25
//				{
//					if((img_edg[j+1]-img_edg[j])>20) //右边沿-左边沿大于20
//					{
//						LMR[0][i]=img_edg[j];
//						
//						if(img_edg[j+1]==255)
//						{
//							LMR[2][i]=80;      
//						}
//						else
//						{
//							LMR[2][i]=img_edg[j+1];
//							
//						}
//						break;//while
//					}
//				} 
//				if(img_edg[j+1]==255)
//				{
//					break;//while
//				}
//				j=j+2;
//			}
//			
//			//  if(LMR[0][i]==0)  break_line_left=59;
//			// if(LMR[2][i]==80) break_line_right=59;
//		}
//		else   //不是底部开始行
//		{ 
//			find=0;
//			while(img_edg[j]!=255)
//			{
//				if((img_edg[j]<=LMR[2][i+1])&&(img_edg[j+1]>=LMR[0][i+1])&&(img_edg[j+1]-img_edg[j])>15)     //左边沿小于上一行的右边线 右边沿大于上一行的左边线是连通域；  //差值改为13 kk
//				{
//					find=1;
//					if(LMR[0][i]==0&& img_edg[j]!=0 /*&& !(absint(img_edg[j],LMR[0][i+1])>12 && LMR[0][i+1]!=0)*/)     //阈值修改为6 kk
//					{
//						if(LMR[2][i]==80)
//						{
//							//             if(left_head_line==60 || slopeL_last==255)
//							//             {
//							//              LMR[0][i]=img_edg[j];
//							//              if(LMR[0][i+1]!=0)slopeL_last=LMR[0][i]-LMR[0][i+1];
//							//             }
//							//             else if(LMR[0][i+1]!=0)
//							//             {
//							//               if(ABS(img_edg[j]-LMR[0][i+1]-slopeL_last)<(ABS(slopeL_last)/5*8+5))
//							//               {
//							//                  LMR[0][i]=img_edg[j];
//							//                  slopeL_last=LMR[0][i]-LMR[0][i+1];
//							//               }
//							//             }
//							//             else if(ABS(img_edg[j]-LMR[0][left_end_line])<15)
//							//             {
//							//                LMR[0][i]=img_edg[j];
//							//             }
//							//             else
//							//             {
//							//                LMR[0][i]=0;
//							//             }
//							if(i>56)
//							{
//								if(img_edg[j]<Black_record[i-50])LMR[0][i]=img_edg[j];
//								else LMR[0][i]=0;
//							}
//							else LMR[0][i]=img_edg[j];
//							//             if(LMR[0][i]!=0)
//							//             {
//							//               leftfind=1;
//							//               left_end_line=i;
//							//               if(left_head_line==60)left_head_line=i;
//							//             }
//						}
//						
//					} 
//					if(img_edg[j+1]!=255&&(LMR[2][i]==80)&& !(absint(img_edg[j+1],LMR[2][i+1])>12 && LMR[2][i+1]!=80))
//					{
//						//              if(LMR[2][i+1]==80 || (absint(LMR[2][i+1],img_edg[j+1])<12))
//						//              {
//						//                if(right_head_line==60 || slopeR_last==255)
//						//                {
//						//                  LMR[2][i]=img_edg[j+1];
//						//                  if(LMR[2][i+1]!=80)slopeR_last=LMR[2][i]-LMR[2][i+1];
//						//                }  
//						//                else if(LMR[2][i+1]!=80)
//						//                {
//						//                  if(ABS(img_edg[j+1]-LMR[2][i+1]-slopeR_last)<(ABS(slopeR_last)/5*8+5))
//						//                  {
//						//                    LMR[2][i]=img_edg[j+1];
//						//                    slopeR_last=LMR[2][i]-LMR[2][i+1];
//						//                  }
//						//                }  
//						//               else if(ABS(img_edg[j+1]-LMR[2][left_end_line])<15)
//						//               {
//						//                  LMR[2][i]=img_edg[j+1];
//						//               }
//						//               else
//						//               {
//						//                  LMR[2][i]=80;
//						//               }
//						if(i>50)
//						{
//							if(img_edg[j+1]>Black_record[i-50])LMR[2][i]=img_edg[j+1];
//							else LMR[2][i]=80;
//						}
//						else LMR[2][i]=img_edg[j+1];
//						//               if(LMR[2][i]!=80)
//						//               {
//						//                 LMR[2][i]=img_edg[j+1];
//						//                 rightfind=1;
//						//                 right_end_line=i;
//						//                 if(right_head_line==60)right_head_line=i;
//						//               }
//						//              }
//					}
//				}
//				if(img_edg[j+1]==255) //该行的跳变沿结束了
//				{
//					if(img_edg[j]==0) //说明该行为全白 
//					{ 
//						if(AllWhileStartLine==0)
//						{
//							AllWhileStartLine=i; //全白行开始的位置
//						}
//						AllWhileEndLine=i;
//					}
//					break;//while
//				}
//				if(img_edg[j+1]>77 && img_edg[j]<3)
//				{
//					
//					if(AllWhileStartLine==0)
//					{
//						AllWhileStartLine=i; //全白行开始的位置
//					}
//					AllWhileEndLine=i;
//					
//					break;//while
//					
//				}
//				j=j+2;
//			}
//			//以上是搜索连通域的算法
//			//       if(i<58 && i>10)
//			//       {
//			//         if(LMR[0][i+2] !=0 && LMR[0][i+1] !=0 && LMR[0][i] !=0 && absint(LMR[0][i],LMR[0][i+2])<8)
//			//         {
//			//            if(LMR[0][i]<LMR[0][i+1])curve_linel_left++;
//			//            else if(LMR[0][i]>LMR[0][i+1])curve_linel_right++;
//			//            if((i>30 && LMR[0][i]<=LMR[0][i+2]+1 && LMR[0][i+2]<=LMR[0][i]) || (i>8 && i<=30 && LMR[0][i]<=LMR[0][i+1]+1 && LMR[0][i+1]<=LMR[0][i])) straight_left++;
//			//            temp_slope=LMR[0][i]-LMR[0][i+2];
//			//            if(temp_slope>SlopeLmax && i>20)SlopeLmax=temp_slope;
//			//            if(temp_slope<SlopeLmin && i>20)SlopeLmin=temp_slope;
//			//            if((temp_slope>=2 && i>30) || (temp_slope>=3 && i<=30 && i>10))count_right++;
//			//         }
//			//         if(LMR[2][i+1] !=80 && LMR[2][i] !=80 && LMR[2][i+2] !=80 && absint(LMR[2][i],LMR[2][i+2])<8)
//			//         {
//			//            if(LMR[2][i]<LMR[2][i+1])curve_liner_left++;
//			//            else if(LMR[2][i]>LMR[2][i+1])curve_liner_right++;
//			//            if((i>30 && LMR[2][i]>=LMR[2][i+2]-1 && LMR[2][i+2]>=LMR[2][i]) || (i>8 && i<=30 && LMR[2][i]>=LMR[2][i+1]-1 && LMR[2][i+1]>=LMR[2][i])) straight_right++;
//			//            temp_slope=LMR[2][i]-LMR[2][i+2];
//			//            if(temp_slope>SlopeRmax && i>20)SlopeRmax=temp_slope;
//			//            if(temp_slope<SlopeRmin && i>20)SlopeRmin=temp_slope;
//			//            if((temp_slope<=-2 && i>30) || (temp_slope<=-3 && i<=30 && i>10))count_left++;
//			//         }
//			//       }       
//			
//			//       if(find==0)//没有找到连通区域
//			//       {
//			//         if(i<20)
//			//         search_end_line=i;
//			//         i++; 
//			//         break;//for
//			//       }
//			
//		}
//		//    if(i<55 && i>25 && LMR[0][i]==0)zuo_break++;
//		//    if(i<55 && i>25 && LMR[2][i]==80)you_break++;
//		//    if(i<55 && i>20)
//		//    {
//		//      if(LMR[2][i]==80 && LMR[2][i+1]==80 && LMR[2][i+2]!=80 && LMR[2][i+3]!=80 && white_right==0)white_right=i+1;
//		//      if(LMR[0][i]==0 && LMR[0][i+1]==0 && LMR[0][i+2]!=0 && LMR[0][i+3]!=0 && white_left==0)white_left=i+1;
//		//    }
//		//    if(i<59 && LMR[2][i]==0 && LMR[2][i+1]==0)first_white_right=i+1;
//	}
//	
//	
//	
//	//================================================================================================================================//
//	//逆透视
//	//================================================================================================================================//
//	uint8 y2,last_y0,last_y2;
//	last_y0=0;
//	last_y2=0;
//	for(i=59;i>13;i--)
//	{
//		y2=map_y[i];
//		if(LMR[0][i]!=0)
//		{ 
//			Loc[0][y2]=map[i][LMR[0][i]];
//			if(Loc[0][y2]>=80)Loc[0][y2]=LIM;
//			else if(Loc[0][y2]<-80)Loc[0][y2]=-LIM;
//			else
//			{
//				if(y2-last_y0>1 && y2-last_y0<12 && last_y0!=0)
//				{
//					insert(0,last_y0,y2);
//				}
//				last_y0=y2;
//			}
//		}
//		if(LMR[2][i]!=80)
//		{
//			Loc[2][y2]=map[i][LMR[2][i]];
//			if(Loc[2][y2]>80)Loc[2][y2]=LIM;
//			else if(Loc[2][y2]<-80)Loc[2][y2]=-LIM;
//			else
//			{
//				if(y2-last_y2>1 && y2-last_y2<11 && last_y2!=0)
//				{
//					insert(2,last_y2,y2);
//				}
//				last_y2=y2;
//			}
//		}
//	}
//	for(i=3;i<100;i++)
//	{
//		if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
//		{
//			con_brick++;
//		}
//	}
//	//================================================================================================================================//
//	//十字判断
//	//================================================================================================================================//
//	if((AllWhileStartLine-AllWhileEndLine)>8 && RoadType==0)  
//		//且两边边线都找到过 排除顶部20行的干扰
//	{
//		RoadType=1; //进入十字了
//	}
//	if(RoadType==1 && AllWhileEndLine==0)
//	{
//		RoadType=0;
//	}
//	//================================================================================================================================//
//	//有效性判断
//	//================================================================================================================================//
//	//障碍物判断
//	
//	uint8 gapl=0,gapr=0;
//	uint8 losel=0,loser=0;
//	if(RoadType==4)
//	{
//		for(i=3;i<100;i++)
//		{
//			if(Loc[0][i]!=-LIM && Loc[2][i]!=LIM)
//			{
//				if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
//				{
//					if(start_brick==255)
//					{
//						start_brick=i;
//					}
//					if(brick_dir==255)
//					{
//						if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]>10 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]<8 )brick_dir=1;
//						else if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]<8 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]>10 )brick_dir=0;
//						else brick_dir=255;
//					}
//				}
//				else
//				{
//					if(stop_brick-start_brick>12)
//					{
//						RoadType=5;
//						break;
//					}
//					if(stop_brick-start_brick<5)
//					{
//						start_brick=255;
//						brick_dir=255;
//					}
//				}
//			}
//			else
//			{
//				if(stop_brick-start_brick>12)
//				{
//					RoadType=5;
//					break;
//				}
//				if(stop_brick-start_brick<5)
//				{
//					start_brick=255;
//					brick_dir=255;
//				}
//			}       
//		}
//		end_line=90;
//		left_end_line=90;
//		right_end_line=90;
//	}
//	
//	else if(RoadType==5 ||(con_brick>6 && RoadType==0))
//	{
//		for(i=3;i<100;i++)
//		{
//			if(Loc[0][i]!=-LIM && Loc[2][i]!=LIM)
//			{
//				if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
//				{
//					if(start_brick==255)start_brick=i;
//					stop_brick=i;
//					if(brick_dir==255)
//					{
//						if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]>10 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]<8 )brick_dir=1;
//						else if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]<8 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]>10 )brick_dir=0;
//						else brick_dir=255;
//					}
//					if(stop_brick-start_brick>12)
//					{
//						break;
//					}
//				}
//				else
//				{
//					if(stop_brick-start_brick>12)
//					{
//						break;
//					}
//					if(stop_brick-start_brick<5)
//					{
//						start_brick=255;
//						brick_dir=255;
//					}
//				}
//			}
//			else
//			{
//				if(stop_brick-start_brick>12)
//				{
//					break;
//				}
//				if(stop_brick-start_brick<5)
//				{
//					start_brick=255;
//					brick_dir=255;
//				}
//			}
//			
//		}
//		if(brick_dir==255)lose_brick++;
//		else lose_brick=0;
//		if(lose_brick>20)
//		{
//			RoadType=0;
//			lose_brick=0;
//		}
//		else
//		{
//			left_end_line=stop_brick;
//			right_end_line=stop_brick;
//			end_line=stop_brick;
//		}
//	}
//	
//	else if(RoadType==1)
//	{
//		last_y0=255;
//		last_y2=255;
//		uint8 fl=0,fr=0;
//		if(Loc[0][1]>-36 && Loc[2][1]<36)
//		{
//			for(i=3;i<120;i++)
//			{
//				
//				if(last_y0==255 &&(Loc[0][i]-Loc[0][i-3]<-3||Loc[0][i]==-LIM) && Loc[0][i-3]!=-LIM)
//				{
//					last_y0=i-3;
//				}
//				if(fl==0 && last_y0!=255  &&ABS(Loc[0][i]-Loc[0][i+1])<3 && ABS(Loc[0][i+2]-Loc[0][i+3])<2 && Loc[0][i]>-35)
//				{
//					fl=i+1;
//					continue_line_left=i+1;
//					insert(0,last_y0,i+1);
//					left_end_line=i+30;
//				}
//				if(last_y2==255 &&(Loc[2][i]-Loc[2][i-3]>3 ||Loc[2][i]==LIM) && Loc[2][i-3]!=LIM)
//				{
//					last_y2=i-3;
//				}
//				if(fr==0 && last_y2!=255  &&ABS(Loc[2][i]-Loc[2][i+1])<3 && ABS(Loc[2][i+2]-Loc[2][i+3])<2 && Loc[2][i]<35)
//				{
//					fr=i+1;
//					continue_line_right=i+1;
//					insert(2,last_y2,i+1);
//					right_end_line=i+30;
//				}
//				if((i>fl+9 && fl!=0) || (i>fr+9&&fr!=0) )
//				{
//					end_line=(fl+fr)/2+18;
//					break;
//				}
//			}
//		}
//		else
//		{
//			for(i=5;i<120;i++)
//			{
//				if(fl==0&& Loc[0][i-5]==-LIM && ABS(Loc[0][i]-Loc[0][i+1])<3 && ABS(Loc[0][i+2]-Loc[0][i+3])<2 && Loc[0][i]>-35)
//				{
//					fl=i;
//					continue_line_left=i+1;
//					for(j=0;j<i+1;j++)Loc[0][j]=Loc[0][i+2];
//					left_end_line=i+30;
//				}
//				if(fr==0 && Loc[2][i-5]==LIM && ABS(Loc[2][i]-Loc[2][i+1])<3 && ABS(Loc[2][i+2]-Loc[2][i+3])<2 && Loc[2][i]<35)
//				{
//					fr=i;
//					continue_line_right=i+1;
//					for(j=0;j<i+1;j++)Loc[2][j]=Loc[2][i+2];
//					right_end_line=i+30;
//				}
//				if((i>fl+9 && fl!=0) || (i>fr+9&&fr!=0) )
//				{
//					end_line=(fl+fr)/2+18;
//					break;
//				}
//			}
//		}
//	}
//	//除十字赛道判断有效性
//	if(RoadType!=5 && RoadType!=1)
//	{
//		last_y0=4;
//		last_y2=4;
//		for(i=5;i<120;i++) 
//		{
//			if(Loc[0][i]!=-LIM && Loc[0][i-1]!=-LIM && Loc[0][i-2]!=-LIM && Loc[0][i-3]!=-LIM)
//			{
//				slope_q[0][i]=(Loc[0][i]-Loc[0][i-2]+Loc[0][i-1]-Loc[0][i-3])*100;
//			}
//			if(Loc[2][i]!=LIM && Loc[2][i+1]!=LIM && Loc[2][i+2]!=LIM && Loc[2][i+3]!=LIM)
//			{
//				slope_q[2][i]=(Loc[2][i]-Loc[2][i-2]+Loc[2][i-1]-Loc[2][i-3])*100;
//			}
//			if(Loc[0][i]!=-LIM)
//			{
//				if(losel==0)
//				{
//					gapl=0;
//					if((Loc[0][i-2]!=-LIM && (ABS(slope_q[0][i]-slope_q[0][i-4])<=100|| slope_q[0][i-4]==255 ||slope_q[0][i]==255) && ABS( Loc[0][i]-Loc[0][i-2])<=4)||(Loc[0][i-2]==-LIM && Loc[0][i+2]!=LIM && /*ABS(Loc[0][i+2]-Loc[0][i]-Loc[0][last_y2]+Loc[0][last_y2-2])<=3 && */ABS( Loc[0][i]-Loc[0][last_y0])<=9 && last_y0!=4) ||(Loc[0][i-2]==-LIM  && Loc[0][i]<0 && last_y0==4))
//					{
//						if(i-last_y0<GAP_THRE )
//						{
//							left_end_line=i;
//							if(left_head_line==255)left_head_line=i;
//							losel=0;
//							if(last_y0!=4 && i-last_y0>1)
//							{
//								insert(0,last_y0,i);
//							}
//							last_y0=i;
//						}
//						else
//						{
//							losel=1;
//							Loc[0][i]=-LIM;
//						}
//					}
//					else
//					{
//						if(i-last_y0>=GAP_THRE)losel=1;
//						Loc[0][i]=-LIM;
//						
//					}
//				}
//			}
//			else 
//			{
//				gapl++;
//			}
//			if(Loc[2][i]!=LIM )
//			{
//				if(loser==0)
//				{
//					gapr=0;
//					if((Loc[2][i-2]!=LIM && (ABS(slope_q[2][i]-slope_q[2][i-4])<=100 || slope_q[2][i-4]==255 ||slope_q[2][i]==255) && ABS( Loc[2][i]-Loc[2][i-2])<=4)||(Loc[2][i-2]==LIM && Loc[2][i+2]!=LIM /*&& ABS(Loc[2][i+2]-Loc[2][i]-Loc[2][last_y2]+Loc[2][last_y2-2])<=3 */&&  ABS( Loc[2][i]-Loc[2][last_y2-2])<=6 && last_y2!=4) ||(Loc[2][i-2]==LIM  && Loc[2][i]>0 && last_y2==4))
//					{
//						if(i-last_y2<GAP_THRE)
//						{
//							right_end_line=i;
//							if(right_head_line==255)right_head_line=i;
//							loser=0;
//							if(last_y2!=4 && i-last_y2>1)
//							{
//								insert(2,last_y2,i);
//							}
//							last_y2=i;
//						}
//						else
//						{
//							loser=1;
//							Loc[2][i]=LIM;
//						}
//					}
//					else
//					{
//						if(i-last_y2>=GAP_THRE)loser=1;
//						Loc[2][i]=LIM;
//					}
//				}
//			}
//			else
//			{
//				gapr++;
//			}
//			if((loser==1 && losel==1) || (gapr>10 && losel==1) || (loser==1 && gapl>10))
//			{
//				if(last_y2>=last_y0)end_line=last_y2;
//				else end_line=last_y0;
//				break;
//			}
//		}
//		if(end_line==0)
//		{
//			if(last_y2>=last_y0)end_line=last_y2;
//			else end_line=last_y0;
//		}
//	}
//	if(left_end_line==255)left_end_line=0;
//	if(right_end_line==255)right_end_line=0;
//	for(i=left_end_line;i<=end_line;i++)
//	{
//		Loc[0][i]=-LIM;
//	}
//	for(i=right_end_line;i<=end_line;i++)
//	{
//		Loc[2][i]=LIM;
//	}
//	//================================================================================================================================//
//	//特征量计算
//	//================================================================================================================================//
//	//近行曲率求解       
//	for(i=3;i<40;i++)
//	{
//		if(Loc[0][i]!=-LIM && Loc[0][i-3]!=-LIM)
//		{
//			//左线曲率
//			if(Loc[0][i]==Loc[0][i-3]) str_L1++;          
//			else if(Loc[0][i]<Loc[0][i-3])LL1++;
//			else LR1++;
//		}
//		if(Loc[2][i]!=LIM && Loc[2][i-3]!=LIM)
//		{
//			//右线曲率
//			if(Loc[2][i]==Loc[2][i-3]) str_R1++;          
//			else if(Loc[2][i]>Loc[2][i-3])RR1++;
//			else RL1++;
//		}   
//	}
//	//远行曲率求解       
//	for(i=40;i<end_line;i++)
//	{
//		if(Loc[0][i]!=-LIM && Loc[0][i-3]!=-LIM)
//		{
//			//左线曲率
//			if(Loc[0][i]==Loc[0][i-3]) str_L2++;          
//			else if(Loc[0][i]<Loc[0][i-3])LL2++;
//			else LR2++;
//		}
//		if(Loc[2][i]!=LIM && Loc[2][i-3]!=LIM)
//		{
//			//右线曲率
//			if(Loc[2][i]==Loc[2][i-3]) str_R2++;          
//			else if(Loc[2][i]>Loc[2][i-3])RR2++;
//			else RL2++;
//		}   
//	}
//	//全局斜率曲率求取
//	str_L=str_L1+str_L2;  
//	str_R=str_R1+str_R2;
//	LL=LL1+LL2;
//	LR=LR1+LR2;
//	RR=RR1+RR2;
//	RL=RL1+RL2;
//	//================================================================================================================================//
//	//赛道识别
//	//================================================================================================================================//
//	//左圆环
//	if((RoadType==0 && left_head_line==255  &&   str_R>50) || (RoadType==0 && left_head_line>20  &&   str_R>50 && right_end_line-right_head_line>75))
//	{ 
//		RoadType=3;         
//	}
//	if(RoadType==0 && str_L>40 && str_R>40)
//	{
//		RoadType=4;         
//	}
//	if(RoadType==4)
//	{
//		if(str_L<25 || str_R<25)
//		{
//			RoadType=0;
//			end_line=70;
//		}
//	}
//	
//	//================================================================================================================================//
//	//赛道特别处理
//	//================================================================================================================================//
//	if(RoadType==3)                    
//	{
//		if(circle_stage==0)
//		{
//                        if(str_L1>20)RoadType=0;
//                        if(turn_flag==0 && left_end_line!=0 &&left_head_line!=255)
//			{
//				if(left_end_line-left_head_line>80)turn_flag=3;
//				else if(left_end_line-left_head_line>=50)turn_flag=2;
//				else if(left_end_line-left_head_line<50 && left_end_line-left_head_line>25)turn_flag=1;
//                                else turn_flag=110;  //报警吧
//			}
//			if(LL1>8 )
//			{
//				circle_stage=1;
//			}
//                        
//		}
//		if(circle_stage==1)
//		{
//			if(left_head_line==255 || left_end_line<15)
//			{
//				for(i=0;i<51;i++)
//				{
//					Loc[0][i]=-18-i;
//				}
//				left_end_line=50;
//			}
//			else if(left_end_line<50)
//			{
//				float slope_temp=0;
//				slope_temp=Loc[0][left_end_line-3]-Loc[0][left_end_line-5]+Loc[0][left_end_line-4]-Loc[0][left_end_line-6];
//				for(i=left_end_line;i<=60;i++)
//				{
//					Loc[0][i]=Loc[0][left_end_line-1]+slope_temp*(i-left_end_line+1)/4;
//					if(Loc[0][i]>0)
//					{
//						Loc[0][i]=0;
//					}
//					else if(Loc[0][i]<-65)
//					{
//						Loc[0][i]=-65;
//					}
//				}
//			}
//			
//			if((RL1>25 || (RL1>8 && right_head_line==5))&& str_R<10)circle_stage=2;
//		}
//		else if(circle_stage==2) 
//		{
//			uint8 j,left_flag=0,ir2=60;
//			ir=60;
//			//     for(j=59;j>20;j--)
//			//     {
//			//        if(LMR[2][j]!=80)
//			//        {
//			//          if(LMR[2][j]>LMR[2][j-2] && LMR[2][j-1]>LMR[2][j-3])left_flag=1;
//			//          else if(left_flag==1 && LMR[2][j]<LMR[2][j-2] && LMR[2][j-1]<LMR[2][j-3])
//			//          {
//			//            ir2=j+2;
//			//            break;
//			//          }
//			//        }
//			//     }
//			if(right_end_line<15)circle_stage=3;
//		}
//		else if(circle_stage==3)
//		{
//			search_end_line = 30;
//			if(left_head_line==255)
//			{
//				for(i=0;i<50;i++)
//				{
//					Loc[0][i]=-18-i;
//				}
//				left_end_line=50;
//			}
//			if(str_R>16 || (right_end_line-right_head_line>60 && right_head_line!=255 && right_end_line!=255))
//			{
//				circle_stage=4;
//
//			}
//		}
//                
//		else if(circle_stage==4)
//		{
//                  wait_time++;
//                  if(str_L>20 || wait_time>=40)
//                  {
//                    RoadType=0;
//                    circle_stage=0;
//                    turn_flag=0;
//                  }
//		}
//	}
//	// if(LMR[0][55]!=0 && LMR[0][15]!=0)curve_left=(LMR[0][15]+LMR[0][55])/2-LMR[0][35];
//	// if(LMR[2][55]!=80 && LMR[2][10]!=80)curve_right=(LMR[2][10]+LMR[2][45])/2-LMR[2][21];
//	//  
//	// if(RoadType==0 && left_head_line >40 && (LMR[2][50]==80||/*LMR[2][55]==80||*/LMR[2][45]==80) )  //先写一侧
//	// {
//	//    
//	//    if(you_break>1 && straight_left>38 && count_right<8 && curve_linel_left<3 && SlopeRmin<=-3 && curve_liner_left>9 && curve_liner_right>1 && SlopeLmax<=3)      //RR改为1.原为2 kk
//	//    {
//	//      // RoadType=2;
//	//    }
//	//     
//	// }
//	// if(zuo_break>1 && RoadType==0 && right_head_line >40 && (LMR[0][50]==0||/*LMR[0][55]==0||*/LMR[0][45]==0) )  //先写一侧
//	// {
//	//    
//	//    if(straight_right>38 && count_left<8 && curve_liner_right<3 && SlopeLmax>=3 && curve_linel_right>9 && curve_linel_left>1 && SlopeRmin>=-3)
//	//    {
//	//    //   RoadType=3;
//	//    }
//	//     
//	// }
//	// if(RoadType==0 && straight_left>44 && straight_right>44)
//	// {
//	//    straight_count++;
//	//    if(straight_count>10)RoadType=4;
//	// }
//	// if(RoadType==4 && (straight_left<40 || straight_right<40))
//	// {
//	//    RoadType=0;
//	//    straight_count=0;
//	// }
//	// /*if(RoadType==0 && search_end_line<8 && ((middle_left_q>7 &&  middle_right_q>9)||(middle_left_q>9 &&middle_right_q>7)) && middle_straight_q>205)
//	// {
//	//    RoadType=6;
//	// }*/
//	// 
//	// if(RoadType==1)
//	// {
//	//   if(AllWhileEndLine==0||AllWhileEndLine<20)RoadType=0;
//	//   if(break_line_left!=0 && continue_line_left!=0)
//	//   {
//	//       for(i=continue_line_left-1;(i>continue_line_left-15)&&(i>0);i--) //续线行可能有问题 检测一下 
//	//      {
//	//        /*if((LMR[0][i]!=0)&&(LMR[0][i-1]!=0))
//	//        {
//	//          if(ABS(LMR[0][i]-LMR[0][i-1])<2)
//	//          {
//	//              if(ABS(LMR[0][i-1]-LMR[0][i-2])<2)
//	//            {
//	//              continue_line_left=i;
//	//              break;
//	//            }
//	//          }
//	//        }*/
//	//        if((LMR[0][i]!=0)&&(LMR[0][i-2]!=0))
//	//        {
//	//          if(LMR[0][i-2]-LMR[0][i]<=2 && LMR[0][i-2]-LMR[0][i]>=0)
//	//          {
//	//              if(LMR[0][i-3]-LMR[0][i-1]<=2 && LMR[0][i-3]-LMR[0][i-1]>=0)
//	//            {
//	//              continue_line_left=i;
//	//              break;
//	//            }
//	//          }
//	//        }
//	//      }
//	//      
//	//      for(i=break_line_left;i>=continue_line_left;i--) //开始补线
//	//      { 
//	//        slope=(LMR[0][break_line_left]- LMR[0][continue_line_left])*1.0/(break_line_left-continue_line_left);
//	//        LMR[0][i]= LMR[0][break_line_left]-(int)((break_line_left-i)*slope);
//	//      }
//	//   }
//	//   else           //补充斜入十字的情况
//	//   {
//	//     uint8 il=60;
//	//     if(leftfind==1)
//	//     {
//	//      il=break_point_find(LMR[0]);
//	//      if(il!=60)
//	//      {
//	//        xierushizi=1;
//	//        fix_line(LMR[0],il+2);
//	//        if(search_end_line<30)search_end_line=30;
//	//      }
//	//     }
//	//         
//	//   }
//	//   if(break_line_right!=0&&continue_line_right!=0)
//	//   {
//	//       for(i=continue_line_right;(i>continue_line_right-15)&&(i>0);i--) //续线行可能有问题 检测一下 
//	//      {
//	//         if((LMR[2][i]!=0)&&(LMR[2][i-2]!=0))
//	//        {
//	//          if(LMR[2][i]-LMR[2][i-2]<=2 && LMR[2][i]-LMR[2][i-2]>=0)
//	//          {
//	//              if(LMR[2][i-1]-LMR[2][i-3]<=2 && LMR[2][i-1]-LMR[2][i-3]>=0)
//	//            {
//	//              continue_line_right=i;
//	//              break;
//	//            }
//	//          }
//	//        }
//	//      }
//	//         for(i=break_line_right;i>=continue_line_right;i--) //开始补线
//	//      { 
//	//        slope=(LMR[2][break_line_right]- LMR[2][continue_line_right])*1.0/(break_line_right-continue_line_right);
//	//        LMR[2][i]= LMR[2][break_line_right]-(int)((break_line_right-i)*slope);
//	//      }
//	//      
//	//   }
//	//   else           //补充斜入十字的情况
//	//   {
//	//     xierushizi=1;
//	//     uint8 ir=60;
//	//     if(rightfind==1)
//	//     {
//	//      ir=break_point_find(LMR[2]);
//	//      if(ir!=60)
//	//      {
//	//        fix_line(LMR[2],ir+2);
//	//        if(search_end_line<30)search_end_line=30;
//	//      }
//	//     }
//	//     
//	//   }
//	// }
//	// else if(RoadType==2)                           //右侧圆环
//	// {
//	//   if(circle_stage==0 && (count_right>16||ABS(curve_left)>4))RoadType=0;
//	//   if(circle_stage==0)
//	//   {
//	//     if(white_right>28 && white_right<47 && right_head_line>55 )circle_stage=1;
//	//   }
//	//   
//	//   if(circle_stage==1)
//	//   {
//	//    uint8 slope=0;  
//	//    uint8 start_point;
//	//    uint8 find_point=0;
//	//    turn_flag=2;
//	//    //get_edge_left(3,79);
//	//    /*for(i=4;i<35;i++)
//	//    {
//	//      uint8 white_count=0;
//	//      //get_edge_left(i,79);
//	//      if(LMR[0][i]>10&&LMR[0][i]<79)
//	//      {
//	//        if(LMR[0][i-1]-LMR[0][i]>15)
//	//        {
//	//          break;
//	//          find_point=1;
//	//        }
//	//      }
//	//      else
//	//      {
//	//        white_count++;
//	//      }
//	//      if(i==25&&white_count>18)
//	//        break;
//	//    }
//	//    
//	//    if(find_point==1)
//	//    { 
//	//      turn_point=i-2;
//	//    }
//	//*/
//	//      /*for(i=4;i<25;i++)
//	//      {
//	//        //if(LMR[2][i+5]>70  && absint(LMR[2][i],LMR[2][i-1])<4 && LMR[2][i]<65)
//	//        if((LMR[2][i+2]>70||LMR[2][i+1]>70) && LMR[2][i]<65)
//	//        {
//	//          turn_point=i;
//	//          find_point=1;
//	//          break;
//	//        }
//	//        if((LMR[2][i+2]>70||LMR[2][i+1]>70) && absint(LMR[0][i],LMR[0][i-1])<4 && LMR[0][i]>30)
//	//        {
//	//          turn_point=i;
//	//          find_point=1;
//	//          break;
//	//        }
//	//      }*/
//	//
//	//    /*if(find_point==1 && turn_point>9)
//	//    {
//	//      slope=LMR[2][turn_point]*5/(59-turn_point);
//	//      for(i=59;i>=turn_point;i--)
//	//      {
//	//        LMR[0][i]=slope*(59-i)/5;
//	//      }
//	//      /*for(;i>0;i--)
//	//      {
//	//        j=edgposition[i];
//	//        while(img_edg[j]!=255)
//	//        {
//	//          if(img_edg[j]<LMR[0][i+1]+8 && img_edg[j]>LMR[0][i+1]-2)
//	//          {
//	//            LMR[0][i]=img_edg[j];
//	//            break;
//	//          }
//	//          j++;
//	//        }
//	//      }
//	//    }*/
//	//    if(white_right<52 && white_right>20)
//	//    {
//	//       for(i=59;i>white_right;i--)
//	//       {
//	//          LMR[0][i]=LMR[2][i]-i;
//	//       }
//	//       search_end_line=35;
//	//       for(;i>25;i--)
//	//       {
//	//          LMR[0][i]=LMR[0][i+1]+3;
//	//          if(LMR[0][i]>75)
//	//          {
//	//            LMR[0][i]=75;
//	//          }
//	//          
//	//       }
//	//    }
//	//    else
//	//    {
//	//        LMR[0][59]=20;
//	//        for(i=58;i>20;i--)
//	//        {
//	//          LMR[0][i]=LMR[0][i+1]+(60-i)/10+1;
//	//          if(LMR[0][i]>70)
//	//          {
//	//            break;
//	//          }
//	//        }
//	//    }
//	//    
//	//    if(curve_linel_right>20 && count_right>20 && SlopeLmax>4)circle_stage=2;
//	//  }
//	//   
//	//   if(circle_stage==2) 
//	//   {
//	//     uint8 j,right_flag=0,il2=60;
//	//     il=60;
//	//     for(j=59;j>17;j--)
//	//     {
//	//        if(LMR[0][j]!=0)
//	//        {
//	//          if(LMR[0][j]<LMR[0][j-2] && LMR[0][j-1]<LMR[0][j-3] )right_flag=1;
//	//          else if(right_flag==1 &&( (LMR[0][j]>LMR[0][j-2] && LMR[0][j-2]>LMR[0][j-4])||(LMR[0][j]>LMR[0][j-2]+7)))
//	//          {
//	//            il2=j+2;
//	//            break;
//	//          }
//	//        }
//	//     }
//	//     
//	//    if(il2>23 && il2<40 && LMR[0][il2]<65 && curve_linel_left>3)circle_stage=3;
//	//    else
//	//    {
//	//      il=break_point_find(LMR[0]);
//	//      if(il>20 && il<40 && LMR[0][il]<65 && curve_linel_left>3)circle_stage=3;
//	//    }
//	//      /*il=break_point_find(LMR[0]);
//	//      if(il>25 && il<40 && LMR[0][il]<65 && curve_linel_left>3)circle_stage=3;*/
//	//    
//	//   }
//	//   if(circle_stage==3)
//	//   {
//	//     uint8 flag=0;
//	//     turn_flag=2;
//	//     il=60;
//	//     il=break_point_find(LMR[0]);
//	//     search_end_line = 30;
//	//     for(i=59;i>0;i--)
//	//     {
//	//       if(LMR[0][i]!=0 && LMR[0][i]<LMR[0][i-2])
//	//       {
//	//         flag=1;
//	//         LMR[0][i]=LMR[0][i]-(i-left_head_line)/2;
//	//       }
//	//       else if(flag==1 && LMR[0][i-1]>LMR[0][i-3])
//	//       {
//	//        break;
//	//       }
//	//     }
//	//     if(i+2<52 && i!=0)
//	//     {
//	//       for(i=i+2;i>0;i--)
//	//       {
//	//        LMR[0][i]=LMR[0][i+1]+(60-i)/10+1;
//	//        if(LMR[0][i]>65)
//	//        {
//	//          if(i>search_end_line)search_end_line = i;
//	//          break;
//	//          
//	//        }
//	//       }  
//	//     }
//	//     else
//	//     {
//	//        LMR[0][59]=15;
//	//        for(i=58;i>20;i--)
//	//        {
//	//          LMR[0][i]=LMR[0][i+1]+(60-i)/10+1;
//	//          if(LMR[0][i]>65)
//	//          {
//	//            if(i>search_end_line)search_end_line = i;
//	//            break;
//	//           
//	//          }
//	//        }
//	//     
//	//     }
//	//     uint8 j,right_flag=0,il2=0;
//	//     for(j=59;j>16;j--)
//	//     {
//	//        if(LMR[0][j]!=0 && LMR[0][j-1]!=0 && LMR[0][j-2]!=0)
//	//        {
//	//          if(LMR[0][j]<LMR[0][j-2])right_flag=1;
//	//          else if(right_flag==1 && LMR[0][j]>LMR[0][j-2])
//	//          {
//	//            il2=j+2;
//	//            break;
//	//          }
//	//        }
//	//     }
//	//     if(il2<15 && ( (AllWhileStartLine==0 || AllWhileStartLine>=40) &&  curve_linel_right>35 && SlopeLmax<=4 && straight_right>9) || straight_left>28||(white_right<57 && white_right>25 && straight_left>27))
//	//     {
//	//       RoadType=0;
//	//       circle_stage=0;
//	//     }
//	//   }
//	// }
//	// else if(RoadType==3)                    //左圆环
//	// {
//	//   if(circle_stage==0 && count_left>16)RoadType=0;
//	//   if(circle_stage==0  && ABS(curve_right)>4)RoadType=0;
//	//   if(circle_stage==0)
//	//   {
//	//     if(white_left>28 && white_left<47 && left_head_line>55)circle_stage=1;
//	//   }
//	//   
//	//   if(circle_stage==1)
//	//   {
//	//    uint8 slope=0;  
//	//    uint8 start_point;
//	//    uint8 find_point=0;
//	//    turn_flag=1;
//	//    
//	//    if(white_left<52 && white_left>20)
//	//    {
//	//       for(i=59;i>white_left;i--)
//	//       {
//	//          LMR[2][i]=LMR[0][i]+i;
//	//       }
//	//       search_end_line=35;
//	//       for(;i>25;i--)
//	//       {
//	//          LMR[2][i]=LMR[2][i+1]-3;
//	//          if(LMR[2][i]<5)
//	//          {
//	//            LMR[2][i]=5;
//	//          }
//	//          
//	//       }
//	//    }
//	//    else
//	//    {
//	//        LMR[2][59]=60;
//	//        for(i=58;i>20;i--)
//	//        {
//	//          LMR[2][i]=LMR[2][i+1]-(60-i)/10-1;
//	//          if(LMR[2][i]<10)
//	//          {
//	//            break;
//	//          }
//	//        }
//	//    }
//	//    
//	//    if(curve_liner_left>20 && count_left>20 && SlopeRmin<-4 )circle_stage=2;
//	//  }
//	//   
//	//   else if(circle_stage==2) 
//	//   {
//	//     uint8 j,left_flag=0,ir2=60;
//	//     ir=60;
//	//     for(j=59;j>20;j--)
//	//     {
//	//        if(LMR[2][j]!=80)
//	//        {
//	//          if(LMR[2][j]>LMR[2][j-2] && LMR[2][j-1]>LMR[2][j-3])left_flag=1;
//	//          else if(left_flag==1 && LMR[2][j]<LMR[2][j-2] && LMR[2][j-1]<LMR[2][j-3])
//	//          {
//	//            ir2=j+2;
//	//            break;
//	//          }
//	//        }
//	//     }
//	//     if(ir2>23 && ir2<40 && LMR[2][ir2]>15 && curve_liner_right>1)circle_stage=3;
//	//     else
//	//     {         
//	//        ir=break_point_find(LMR[2]);
//	//        if(ir>20 && ir<40 && LMR[2][ir]>15 && curve_liner_right>1)circle_stage=3;   
//	//     }
//	//       
//	//      
//	//   }
//	//   else if(circle_stage==3)
//	//   {
//	//     uint8 flag=0;
//	//     turn_flag=1;
//	//     ir=60;
//	//     ir=break_point_find(LMR[2]);
//	//     search_end_line = 30;
//	//     for(i=59;i>0;i--)
//	//     {
//	//       if(LMR[2][i]!=80 && LMR[2][i]>LMR[2][i-2])
//	//       {
//	//         flag=1;
//	//         LMR[2][i]=LMR[2][i]+(i-right_head_line)/2;
//	//       }
//	//       else if(flag==1 && LMR[2][i-1]<LMR[2][i-3])
//	//       {
//	//        break;
//	//       }
//	//     }
//	//     if(i+2<52 && i!=0)
//	//     {
//	//       for(i=i+2;i>0;i--)
//	//       {
//	//        LMR[2][i]=LMR[2][i+1]-(60-i)/10-1;
//	//        if(LMR[2][i]<15)
//	//        {
//	//          if(i>search_end_line)search_end_line = i;
//	//          break;
//	//          
//	//        }
//	//       }  
//	//     }
//	//     else
//	//     {
//	//        LMR[2][59]=65;
//	//        for(i=58;i>20;i--)
//	//        {
//	//          LMR[2][i]=LMR[2][i+1]-(60-i)/10-1;
//	//          if(LMR[2][i]<15)
//	//          {
//	//            if(i>search_end_line)search_end_line = i;
//	//            break;
//	//           
//	//          }
//	//        }
//	//     
//	//     }
//	//     uint8 j,left_flag=0,ir2=0;
//	//     for(j=59;j>16;j--)
//	//     {
//	//        if(LMR[2][j]!=80 )
//	//        {
//	//          if(LMR[2][j]>LMR[2][j-2])left_flag=1;
//	//          else if(left_flag==1 && LMR[2][j]<LMR[2][j-2])
//	//          {
//	//            ir2=j+2;
//	//            break;
//	//          }
//	//        }
//	//     }
//	//     if(ir2<15 && ( (AllWhileStartLine==0 || AllWhileStartLine>=40) &&  curve_liner_left>35 && SlopeRmin>=-4 && straight_left>9) || straight_right>28||(white_left<57 && white_left>25 && straight_right>27))
//	//     {
//	//       RoadType=0;
//	//       circle_stage=0;
//	//     }
//	//   }
//	// }
//	// else           //补充斜入十字的情况
//	// {
//	//   uint8 il=60,ir=60;
//	//   if(leftfind==1)
//	//   {
//	//    il=break_point_find(LMR[0]);
//	//    if(il!=60 && LMR[2][50]>65 && curve_liner_left<10)
//	//    {
//	//      fix_line(LMR[0],il+2);
//	//      if(search_end_line<25)search_end_line=25;
//	//    }
//	//   }
//	//   if(rightfind==1)
//	//   {
//	//    ir=break_point_find(LMR[2]);
//	//    if(ir!=60 && LMR[0][50]<15 && curve_linel_right<10)
//	//    {
//	//      fix_line(LMR[2],ir+2);
//	//      if(search_end_line<25)search_end_line=25;
//	//    }
//	//   }
//	//   
//	// }
//	
//	
//	//================================================================================================================================//
//	//中线提取
//	//================================================================================================================================//
//	uint8 line1;
//	uint8 con1=0,con2=0;
//	
//	if( RoadType==3 && circle_stage==1 )
//	{
//		
//		for(i=0; i<left_end_line;i++)
//		{
//                  if(turn_flag==1)Loc[1][i]=Loc[0][i]+16;
//                  else if(turn_flag==3)Loc[1][i]=Loc[0][i]+22;
//                  else Loc[1][i]=Loc[0][i]+19;
//                  
//		}
//		end_line=left_end_line-1;
//	}
//        else if( RoadType==3 &&  circle_stage==3)
//	{
//		
//		for(i=0; i<left_end_line;i++)
//		{
//			Loc[1][i]=Loc[0][i]+26;
//		}
//		end_line=left_end_line-1;
//	}
//	else if( RoadType==3 && circle_stage==0 )
//	{
//		for(i=0; i<right_end_line;i++)
//		{
//			Loc[1][i]=Loc[2][i]-17;
//		}
//		end_line=right_end_line-1;
//	}
//        else if( RoadType==3 && circle_stage==4 )
//	{
//		for(i=0; i<right_end_line;i++)
//		{
//			Loc[1][i]=Loc[2][i]-17;
//		}
//		end_line=right_end_line-1;
//	}
//	else if(RoadType==5)
//	{
//		if(brick_dir==0)
//		{
//			for(i=0;i<left_end_line;i++)
//			{
//				Loc[1][i]=Loc[0][i]+9;
//			}   
//			end_line=left_end_line;
//		}
//		else if(brick_dir==1)
//		{
//			for(i=0;i<right_end_line;i++)
//			{
//				Loc[1][i]=Loc[2][i]-9;
//			}   
//			end_line=right_end_line;
//		}
//		else
//		{
//			for(i=0;i<=60;i++)
//			{
//				Loc[1][i]=0;
//			}
//			end_line=60;
//		}
//	}
//	else if(RoadType==1)
//	{
//		
//		for(i=0;i<end_line;i++)
//		{ 
//			//左右线
//			if(Loc[0][i]!=-255 && Loc[2][i]!=255)
//			{
//				Loc[1][i]=(Loc[0][i]+Loc[2][i])/2;
//			}
//			else if(Loc[0][i]!=-255)
//			{
//				Loc[1][i]=Loc[0][i]+half;
//			}
//			else if(Loc[2][i]!=255)
//			{
//				Loc[1][i]=Loc[2][i]-half;
//			}
//			else
//			{
//				Loc[1][i]=0;
//			}
//			if(Loc[1][i]>LIM)
//			{
//				Loc[1][i]=40;
//				end_line=i-1;
//				break;
//			}
//			if(Loc[1][i]<-LIM)
//			{
//				Loc[1][i]=-LIM;
//				end_line=i-1;
//				break;
//			}
//			if(i>5)
//			{
//				if(ABS(Loc[1][i]-Loc[1][i-1])>7 && left_end_line>i && right_end_line>i)
//				{
//					end_line=i-2;
//				}
//				else if(ABS(Loc[1][i]-Loc[1][i-2]-Loc[1][i-2]+Loc[1][i-4])>8)
//				{
//					end_line=i-4;
//				}
//			}
//		}
//		if(end_line<45)
//		{
//			if(end_line>10)
//			{
//				flope_temp=Slope_Calculate_Uint8(end_line-11,end_line-1,Loc[1]);
//				for(i=end_line;i<=60;i++)
//				{
//					Loc[1][i]=Loc[1][end_line-1]+flope_temp*(i-end_line+1);
//					if(Loc[1][i]>60)
//					{
//						Loc[1][i]=60;
//						break;
//					}
//					else if(Loc[1][i]<-60)
//					{
//						Loc[1][i]=-60;
//						break;
//					}
//				}
//				if(i<60)end_line=i;
//		        else end_line=60;
//			}
//			else
//			{
//				for(i=end_line;i<=40;i++)
//				{
//					Loc[1][i]=0;
//				}
//				if(i<40)end_line=i;
//		        else end_line=40;
//			}
//		}
//	}
//	else
//	{
//		//   if(left_end_line>50)
//		//   {
//		//    if(left_end_line>70)line1=70;
//		//    else line1=left_end_line;
//		//    for(i=line1;i>line1-10;i--)
//		//    {  
//		//        if(slope_q[0][i]>=500)
//		//        {
//		//          con2++;   
//		//        }
//		//    }
//		//    for(i=4;i<40;i++)
//		//    {
//		//     if(ABS(slope_q[0][i])<300 &&slope_q[0][i]!=255 )con1++;
//		//    }
//		//    if(con1>10 && con2>3 && RoadType==0)ruwan_flag=1;
//		//    if(ruwan_flag==1 &&( con1<3 || con2<2 || RoadType!=0))ruwan_flag=0;
//		//   }
//		
//		if(ruwan_flag==1)
//		{
//			for(i=0;i<left_end_line;i++) 
//				Loc[1][i]=Loc[0][i]+10;
//		}
//		else 
//		{
//			for(i=0;i<end_line;i++)
//			{ 
//				//左右线
//				if(Loc[0][i]!=-255 && Loc[2][i]!=255)
//				{
//					Loc[1][i]=(Loc[0][i]+Loc[2][i])/2;
//				}
//				else if(Loc[0][i]!=-255)
//				{
//					Loc[1][i]=Loc[0][i]+half;
//				}
//				else if(Loc[2][i]!=255)
//				{
//					Loc[1][i]=Loc[2][i]-half;
//				}
//				if(Loc[1][i]>LIM)
//				{
//					Loc[1][i]=LIM;
//					end_line=i;
//					break;
//				}
//				if(Loc[1][i]<-LIM)
//				{
//					Loc[1][i]=-LIM;
//					end_line=i;
//					break;
//				}
//				if(i>5)
//				{
//					if(ABS(Loc[1][i]-Loc[1][i-1])>7 && left_end_line>i && right_end_line>i)
//					{
//						end_line=i-2;
//					}
//					else if(ABS(Loc[1][i]-Loc[1][i-2]-Loc[1][i-2]+Loc[1][i-4])>8)
//					{
//						end_line=i-4;
//					}
//				}
//			}
//		}
//	}
//        flope_temp=0;
//	uint8 con=0;
//	for(i=59;i>50;i--)
//	{
//		Black_record[i-50]=(LMR[0][i]+LMR[2][i])/2;
//	}
//	if(end_line<45 && end_line>10 && RoadType!=1)
//	{
//                fix_flag=1;
//		flope_temp=Slope_Calculate_Uint8(end_line-11,end_line-1,Loc[1]);
//		for(i=end_line;i<=70;i++)
//		{
//			Loc[1][i]=Loc[1][end_line-1]+flope_temp*(i-end_line+1);
//			if(Loc[1][i]>60)
//			{
//				Loc[1][i]=60;
//				break;
//			}
//			else if(Loc[1][i]<-60)
//			{
//				Loc[1][i]=-60;
//				break;
//			}
//		}
//		if(i<70)end_line=i;
//		else end_line=70;
//	}
//        for(i=4;i<end_line;i++)
//        {
//          slope_q[1][i]=(Loc[1][i]-Loc[1][i-2]+Loc[1][i-1]-Loc[1][i-3])*100;
//        }
//
//	//================================================================================================================================//
//	//控制行
//	//================================================================================================================================//
//	uint8 temp2=0;
//	// uint8 s_grade=0;
//	// if(CarSpeed<2)s_grade=0;
//	// else if(CarSpeed<2.0)s_grade=1;
//	// else if(CarSpeed<2.2)s_grade=2;
//	// else if(CarSpeed<2.4)s_grade=3;
//	// else if(CarSpeed<2.6)s_grade=4;
//	// else if(CarSpeed<2.7)s_grade=6;
//	// else if(CarSpeed<2.8)s_grade=7;
//	// else s_grade=8;
//	// line=fuzzy_line[s_grade];
//	if(CarSpeed < 1.8)
//	{
//		line = bais;
//	}
//	else if(CarSpeed < 2.5)
//	{
//		line = bais + (uint8)((CarSpeed - 1.8) * 18);
//	}
//	else if(CarSpeed < 3.3)
//	{
//		line = bais + 13 + (uint8)(CarSpeed - 2.5) * 20;
//	}
//	else
//	{
//		line = bais + 29 + (uint8)(CarSpeed - 3.3) * 15;
//	}
//	
//	line_c = line + 30;
//	
//	if(line>=end_line-3)line=end_line-3;
//	if(RoadType==1)
//	{
//		if(line<continue_line_left)line=continue_line_left;
//		if(line<continue_line_right)line=continue_line_right;
//	}
//	
//	if(line_c>=end_line-3)line_c=end_line-3;
//	if(RoadType==1)
//	{
//		if(line_c<continue_line_left)line_c=continue_line_left;
//		if(line_c<continue_line_right)line_c=continue_line_right;
//	}
//	
////	control_line=line;
//	control_line_far = line;
//	control_line_near = 15 + (int)(CarSpeed * 2);
//	//================================================================================================================================//
//	//偏差值计算
//	//================================================================================================================================//
//	temp2 = 0;
//	int DeviFar;
//	//速度偏差
//	//FAR分量
//	for(i = line_c - 8; i < line_c; i++)
//	{
//		if(Loc[1][i] != LIM)
//		{
//			DeviFar += Loc[1][i];
//			temp2++;
//		}
//	}
//	if(temp2 != 0)
//		DeviFar /= temp2;
//	
//	DeviFar = (DeviFar) * 50 / (line_c - 30);
//	DeviFar = LIMIT(DeviFar,79,-79);
//	
//	if(DeviFar >= 0)
//	{
//          SpeedDevi = ARCTANG[DeviFar];
//	}
//	else
//	{
//          SpeedDevi = - ARCTANG[-DeviFar];
//	}
//
//	temp2 = 0;
//	//舵机偏差
//	//FAR分量
//	int Err_temp;
//	for(i = control_line_far - 8; i < control_line_far; i++)
//	{
//		if(Loc[1][i] != LIM)
//		{
//			Middle_Err_Sum_Far += Loc[1][i];
//			temp2++;
//		}
//	}
//	if(temp2 != 0)
//		Middle_Err_Sum_Far /= temp2;
//	//NEAR分量
//	for(i = control_line_near - 8; i < control_line_near; i++)
//	{
//		if(Loc[1][i] != LIM)
//		{
//			Middle_Err_Sum_Near += Loc[1][i];
//			temp2++;
//		}
//	}
//	if(temp2 != 0)
//		Middle_Err_Sum_Near /= temp2;
//	Err_temp = (Middle_Err_Sum_Far) * 50 / (control_line_far-4);
//	Err_temp = LIMIT(Err_temp,79,-79);
//
//	if(Err_temp >= 0)
//	{
//          Middle_Err_Sum_Far = ARCTANG[Err_temp];
//	}
//	else
//	{
//          Middle_Err_Sum_Far = - ARCTANG[-Err_temp];
//	}
//        Err_temp = (int)((Middle_Err_Sum_Near) * 50 / (control_line_near-4));
//	Err_temp = LIMIT(Err_temp,79,-79);
//    if(Err_temp >= 0)
//	{
//		Middle_Err_Sum_Near = ARCTANG[Err_temp];
//	}
//	else
//	{
//		Middle_Err_Sum_Near = - ARCTANG[-Err_temp];
//	}
//	Middle_Err=(9*Middle_Err_Sum_Far+1*Middle_Err_Sum_Near)/10;
//	/******************************************************************/
//																	/**/
////	temp2 = 0;
////	for(i=control_line-1;i>=control_line-7;i=i-2)
////	{
////		if(Loc[1][i] != LIM)
////		{
////			Middle_Err_Sum_Far=Middle_Err_Sum_Far+ Loc[1][i];
////			temp2++;
////		}
////	}
////	if(temp2 != 0)
////		Middle_Err_Sum_Far=Middle_Err_Sum_Far/temp2;
////	else
////	{
////		for(; i>10; i--)
////		{
////			if(Loc[1][i] != LIM)
////			{
////				Middle_Err_Sum_Far=Loc[1][i];
////				break;
////			}
////		}
////	}
////	
////	temp2=0;
////	for(i=15;i>=9;i=i-2)
////	{
////		if(Loc[1][i] != LIM)
////		{
////			Middle_Err_Sum_Near=Middle_Err_Sum_Near + Loc[1][i];
////			temp2++;
////		}
////	}
////	if(temp2 != 0)
////		Middle_Err_Sum_Near=Middle_Err_Sum_Near/temp2;
//	
////	slope_qj=0;
////	Middle_Err_Sum=(Middle_Err_Sum_Near*2+Middle_Err_Sum_Far*8)/10;
////	if(control_line>25 && Loc[1][control_line-5]!=LIM && Loc[1][10]!=LIM)
////		slope_qj =  (Loc[1][control_line-5]-Loc[1][10])*10.0/(control_line-10);
////	Middle_Err=(slope_qj*4 + Middle_Err_Sum*6)/10;
//																					/**/
//	/*********************************************************************************/
////        if(end_line>40)
////        {
////          slope_speed==Slope_Calculate_Uint8(end_line-20,end_line-1,Loc[1]);
////        }
////        GO=255;
////        NO=255;
////        if(left_end_line+right_end_line>117 && end_line>65)
////        {
////          for(i=10;i<end_line;i++)
////          {
////            if(ABS(slope_q[1][i])<=300 &&slope_q[1][i]!=255 )GO++;
////            else if(ABS(slope_q[1][i])>=500)NO++;
////          }
////        } 
//        N0=0;
//        N1=0;
//        N2=0;
//        Np=0;
//        GO=0;
//        if(end_line>55 && fix_flag==0)
//        {
//          float slope_fit;
//          float fit_x;
//          slope_fit=Slope_Calculate_Uint8(5,end_line-1,Loc[1]);
//          for(i=5;i<=55;i++)
//          {
//            fit_x=Loc[1][5]+slope_fit*(i-5);
//            GO+=Loc[1][i]-fit_x;
//            if(ABS(Loc[1][i]-fit_x)==0)N0++;
//            else if(ABS(Loc[1][i]-fit_x)<1)N1++;
//            else if(ABS(Loc[1][i]-fit_x)<2)N2++;
//            else Np++;
//          }
//        }
//	// if(straight_left+straight_right>=70&&RoadType!=4)
//	//   Middle_Err=(Middle_Err_Sum_Near*4+Middle_Err_Sum*3+Middle_Err_Sum_Middle*3)/10;
//	// if((curve_liner_left>7  && curve_liner_right>7  && curve_linel_left>2 && curve_linel_right>2 ) || (curve_liner_left>2  && curve_liner_right>2  &&curve_linel_left>7 && curve_linel_right>7 ))
//	//   Middle_Err=(Middle_Err_Sum_Near*2+Middle_Err_Sum*5+Middle_Err_Sum_Middle*3)/10;
//	// else if((curve_liner_left>2  && curve_liner_right>2) || (curve_linel_left>2 && curve_linel_right>2 ))Middle_Err=(Middle_Err_Sum_Near*2+Middle_Err_Sum*6+Middle_Err_Sum_Middle*2)/10;
//	//  /*if((Middle_Err_Sum_Near<0 && Middle_Err_Sum>0)||(Middle_Err_Sum_Near>0 && Middle_Err_Sum<0))Middle_Err=(Middle_Err_Sum_Near*3+Middle_Err_Sum*7)/10;
//	//  else if(Middle_Err_Sum_Near>5||Middle_Err_Sum_Near<-5)Middle_Err=(Middle_Err_Sum_Near*2+Middle_Err_Sum*8)/10;
//	//  else if(Middle_Err_Sum_Near>2||Middle_Err_Sum_Near<-2)Middle_Err=(Middle_Err_Sum_Near*1+Middle_Err_Sum*9)/10;*/
//	//  else Middle_Err=(Middle_Err_Sum_Near*1+Middle_Err_Sum*7+Middle_Err_Sum_Middle*2)/10;
//	//  
//	//  if(left_head_line+right_head_line>103 && left_continue+right_continue<20 )
//	//  {
//	//    if(RoadType==0 && middle_continue<7  && search_end_line<6 && ((middle_left_q>7 &&  middle_right_q>9)||(middle_left_q>9 &&middle_right_q>7)) && middle_straight_q>20){
//	//      Middle_Err=Middle_Err*0.65;    //zaixiaodian kk
//	//      //Middle_Err=(Middle_Err*5+(middle_right_q-middle_left_q)*0.5*5)/10.0;
//	//      S_flag=1;
//	//    }
//	//  }
//	//  else
////	    Middle_Err=(Middle_Err*8+(middle_right-middle_left)*0.5*2)/10.0;
////	if(ABS(Middle_Err-Previous_Error[0])>30)
////		Middle_Err=Previous_Error[0];  //防止中心线跳变wk
//        if(circle_stage==1||circle_stage==3)
//        {
//          if(turn_flag==3)
//          {
//            if(RoadType==3 && Middle_Err>-2)Middle_Err=-2;
//          }
//          else if(turn_flag==2)
//          {
//            if(RoadType==3 && Middle_Err>-3)Middle_Err=-3;
//          }
//           else if(turn_flag==1)
//          {
//            if(RoadType==3 && Middle_Err>-5)Middle_Err=-5;
//          }
//        }
//        if(circle_stage==2)
//        {
//          if(turn_flag==1)
//          {
//            if(RoadType==3 && Middle_Err>-30)Middle_Err=-30;
//          }
//        }
//	if(stop_line==1)
//	{
//		if(Middle_Err>1)Middle_Err=1;
//		else if(Middle_Err<-1)Middle_Err=-1;
//	}
//	/////////////////////////////////////////////////////////////////////////
//	if(search_time%2==0)
//	{
//          Middle_Err = Middle_Err * 0.8 + Previous_Error[0] * 0.2;
//          Push_And_Pull(Previous_Error,20,Middle_Err);
//          Delt_error=-10*Slope_Calculate(0,10,Previous_Error);
//		  
//		  SpeedDevi = SpeedDevi * 0.8 + SpeedDevi_His[0] * 0.2;
//		  Push_And_Pull(SpeedDevi_His,ARR_SIZE(SpeedDevi_His),SpeedDevi);
//		  SpeedDeviD = Slope_Calculate(0,10,SpeedDevi_His);
//		  
//	}
//	//////////////////////////////////////////////////////////////////////////
//	//错误判断
//	if(times_count<30)
//	{
//		times_count++;
//		//    if(RoadType==0 && (left_end_line-left_head_line<20 && right_end_line-right_head_line<20 && left_head_line!=255 && right_head_line!=255))failcount++;
//		//    else 
//		if(ABS(slope_qj)>100)failcount++;
//	}
//	else
//	{
//		if(failcount>15)Stop=1;
//		else
//		{
//			failcount=0;
//			times_count=0;
//		}
//	}
//	Err_Fuzzy();
//}