#include "exti.h"
#include "bsp.h"

/* void EXTI_Pxy_Config(void)    //外部中断的初始化函数
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   //内核终端配置
    EXTI_InitTypeDef EXTI_InitStructure;   //外部终端配置
  
    /* config the extiline clock and AFIO clock 
    RCC_APB2PeriphClockCmd(macEXTI_GPIO_CLK,ENABLE);
                
/* EXTI line gpio config    
    GPIO_InitStructure.GPIO_Pin = macEXTI_GPIO_PIN;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;     // 下拉输入
    GPIO_Init(macEXTI_GPIO_PORT, &GPIO_InitStructure);
    
    /* config the NVIC 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* 配置中断源 
    NVIC_InitStructure.NVIC_IRQChannel = macEXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     //初始化函数

    /* EXTI line mode config 
    GPIO_EXTILineConfig(macEXTI_SOURCE_PORT, macEXTI_SOURCE_PIN); 
    EXTI_InitStructure.EXTI_Line = macEXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿中断
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //没有的
}   */

void EXTI_Pxy_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   
    EXTI_InitTypeDef EXTI_InitStructure;  
  
    /* Enable clocks for GPIOA and AFIO */
    RCC_APB2PeriphClockCmd(macEXTI_GPIO_CLK, ENABLE);
                
    /* Configure PA2 pin as input pull-down */
    GPIO_InitStructure.GPIO_Pin = macEXTI_GPIO_PIN;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(macEXTI_GPIO_PORT, &GPIO_InitStructure);
    
    /* Configure NVIC */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = macEXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure EXTI line */
    GPIO_EXTILineConfig(macEXTI_SOURCE_PORT, macEXTI_SOURCE_PIN); 
    EXTI_InitStructure.EXTI_Line = macEXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


void macEXTI_INT_FUNCTION (void)
{
   if(EXTI_GetITStatus(macEXTI_LINE) != RESET)     //确保是否产生了EXTILine中断
   {
         // LED1 点亮    
         LED1_TOGGLE();
         EXTI_ClearITPendingBit(macEXTI_LINE);     //清除中断标志位
   }  
}


