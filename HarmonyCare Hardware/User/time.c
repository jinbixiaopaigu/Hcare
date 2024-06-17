#include "time.h"


void TIMx_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        
          // ����TIMx_CLK,x[6,7],���ڲ�ʱ��CK_INT=72M
    BASIC_TIM_APBxClock_FUN (BASIC_TIM_CLK, ENABLE);
    
          // �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
    TIM_TimeBaseStructure.TIM_Period=1000;

    // �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
      // ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
    
          // ʱ�ӷ�Ƶ���� ��������ʱ��TIM6��TIM7û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
        
          // ����������ģʽ��������ʱ��TIM6��TIM7ֻ�����ϼ�����û�м���ģʽ�����ã����ù�
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
        
          // �ظ���������ֵ��������ʱ��TIM6��TIM7û�У����ù�
      //TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    
      // ��ʼ����ʱ��TIMx, x[6,7]
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
      // ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
          // �����������ж�
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
          // ʹ�ܼ�����
    TIM_Cmd(BASIC_TIM, ENABLE);                                                                        
        // ��ʱ�ر�TIMx,x[6,7]��ʱ�ӣ��ȴ�ʹ��
    BASIC_TIM_APBxClock_FUN (BASIC_TIM_CLK, DISABLE);   
}

 // �ж����ȼ�����
 void BASIC_TIM_NVIC_Config(void)
 {
     NVIC_InitTypeDef NVIC_InitStructure;
     // �����ж���Ϊ0
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
     // �����ж���Դ
     NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;
     // ���������ȼ�Ϊ 0
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     // ������ռ���ȼ�Ϊ3
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
 


