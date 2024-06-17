#include "time.h"


void TIMx_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        
          // 开启TIMx_CLK,x[6,7],即内部时钟CK_INT=72M
    BASIC_TIM_APBxClock_FUN (BASIC_TIM_CLK, ENABLE);
    
          // 自动重装载寄存器周的值(计数值)
    TIM_TimeBaseStructure.TIM_Period=1000;

    // 累计 TIM_Period个频率后产生一个更新或者中断
      // 时钟预分频数为71，则驱动计数器的时钟CK_CNT = CK_INT / (71+1)=1M
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
    
          // 时钟分频因子 ，基本定时器TIM6和TIM7没有，不用管
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
        
          // 计数器计数模式，基本定时器TIM6和TIM7只能向上计数，没有计数模式的设置，不用管
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
        
          // 重复计数器的值，基本定时器TIM6和TIM7没有，不用管
      //TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    
      // 初始化定时器TIMx, x[6,7]
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
      // 清除计数器中断标志位
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
          // 开启计数器中断
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
          // 使能计数器
    TIM_Cmd(BASIC_TIM, ENABLE);                                                                        
        // 暂时关闭TIMx,x[6,7]的时钟，等待使用
    BASIC_TIM_APBxClock_FUN (BASIC_TIM_CLK, DISABLE);   
}

 // 中断优先级配置
 void BASIC_TIM_NVIC_Config(void)
 {
     NVIC_InitTypeDef NVIC_InitStructure;
     // 设置中断组为0
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
     // 设置中断来源
     NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;
     // 设置主优先级为 0
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     // 设置抢占优先级为3
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

extern int time;
void BASIC_TIM_IRQHandler (void)
 {
     if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) {
     time++;
     TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update);
     }
}
 


