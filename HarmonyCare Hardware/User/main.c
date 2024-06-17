#include "include.h"

char data[128]; 
const char *topics[] = {"kylinBoard"};
unsigned short timeCount = 0;	//发送间隔变量
unsigned char *dataPtr = NULL; 

int main(void)
{	 
		
	 Init_cgq();	 //传感器初始化
	 Hardware_Init();
	 


	 while(OneNet_DevLink())			//接入OneNET
	 OneNet_Subscribe(topics, 1);
	 
	 
	 while(1)
	 {
		 if(timeCount%40 == 0)
		 {
				 GetStep();                   //步数温度测量
				 GetHeart();                  //心率血氧测量
				 Show();                     //图片显示(延时)
		 }
		 SendData();

	 }	
	 
 }

 
 
 
 
  void SendData(void)
{
			 if(++timeCount >= 200)									//发送间隔2s
		{
			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
			
			sprintf(data,"{\"step\":%d,\"temp\":%d,\"heart\":%d,\"sp02\":%d}",getstep(),gettemp(),getheart(),getsp02());
			
			OneNet_Publish("CqTopic", data);
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		 dataPtr = ESP8266_GetIPD(3);
		
		 if(dataPtr != NULL)
		 OneNet_RevPro(dataPtr);

}

