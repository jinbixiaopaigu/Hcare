/*#ifndef _EXIT_H_
#define _EXIT_H_
#include "stm32f10x.h"

///*�ⲿ�ж�EXIT��غ궨��
//#define   macEXTI_GPIO_CLK     (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     
//#define   macEXTI_GPIO_PORT      GPIOA   
//#define   macEXTI_GPIO_PIN       GPIO_Pin_0
//#define   macEXTI_SOURCE_PORT    GPIO_PortSourceGPIOA
//#define   macEXTI_SOURCE_PIN     GPIO_PinSource0
//#define   macEXTI_LINE            EXTI_Line0
//#define   macEXTI_IRQ             EXTI0_IRQn
//#define   macEXTI_INT_FUNCTION    EXTI0_IRQHandler

#define   macEXTI_GPIO_CLK     (RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO)     
#define   macEXTI_GPIO_PORT      GPIOC  
#define   macEXTI_GPIO_PIN       GPIO_Pin_13
#define   macEXTI_SOURCE_PORT    GPIO_PortSourceGPIOC
#define   macEXTI_SOURCE_PIN     GPIO_PinSource13
#define   macEXTI_LINE            EXTI_Line13
#define   macEXTI_IRQ             EXTI15_10_IRQn
#define   macEXTI_INT_FUNCTION    EXTI15_10_IRQHandler

void EXTI_Pxy_Config(void);

#endif
*/
#ifndef _EXIT_H_
#define _EXIT_H_
#include "stm32f10x.h"

// �������ⲿ�ж��йصĺ�
#define   macEXTI_GPIO_CLK     (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     // ����GPIOA��AFIO��ʱ��
#define   macEXTI_GPIO_PORT      GPIOA   // �ⲿ�жϵ�GPIO�˿�
#define   macEXTI_GPIO_PIN       GPIO_Pin_2  // �ⲿ�жϵ�GPIO�˿�,��PA2
#define   macEXTI_SOURCE_PORT    GPIO_PortSourceGPIOA  // GPIO�˿�Դ,����AFIOӳ��
#define   macEXTI_SOURCE_PIN     GPIO_PinSource2  // GPIO����Դ,��Ӧ��PA2
#define   macEXTI_LINE            EXTI_Line2  // EXTI��·
#define   macEXTI_IRQ             EXTI2_IRQn  // NVIC�ж�ͨ��
#define   macEXTI_INT_FUNCTION    EXTI2_IRQHandler  // �жϴ�����

void EXTI_Pxy_Config(void);

#endif
