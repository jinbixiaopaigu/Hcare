/*#ifndef _EXIT_H_
#define _EXIT_H_
#include "stm32f10x.h"

///*外部中断EXIT相关宏定义
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

// 定义与外部中断有关的宏
#define   macEXTI_GPIO_CLK     (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     // 开启GPIOA和AFIO的时钟
#define   macEXTI_GPIO_PORT      GPIOA   // 外部中断的GPIO端口
#define   macEXTI_GPIO_PIN       GPIO_Pin_2  // 外部中断的GPIO端口,即PA2
#define   macEXTI_SOURCE_PORT    GPIO_PortSourceGPIOA  // GPIO端口源,用于AFIO映射
#define   macEXTI_SOURCE_PIN     GPIO_PinSource2  // GPIO引脚源,对应于PA2
#define   macEXTI_LINE            EXTI_Line2  // EXTI线路
#define   macEXTI_IRQ             EXTI2_IRQn  // NVIC中断通道
#define   macEXTI_INT_FUNCTION    EXTI2_IRQHandler  // 中断处理函数

void EXTI_Pxy_Config(void);

#endif
