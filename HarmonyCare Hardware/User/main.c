#include "include.h"

char data[128]; 
const char *topics[] = {"kylinBoard"};
unsigned short timeCount = 0;	//���ͼ������
unsigned char *dataPtr = NULL; 

int main(void)
{	 
		
	 Init_cgq();	 //��������ʼ��
	 Hardware_Init();
	 


	 while(OneNet_DevLink())			//����OneNET
	 OneNet_Subscribe(topics, 1);
	 
	 
	 while(1)
	 {
		 if(timeCount%40 == 0)
		 {
				 GetStep();                   //�����¶Ȳ���
				 GetHeart();                  //����Ѫ������
				 Show();                     //ͼƬ��ʾ(��ʱ)
		 }
		 SendData();

	 }	
	 
 }

 
 
 
 
  void SendData(void)
{
			 if(++timeCount >= 200)									//���ͼ��2s
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

