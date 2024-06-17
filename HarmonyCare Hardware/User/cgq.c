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



//����������һЩ����

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
							aun_red_buffer[ii-100]=aun_red_buffer[ii];//��100-500����������λ��0-400
							aun_ir_buffer[ii-100]=aun_ir_buffer[ii];//��100-500����������λ��0-400
							//�����źŵ���Сֵ�����ֵ
							if(un_min>aun_red_buffer[ii])//Ѱ����λ��0-400�е���Сֵ
								un_min=aun_red_buffer[ii];
							if(un_max<aun_red_buffer[ii])//Ѱ����λ��0-400�е����ֵ
								un_max=aun_red_buffer[ii];
					}
					//�ڼ�������ǰȡ100��������ȡ�����ݷ���400-500����������
					for(ii=400;ii<500;ii++){
						un_prev_data=aun_red_buffer[ii-1];//��ʱ��¼��һ�ζ�ȡ����
						while(MAX30102_INT==1);
						max30102_FIFO_ReadBytes(REG_FIFO_DATA,temp);//��ȡ���������ݣ���ֵ��temp��
						aun_red_buffer[ii] =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];  //��ֵ�ϲ��õ�ʵ�����֣�����400-500Ϊ�¶�ȡ����
						aun_ir_buffer[ii] = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   //��ֵ�ϲ��õ�ʵ�����֣�����400-500Ϊ�¶�ȡ����
						if(aun_red_buffer[ii]>un_prev_data){//���»�ȡ��һ����ֵ����һ����ֵ�Ա�
							f_temp=aun_red_buffer[ii]-un_prev_data;
							f_temp/=(un_max-un_min);
							f_temp*=MAX_BRIGHTNESS;//��ʽ���������ߣ�=������ֵ-����ֵ��/�����ֵ-��Сֵ��*255
							n_brightness-=(int)f_temp;
							if(n_brightness<0)
								n_brightness=0;
						}
						else{
							f_temp=un_prev_data-aun_red_buffer[ii];
							f_temp/=(un_max-un_min);
							f_temp*=MAX_BRIGHTNESS;//��ʽ���������ߣ�=������ֵ-����ֵ��/�����ֵ-��Сֵ��*255
							n_brightness+=(int)f_temp;
							if(n_brightness>MAX_BRIGHTNESS)
								n_brightness=MAX_BRIGHTNESS;
						}

						if(ch_hr_valid == 1 && ch_spo2_valid ==1 && n_heart_rate<150 && n_sp02<100)//ʹ����һ�β����Ľ�����Ϊ�����ȷ���ж�//ch_hr_valid == 1 && n_heart_rate<120
					{
							sprintf(heart,"%d",n_heart_rate);
							ILI9341_DispString_EN_CH ( 20, 80, "����=");
							ILI9341_DispString_EN ( 60,80, heart );
							sprintf(spo2,"%d",n_sp02);
							ILI9341_DispString_EN_CH ( 20, 100,"Ѫ��=");
							ILI9341_DispString_EN ( 60, 100, spo2 );
						}
	
					}
					maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
}
 void  Step_temp(void)
{
	              //��ȡԭʼ����
              MPU6050ReadAcc(Accel);    
               //���ݴ���
              MPU6050_DateConver(Accel);             
            
              MPU6050ReadGyro(Gyro);//������
              MPU6050_ReturnTemp(&Temp);//�¶�
					 
					 
              int2str(Temp,temp_num);
              ILI9341_DispString_EN_CH ( 20, 40, "�¶�=" );
              ILI9341_DispString_EN ( 60, 40, temp_num);
        
              //int2str(step_count,temp_num);
		          int2str(Accel[0],temp_num);
              ILI9341_DispString_EN_CH ( 20, 60, "����=" );
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
 Buf[i++] = t+0x30;  // ͨ����������ֱ��ASCII����ʽ
 }
 i -- ;
 for(;i >= 0;i --)  // ���õ����ַ�������
 {
 *(Ptr++) = Buf[i];
 }
 
 *Ptr = '\0';
}

static void MPU6050_DataAnalyze()
{
    //����б��
        for(int i=0;i<50-2;i++)
            {
                //X���Ծ                 
                if((data_temp[i][X_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][X_AXLE]>=data_temp[i][Z_AXLE]))
                {
                    //����б�ʣ������ж�3��ֵ���ų����
                    if((data_temp[i][X_AXLE]-hold_value)<0) 
                        if((data_temp[i+1][X_AXLE]-hold_value)<0)
                            if((data_temp[i+2][X_AXLE]-hold_value)<0)
                        {
                                  if(data_temp[i][X_AXLE] > DATA_COMPARE)
                                    step_count++;
                        }
                }
                //Y���Ծ
                else  if((data_temp[i][Y_AXLE]>=data_temp[i][X_AXLE])&&(data_temp[i][Y_AXLE]>=data_temp[i][Z_AXLE]))
                {
                    //�����ж�3��ֵ���ų����
                    if((data_temp[i][X_AXLE]-hold_value)<0)
                        if((data_temp[i+1][X_AXLE]-hold_value)<0)
                            if((data_temp[i+2][X_AXLE]-hold_value)<0)
                        {                
                                    if(data_temp[i][Y_AXLE] > DATA_COMPARE )
                                    step_count++;                        
                        }
                }
                //Z���Ծ
                else if((data_temp[i][Z_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][Z_AXLE]>=data_temp[i][X_AXLE]))
                {
                  //�����ж�3��ֵ���ų����
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
    //�������ֵ
    data_temp[i_save][0] = data_src[0];
    data_temp[i_save][1] = data_src[1];
    data_temp[i_save][2] = data_src[2];
    if ((++i_save)==50) 
    {
        //�ҳ����ֵ����Сֵ
        max=min=data_temp[0][0];
        for(i=0;i<50;i++)
            for(j=0;j<3;j++)
            {
                if(max<data_temp[i][j]) max=data_temp[i][j];
                if(min>data_temp[i][j]) min=data_temp[i][j];
            }
            //���㶯̬��ֵ
            hold_value = (max+min)/2;
            //���㲽��
          MPU6050_DataAnalyze();
        //���²���
        i_save=0;
    }
}


/*********************************************END OF FILE**********************/
