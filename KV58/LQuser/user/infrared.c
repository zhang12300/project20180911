#include "common.h"
#include "include.h"
#include "infrared.h"
 /*
    函数作用 :红外初始化
 */  

  int inf0_data = 0;
  int inf1_data = 0;
  int inf2_data = 0;
  int inf3_data = 0;
  int inf4_data = 0;
  int inf5_data = 0;
  int inf6_data = 0;
  int inf7_data = 0;
   
void infrared_init()
{
//  gpio_init (inf0, GPI,0);
//  port_init_NoALT (inf0, PULLUP );   
//  gpio_init (inf1, GPI,0);
//  port_init_NoALT (inf1, PULLUP ); 
//  gpio_init (inf2, GPI,0);
//  port_init_NoALT (inf2, PULLUP );
//  gpio_init (inf3, GPI,0);
//  port_init_NoALT (inf3, PULLUP ); 
//  gpio_init (inf4, GPI,0);
//  port_init_NoALT (inf4, PULLUP ); 
//  gpio_init (inf5, GPI,0);
//  port_init_NoALT (inf5, PULLUP ); 
//  gpio_init (inf6, GPI,0);
//  port_init_NoALT (inf6, PULLUP ); 
//  gpio_init (inf7, GPI,0);
//  port_init_NoALT (inf7, PULLUP ); 
  
  
  GPIO_Init(GPIOC,12,GPI,0);
  GPIO_Init(GPIOC,13,GPI,0);
  GPIO_Init(GPIOC,14,GPI,0);
  GPIO_Init(GPIOC,15,GPI,0);
  GPIO_Init(GPIOD,0,GPI,0);
  GPIO_Init(GPIOD,1,GPI,0);
  GPIO_Init(GPIOD,2,GPI,0);
  GPIO_Init(GPIOD,3,GPI,0);
  
//  PORT_PCR_REG(PORTD_BASE_PTR, 0) = 0	 | (0xc0u>> 6);    
//  PORT_PCR_REG(PORTD_BASE_PTR, 1) = 0	 | (0xc0u>> 6);  
//  PORT_PCR_REG(PORTD_BASE_PTR, 2) = 0	 | (0xc0u>> 6);    
//  PORT_PCR_REG(PORTD_BASE_PTR, 3) = 0	 | (0xc0u>> 6); 
//  PORT_PCR_REG(PORTC_BASE_PTR, 12) = 0	 | (0xc0u>> 6);    
//  PORT_PCR_REG(PORTC_BASE_PTR, 13) = 0	 | (0xc0u>> 6); 
//  PORT_PCR_REG(PORTC_BASE_PTR, 14) = 0	 | (0xc0u>> 6);    
//  PORT_PCR_REG(PORTC_BASE_PTR, 15) = 0	 | (0xc0u>> 6); 
  
        
}


int infrared_pro()
{

  inf0_data = gpio_get (inf0);
  inf1_data = gpio_get (inf1);
  inf2_data = gpio_get (inf2);
  inf3_data = gpio_get (inf3);
  inf4_data = gpio_get (inf4);
  inf5_data = gpio_get (inf5);
  inf6_data = gpio_get (inf6);
  inf7_data = gpio_get (inf7);
  
  if(inf0_data == 1 && inf1_data == 1 && inf2_data == 1 && inf3_data == 1 && inf4_data == 1 && inf5_data == 1 && inf6_data == 1 && inf7_data == 1)
    return 0; //全部没信号 返回0
  else 
    return 1;
}