#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

/*-------------------------------- 函数声明 -------------------------------*/
void          delay_init          (void);            // 延时初始化
void          delay_us            (u32 nus);         // 微秒延时
void          delay_ms            (u16 nms);         // 毫秒延时


#endif    /*     _DELAY_H_      */
