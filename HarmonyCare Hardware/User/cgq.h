#include "stm32f10x.h"
#include "stdio.h"
//时间中断变量
int time=0;
         char loading[50];
         static uint32_t load=0;


	 	 

//计步de定义
#define  X_AXLE  0
#define  Y_AXLE  1
#define  Z_AXLE  2
#define  DATA_COMPARE  9000
short    Accel[3];
short    Gyro[3];
char     temp_num[20];
short    Temp;
int      data_temp [100][3];
int      hold_value=0, step_count=0;
int      flag=1;



//max30102d的定义
uint32_t aun_ir_buffer[500]; //IR LED sensor data   红外数据，用于计算血氧
int32_t n_ir_buffer_length=500;    //data length  
uint32_t aun_red_buffer[500];    //Red LED sensor data  红光数据，用于计算心率曲线以及计算心率
int n_sp02; //SPO2 value
int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
int n_heart_rate;   //heart rate value
int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
char heart[6] ={0};
char spo2[6] ={0};
#define MAX_BRIGHTNESS 255
