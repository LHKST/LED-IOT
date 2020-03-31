#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "usart3.h"
#include "gizwits_product.h" 


/* �û�����ǰ�豸״̬�ṹ��*/
dataPoint_t currentDataPoint;

//Э���ʼ��
void Gizwits_Init(void)
{
	
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
    usart3_init(9600);//WIFI��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();//��������ʼ��
}

//���ݲɼ�
void userHandle(void)
{

    //�жϵ�ǰLED1������
	   if(LED1==0)
	    currentDataPoint.valueLEDonoff = 1;
      else 
	    currentDataPoint.valueLEDonoff = 0;
	
}

//������
 int main(void)
 {		
    int key;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	    //���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	KEY_Init();             //������ʼ��  
    Gizwits_Init();         //Э���ʼ��
	printf("--------������-Э����ֲLED����ʵ��----------\r\n");
	printf("KEY1:AirLink����ģʽ\t KEY_UP:��λ\r\n\r\n");
   	while(1)
	{
	   userHandle();//�û��ɼ�
         
       gizwitsHandle((dataPoint_t *)&currentDataPoint);//Э�鴦��
 		
	    key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1����
		{
			printf("WIFI����AirLink����ģʽ\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-linkģʽ����
		}			
		if(key==WKUP_PRES)//KEY_UP����
		{  
			printf("WIFI��λ����������������\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI��λ
		}
		delay_ms(200);
		LED0=!LED0;
	}	 

} 
 
