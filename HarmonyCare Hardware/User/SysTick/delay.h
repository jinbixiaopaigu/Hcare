#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

/*-------------------------------- �������� -------------------------------*/
void          delay_init          (void);            // ��ʱ��ʼ��
void          delay_us            (u32 nus);         // ΢����ʱ
void          delay_ms            (u16 nms);         // ������ʱ


#endif    /*     _DELAY_H_      */
