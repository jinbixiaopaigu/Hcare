#ifndef __OTHER_H
#define __OTHER_H
#include "stm32f10x.h"
//#define MAX30102_INT PAin(2)
#define MAX30102_INT PAin(2)


void SendData(void);
void Hardware_Init(void);
static void  MPU6050_DateConver(short *data_src);
static void  Step_temp(void);
static void  Heart_spo2(void);
void int2str(int x,char *Str);
void Delay(__IO uint32_t nCount);
void Show(void);
void Load(void);
void Init_cgq(void);
void Init_Background(void);
void Clean_Background(void);
void GetStep(void);
void GetHeart(void);
void IIC_Init(void);
int gettemp(void);
int getheart(void);
int getstep(void);
int getsp02(void);

#endif

