#include "delay.h"
 
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

/*-------------------- 初始化延迟函数 ------------------------
 * 当使用ucos的时候,此函数会初始化ucos的时钟节拍
 * SYSTICK的时钟固定为HCLK时钟的1/8，HCLK = 72MHz
 * SYSCLK:系统滴答时钟
 * 当SYSCLK为9MHz，系统滴答校准值固定为9000时，产生1ms的时基单元
 * 当SYSCLK为9MHz，系统滴答校准值固定为9时，产生1uss的时基单元
-------------------------------------------------------------*/
void delay_init(void)	 
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟HCLK/8
	fac_us=9;	                        //系统滴答校准值,为系统滴答时钟的1/8000000 即9

	fac_ms=9000;                                //非ucos下,代表每个ms需要的systick时钟数：9000
}								    

/*-------------------- 延时nus函数 ------------------------
 * nus为要延时的us数.	
 * SysTick->CTRL：SysTick控制及状态寄存器
 * SysTick->LOAD：SysTick重装载数值寄存器
 * SysTick->VAL ：SysTick当前数值寄存器
---------------------------------------------------------*/
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;                         // 重装载寄存器LOAD	  		 
	SysTick->VAL=0x00;                                // 清空计数器，
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          // 开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;          //关闭计数器
	SysTick->VAL =0X00;                               //清空计数器	 
}
/*-------------------- 延时nms函数 ------------------------
 * nms为要延时的ms数.	
 * 注意nms的范围
 * SysTick->LOAD为24位寄存器,所以,最大延时为:0xffffff
 * nms<=0xffffff*8*1000/SYSCLK
 * SYSCLK单位为Hz,nms单位为ms
 * 对72M条件下,nms<=1864 
---------------------------------------------------------*/
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;                    //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;                               //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          // 使能：开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;          //关闭计数器
	SysTick->VAL =0X00;                               //清空计数器	  	    
} 

































