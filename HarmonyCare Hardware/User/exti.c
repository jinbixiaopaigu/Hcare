#include "exti.h"
#include "bsp.h"

/* void EXTI_Pxy_Config(void)    //�ⲿ�жϵĳ�ʼ������
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   //�ں��ն�����
    EXTI_InitTypeDef EXTI_InitStructure;   //�ⲿ�ն�����
  
    /* config the extiline clock and AFIO clock 
    RCC_APB2PeriphClockCmd(macEXTI_GPIO_CLK,ENABLE);
                
/* EXTI line gpio config    
    GPIO_InitStructure.GPIO_Pin = macEXTI_GPIO_PIN;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;     // ��������
    GPIO_Init(macEXTI_GPIO_PORT, &GPIO_InitStructure);
    
    /* config the NVIC 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* �����ж�Դ 
    NVIC_InitStructure.NVIC_IRQChannel = macEXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     //��ʼ������

    /* EXTI line mode config 
    GPIO_EXTILineConfig(macEXTI_SOURCE_PORT, macEXTI_SOURCE_PIN); 
    EXTI_InitStructure.EXTI_Line = macEXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);   //û�е�
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
   if(EXTI_GetITStatus(macEXTI_LINE) != RESET)     //ȷ���Ƿ������EXTILine�ж�
   {
         // LED1 ����    
         LED1_TOGGLE();
         EXTI_ClearITPendingBit(macEXTI_LINE);     //����жϱ�־λ
   }  
}


