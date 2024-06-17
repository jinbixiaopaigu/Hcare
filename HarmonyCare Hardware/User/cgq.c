#include "stm32f10x.h"
#include "bsp.h"
#include "time.h"
#include "exti.h"
#include "fonts.h"
#include "bsp_ili9341_lcd.h"
#include "stm32f10x_fsmc.h"
#include "bsp_i2c.h"
#include "mpu6050.h"
#include "bsp_usart.h"
#include "delay.h"
#include "algorithm.h"
#include "myiic.h"
#include "delay.h"
#include "max30102.h"
#include "sys.h"
#include "stdio.h"
#include "cgq.h"



//其他函数的一些定义

void  Heart_spo2(void)
{
	        int ii=0;
					uint32_t un_min=0x3FFFF;
					uint32_t un_max=0;
          uint32_t un_prev_data;
	        int32_t n_brightness;
	        float f_temp;
	        u8 temp[6];
					for(ii=100;ii<500;ii++){
							aun_red_buffer[ii-100]=aun_red_buffer[ii];//将100-500缓存数据移位到0-400
							aun_ir_buffer[ii-100]=aun_ir_buffer[ii];//将100-500缓存数据移位到0-400
							//更新信号的最小值和最大值
							if(un_min>aun_red_buffer[ii])//寻找移位后0-400中的最小值
								un_min=aun_red_buffer[ii];
							if(un_max<aun_red_buffer[ii])//寻找移位后0-400中的最大值
								un_max=aun_red_buffer[ii];
					}
					//在计算心率前取100组样本，取的数据放在400-500缓存数组中
					for(ii=400;ii<500;ii++){
						un_prev_data=aun_red_buffer[ii-1];//临时记录上一次读取数据
						while(MAX30102_INT==1);
						max30102_FIFO_ReadBytes(REG_FIFO_DATA,temp);//读取传感器数据，赋值到temp中
						aun_red_buffer[ii] =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];  //将值合并得到实际数字，数组400-500为新读取数据
						aun_ir_buffer[ii] = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   //将值合并得到实际数字，数组400-500为新读取数据
						if(aun_red_buffer[ii]>un_prev_data){//用新获取的一个数值与上一个数值对比
							f_temp=aun_red_buffer[ii]-un_prev_data;
							f_temp/=(un_max-un_min);
							f_temp*=MAX_BRIGHTNESS;//公式（心率曲线）=（新数值-旧数值）/（最大值-最小值）*255
							n_brightness-=(int)f_temp;
							if(n_brightness<0)
								n_brightness=0;
						}
						else{
							f_temp=un_prev_data-aun_red_buffer[ii];
							f_temp/=(un_max-un_min);
							f_temp*=MAX_BRIGHTNESS;//公式（心率曲线）=（旧数值-新数值）/（最大值-最小值）*255
							n_brightness+=(int)f_temp;
							if(n_brightness>MAX_BRIGHTNESS)
								n_brightness=MAX_BRIGHTNESS;
						}

						if(ch_hr_valid == 1 && ch_spo2_valid ==1 && n_heart_rate<150 && n_sp02<100)//使用上一次测量的结论作为检测正确性判断//ch_hr_valid == 1 && n_heart_rate<120
					{
							sprintf(heart,"%d",n_heart_rate);
							ILI9341_DispString_EN_CH ( 20, 80, "心率=");
							ILI9341_DispString_EN ( 60,80, heart );
							sprintf(spo2,"%d",n_sp02);
							ILI9341_DispString_EN_CH ( 20, 100,"血氧=");
							ILI9341_DispString_EN ( 60, 100, spo2 );
						}
	
					}
					maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
}
 void  Step_temp(void)
{
	              //获取原始数据
              MPU6050ReadAcc(Accel);    
               //数据处理
              MPU6050_DateConver(Accel);             
            
              MPU6050ReadGyro(Gyro);//陀螺仪
              MPU6050_ReturnTemp(&Temp);//温度
					 
					 
              int2str(Temp,temp_num);
              ILI9341_DispString_EN_CH ( 20, 40, "温度=" );
              ILI9341_DispString_EN ( 60, 40, temp_num);
        
              //int2str(step_count,temp_num);
		          int2str(Accel[0],temp_num);
              ILI9341_DispString_EN_CH ( 20, 60, "步数=" );
              ILI9341_DispString_EN ( 60, 60, temp_num);
}


void int2str(int x,char *Str)
{
 int t;
 char *Ptr,Buf[5];                
 int i = 0;                          
 Ptr = Str;                           

 while(x > 0)
 {
 t = x % 10;
 x = x / 10;
 Buf[i++] = t+0x30;  // 通过计算把数字编成ASCII码形式
 }
 i -- ;
 for(;i >= 0;i --)  // 将得到的字符串倒序
 {
 *(Ptr++) = Buf[i];
 }
 
 *Ptr = '\0';
}

static void MPU6050_DataAnalyze()
{
    //计算斜率
        for(int i=0;i<50-2;i++)
            {
                //X轴活跃                 
                if((data_temp[i][X_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][X_AXLE]>=data_temp[i][Z_AXLE]))
                {
                    //计算斜率，连续判断3次值，排除误差
                    if((data_temp[i][X_AXLE]-hold_value)<0) 
                        if((data_temp[i+1][X_AXLE]-hold_value)<0)
                            if((data_temp[i+2][X_AXLE]-hold_value)<0)
                        {
                                  if(data_temp[i][X_AXLE] > DATA_COMPARE)
                                    step_count++;
                        }
                }
                //Y轴活跃
                else  if((data_temp[i][Y_AXLE]>=data_temp[i][X_AXLE])&&(data_temp[i][Y_AXLE]>=data_temp[i][Z_AXLE]))
                {
                    //连续判断3次值，排除误差
                    if((data_temp[i][X_AXLE]-hold_value)<0)
                        if((data_temp[i+1][X_AXLE]-hold_value)<0)
                            if((data_temp[i+2][X_AXLE]-hold_value)<0)
                        {                
                                    if(data_temp[i][Y_AXLE] > DATA_COMPARE )
                                    step_count++;                        
                        }
                }
                //Z轴活跃
                else if((data_temp[i][Z_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][Z_AXLE]>=data_temp[i][X_AXLE]))
                {
                  //连续判断3次值，排除误差
                    if((data_temp[i][X_AXLE]-hold_value)<0) 
                        if((data_temp[i+1][X_AXLE]-hold_value)<0)
                            if((data_temp[i+2][X_AXLE]-hold_value)<0)
                        {
                                    if(data_temp[i][Z_AXLE]> DATA_COMPARE)
                                    step_count++;
                        }
                }
    
            }

}

	static void MPU6050_DateConver(short *data_src)
{
  static int i_save= 0;
    int i=0,j=0;
    short max,min;
    //保存采样值
    data_temp[i_save][0] = data_src[0];
    data_temp[i_save][1] = data_src[1];
    data_temp[i_save][2] = data_src[2];
    if ((++i_save)==50) 
    {
        //找出最大值和最小值
        max=min=data_temp[0][0];
        for(i=0;i<50;i++)
            for(j=0;j<3;j++)
            {
                if(max<data_temp[i][j]) max=data_temp[i][j];
                if(min>data_temp[i][j]) min=data_temp[i][j];
            }
            //计算动态阙值
            hold_value = (max+min)/2;
            //计算步数
          MPU6050_DataAnalyze();
        //重新采样
        i_save=0;
    }
}


/*********************************************END OF FILE**********************/
