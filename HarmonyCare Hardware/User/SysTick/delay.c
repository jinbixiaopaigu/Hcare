#include "delay.h"
 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������

/*-------------------- ��ʼ���ӳٺ��� ------------------------
 * ��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
 * SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8��HCLK = 72MHz
 * SYSCLK:ϵͳ�δ�ʱ��
 * ��SYSCLKΪ9MHz��ϵͳ�δ�У׼ֵ�̶�Ϊ9000ʱ������1ms��ʱ����Ԫ
 * ��SYSCLKΪ9MHz��ϵͳ�δ�У׼ֵ�̶�Ϊ9ʱ������1uss��ʱ����Ԫ
-------------------------------------------------------------*/
void delay_init(void)	 
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��HCLK/8
	fac_us=9;	                        //ϵͳ�δ�У׼ֵ,Ϊϵͳ�δ�ʱ�ӵ�1/8000000 ��9

	fac_ms=9000;                                //��ucos��,����ÿ��ms��Ҫ��systickʱ������9000
}								    

/*-------------------- ��ʱnus���� ------------------------
 * nusΪҪ��ʱ��us��.	
 * SysTick->CTRL��SysTick���Ƽ�״̬�Ĵ���
 * SysTick->LOAD��SysTick��װ����ֵ�Ĵ���
 * SysTick->VAL ��SysTick��ǰ��ֵ�Ĵ���
---------------------------------------------------------*/
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;                         // ��װ�ؼĴ���LOAD	  		 
	SysTick->VAL=0x00;                                // ��ռ�������
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          // ��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;          //�رռ�����
	SysTick->VAL =0X00;                               //��ռ�����	 
}
/*-------------------- ��ʱnms���� ------------------------
 * nmsΪҪ��ʱ��ms��.	
 * ע��nms�ķ�Χ
 * SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:0xffffff
 * nms<=0xffffff*8*1000/SYSCLK
 * SYSCLK��λΪHz,nms��λΪms
 * ��72M������,nms<=1864 
---------------------------------------------------------*/
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;                    //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;                               //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          // ʹ�ܣ���ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));                //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;          //�رռ�����
	SysTick->VAL =0X00;                               //��ռ�����	  	    
} 

































