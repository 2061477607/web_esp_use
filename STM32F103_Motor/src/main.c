#include "stm32f1xx_hal.h"
#include "key.h"
#include "motor.h"
#include "led.h"
#include "key.h"
#include "uart.h"
#include "delay.h"
#include "sys.h"

int main(void)
{
	HAL_Init();
	SystemClock_Config();   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	DEBUG_USART_Config();					//��ʼ������
	delay_ms(100);
	LED_Init();							//��ʼ��LED	
	KEY_Init();							//��ʼ������
	
    while(1)
    {
		Usart1_SendString("OK\r\n");          	 	//��ӡOK��ʾ��������
        delay_ms(1000);             	//ÿ��1s��ӡһ�� 
	}
}