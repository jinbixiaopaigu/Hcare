#include "include.h"
#include "cgq.h"
#include "pic.h"



void Hardware_Init(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置

	delay_init();									//systick初始化
	
	Usart1_Init(115200);							//串口1，打印信息用
	
	Usart3_Init(115200);							//串口3，驱动ESP8266用
	Usart_SendString(USART1, (unsigned char *)"Hello, USART1!\r\n", 17);
  Usart_SendString(USART3, (unsigned char *)"Hello, USART3!\r\n", 17);
	ESP8266_Init(115200);
	
	//Beep_Init();									//蜂鸣器初始化
	
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
}

void Init_cgq(void)
{
		//delay初始化
		delay_init();
	  delay_ms(1000);
	  //LCD 初始化
    ILI9341_Init ();   
    //I2C初始化
    i2c_GPIO_Config();
		IIC_Init();
    //led初始化
		LED_GPIO_Config(); 
		//6050初始化
    MPU6050_Init();
	  //30102初始化
		max30102_init();
}
void Load(void)
{
	int m;
	for(m=0;m<100;m++){
		sprintf(loading,">>>>>>>正在加载,请稍后： %d ％",m);
		ILI9341_DispStringLine_EN_CH(LINE(0),loading);
		load++;
		m=load/7;
	  }		
}

void Init_Background(void)
{
		//初始化背景图
	 ILI9341_GramScan ( 6 );
	 LCD_Showimage(0, 0, 240, 320, gImage_666);
	
}

void Clean_Background(void)
{
	 ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
	 LCD_SetColors(BLACK,WHITE);
}	

void Show(void)
{
	         //静态图显示
	         ILI9341_Clear(0,200,LCD_X_LENGTH,LCD_Y_LENGTH);
           if(flag==1)
           LCD_Showimage(0, 200,120, 120, gImage_999);		
           if(flag==-1)		
           LCD_Showimage(0, 200, 120, 120, gImage_888);

			
	
		       //动态图显示
	         LCD_Showimage(190,270, 48, 48, gImage_1);
	         Delay(0x0bffff);
	         ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_2);
	         Delay(0x0bffff);
	         ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_3);
       		 Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_4);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_5);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190,270, 48, 48, gImage_6);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_7);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_8);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_9);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_10);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190,270, 48, 48, gImage_11);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_12);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_13);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_14);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
	         LCD_Showimage(190, 270, 48, 48, gImage_15);
		       Delay(0x0bffff);
		       ILI9341_Clear(190,270,LCD_X_LENGTH,LCD_Y_LENGTH);
  	       flag=-flag;
}
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*static void  Heart_spo2(void)
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
							
						//printf("Red Data[%d]: %lu, IR Data[%d]: %lu\n", ii, aun_red_buffer[ii], ii, aun_ir_buffer[ii]);
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
						maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);

						// ??????
						//printf("Heart Rate: %d, SpO2: %d\n", n_heart_rate, n_sp02);
						if(ch_hr_valid == 1 && ch_spo2_valid ==1 && n_heart_rate<=150 && n_sp02<98&& n_sp02>90)//使用上一次测量的结论作为检测正确性判断//ch_hr_valid == 1 && n_heart_rate<120
						{
							sprintf(heart,"%d",n_heart_rate);
						  //int2str(n_heart_rate,heart);
							ILI9341_DispString_EN_CH ( 20, 80, "心率=");
							ILI9341_DispString_EN ( 60,80, heart );
							sprintf(spo2,"%d",n_sp02);
						  //int2str(n_sp02,spo2);
							ILI9341_DispString_EN_CH ( 20, 100,"血氧=");
							ILI9341_DispString_EN ( 60, 100, spo2 );
						}else {
							// ???????????
							//printf("Invalid Data - Heart Rate: %d, SpO2: %d\n", n_heart_rate, n_sp02);
						}

					}

					maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
}*/

static void Heart_spo2(void)
{
    int ii = 0;
    uint32_t un_min = 0x3FFFF;
    uint32_t un_max = 0;
    uint32_t un_prev_data;
    int32_t n_brightness;
    float f_temp;
    u8 temp[6];

    // ????????????
    for(ii = 100; ii < 500; ii++) {
        aun_red_buffer[ii - 100] = aun_red_buffer[ii];
        aun_ir_buffer[ii - 100] = aun_ir_buffer[ii];
        if(un_min > aun_red_buffer[ii]) 
            un_min = aun_red_buffer[ii];
        if(un_max < aun_red_buffer[ii])
            un_max = aun_red_buffer[ii];
    }

    // ??????
    for(ii = 400; ii < 500; ii++) {
        un_prev_data = aun_red_buffer[ii - 1];
        while(MAX30102_INT == 1);
        max30102_FIFO_ReadBytes(REG_FIFO_DATA, temp);
        aun_red_buffer[ii] = (long)((long)((long)temp[0] & 0x03) << 16) | (long)temp[1] << 8 | (long)temp[2];
        aun_ir_buffer[ii] = (long)((long)((long)temp[3] & 0x03) << 16) | (long)temp[4] << 8 | (long)temp[5];

        // ??????
        //UsartPrintf(USART_DEBUG, "IR Data[%d]: %lu, Red Data[%d]: %lu\n", ii, aun_ir_buffer[ii], ii, aun_red_buffer[ii]);

        if(aun_red_buffer[ii] > un_prev_data) {
            f_temp = aun_red_buffer[ii] - un_prev_data;
            f_temp /= (un_max - un_min);
            f_temp *= MAX_BRIGHTNESS;
            n_brightness -= (int)f_temp;
            if(n_brightness < 0)
                n_brightness = 0;
        } else {
            f_temp = un_prev_data - aun_red_buffer[ii];
            f_temp /= (un_max - un_min);
            f_temp *= MAX_BRIGHTNESS;
            n_brightness += (int)f_temp;
            if(n_brightness > MAX_BRIGHTNESS)
                n_brightness = MAX_BRIGHTNESS;
        }

        // ?????????(??)
        aun_red_buffer[ii] = (aun_red_buffer[ii] + aun_red_buffer[ii - 1] + aun_red_buffer[ii - 2]) / 3;
        aun_ir_buffer[ii] = (aun_ir_buffer[ii] + aun_ir_buffer[ii - 1] + aun_ir_buffer[ii - 2]) / 3;

        maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);

        // ????????
        

        // ???????
        if (n_heart_rate < 30 || n_heart_rate > 220 || n_sp02 < 70 || n_sp02 > 100) {
            // ??????
            //UsartPrintf(USART_DEBUG, "Invalid Data - Heart Rate: %d, SpO2: %d\n", n_heart_rate, n_sp02);
            continue;
        }

        // ????????
        if(ch_hr_valid == 1 && ch_spo2_valid == 1 && n_heart_rate <= 180 && n_heart_rate >= 40 && n_sp02 <= 100 && n_sp02 >= 85) {
					//UsartPrintf(USART_DEBUG, "Processed Heart Rate: %d, SpO2: %d\n", n_heart_rate, n_sp02);
            sprintf(heart, "%d", n_heart_rate);
            ILI9341_DispString_EN_CH(20, 80, "心率=");
            ILI9341_DispString_EN(60, 80, heart);
            sprintf(spo2, "%d", n_sp02);
            ILI9341_DispString_EN_CH(20, 100, "血氧=");
            ILI9341_DispString_EN(60, 100, spo2);
					//UsartPrintf(USART_DEBUG, "Processed String Heart Rate: %s, String SpO2: %s\n", heart, spo2);
        } else {
            // ??????
            UsartPrintf(USART_DEBUG, "Invalid Data - Heart Rate: %d, SpO2: %d\n", n_heart_rate, n_sp02);
        }
    }
}



static void  Step_temp(void)
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
        
              int2str(step_count,temp_num);
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

static void MPU6050_DateConver(short *data_src)
{
  static int i_save= 0;
    int i=0;
    //保存采样值
    data_temp[i_save][0] = data_src[0];
    data_temp[i_save][1] = data_src[1];
    data_temp[i_save][2] = data_src[2];
    //X轴活跃                 
                if((data_temp[i][X_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][X_AXLE]>=data_temp[i][Z_AXLE]))
                {
                    
                                  if(data_temp[i][X_AXLE] > DATA_COMPARE)
                                    step_count++;
                        
                }
                //Y轴活跃
                else  if((data_temp[i][Y_AXLE]>=data_temp[i][X_AXLE])&&(data_temp[i][Y_AXLE]>=data_temp[i][Z_AXLE]))
                {
                       
                                    if(data_temp[i][Y_AXLE] > DATA_COMPARE )
                                    step_count++;                        
                }
                //Z轴活跃
                else if((data_temp[i][Z_AXLE]>=data_temp[i][Y_AXLE])&&(data_temp[i][Z_AXLE]>=data_temp[i][X_AXLE]))
                {
                
                                    if(data_temp[i][Z_AXLE]> DATA_COMPARE)
                                    step_count++;
                        
                }
								
        //重新采样
        i_save=0;
    }

void  GetStep()
{
	Step_temp();
}

void  GetHeart()
{
	Heart_spo2();
}


int getstep(void)
{
	return step_count;
}

int getheart(void)
{
	return n_heart_rate;
}

int gettemp(void)
{
	return Temp;
}

int getsp02(void)
{
	return n_sp02;
}
