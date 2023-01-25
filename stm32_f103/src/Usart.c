#include "Usart.h"
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
//extern uint8_t ucTemp;  

 /**
  * @brief  DEBUG_USART GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */  
void DEBUG_USART_Config(void)
{ 
  
  huart1.Instance          = DEBUG_USART;
  
  huart1.Init.BaudRate     = DEBUG_USART_BAUDRATE;
  huart1.Init.WordLength   = UART_WORDLENGTH_8B;
  huart1.Init.StopBits     = UART_STOPBITS_1;
  huart1.Init.Parity       = UART_PARITY_NONE;
  huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart1.Init.Mode         = UART_MODE_TX_RX;
  
  HAL_UART_Init(&huart1);
    
 /*使能串口接收断 */
  __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);  
}
void AT_USART_Config(void)
{ 
  
  huart2.Instance          = AT_USART;
  
  huart2.Init.BaudRate     = AT_USART_BAUDRATE;
  huart2.Init.WordLength   = UART_WORDLENGTH_8B;
  huart2.Init.StopBits     = UART_STOPBITS_1;
  huart2.Init.Parity       = UART_PARITY_NONE;
  huart2.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  huart2.Init.Mode         = UART_MODE_TX_RX;
  
  HAL_UART_Init(&huart2);
    
 /*使能串口接收断 */
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);  
}

/**
  * @brief UART MSP 初始化 
  * @param huart: UART handle
  * @retval 无
  */
void HAL_UART_MspInit(UART_HandleTypeDef *usart_Handle)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    if(usart_Handle->Instance==DEBUG_USART)
    {
      DEBUG_USART_CLK_ENABLE();

      DEBUG_USART_RX_GPIO_CLK_ENABLE();
      DEBUG_USART_TX_GPIO_CLK_ENABLE();

      /**USART1 GPIO Configuration    
       PA9     ------> USART1_TX
      PA10    ------> USART1_RX 
      */
      /* 配置Tx引脚为复用功能  */
      GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
      HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

      /* 配置Rx引脚为复用功能 */
      GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
      GPIO_InitStruct.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
      HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
      //抢占优先级0，子优先级1
      HAL_NVIC_SetPriority(DEBUG_USART_IRQ ,0,1);	
          //使能USART1中断通道  
      HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ );		
    }
    else
    {
      if(usart_Handle->Instance==AT_USART)
      {
        AT_USART_CLK_ENABLE();

        AT_USART_RX_GPIO_CLK_ENABLE();
        AT_USART_TX_GPIO_CLK_ENABLE();

      
        // 配置Tx引脚为复用功能  
        GPIO_InitStruct.Pin = AT_USART_TX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(AT_USART_TX_GPIO_PORT, &GPIO_InitStruct);

        // 配置Rx引脚为复用功能 
        GPIO_InitStruct.Pin = AT_USART_RX_PIN;
        GPIO_InitStruct.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
        HAL_GPIO_Init(AT_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
        //抢占优先级0，子优先级1
        HAL_NVIC_SetPriority(AT_USART_IRQ ,0,1);	
            //使能USART1中断通道  
        HAL_NVIC_EnableIRQ(AT_USART_IRQ );
      }

    }
}
/*
void HAL_UART_MspInit(UART_HandleTypeDef *huart2)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    
    AT_USART_CLK_ENABLE();

    AT_USART_RX_GPIO_CLK_ENABLE();
    AT_USART_TX_GPIO_CLK_ENABLE();

   
    // 配置Tx引脚为复用功能  
    GPIO_InitStruct.Pin = AT_USART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AT_USART_TX_GPIO_PORT, &GPIO_InitStruct);

    // 配置Rx引脚为复用功能 
    GPIO_InitStruct.Pin = AT_USART_RX_PIN;
    GPIO_InitStruct.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
    HAL_GPIO_Init(AT_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
    //抢占优先级0，子优先级1
    HAL_NVIC_SetPriority(AT_USART_IRQ ,0,1);	
        //使能USART1中断通道  
    HAL_NVIC_EnableIRQ(AT_USART_IRQ );		
    
}*/

/*****************  发送字符串 **********************/
void Usart1_SendString(uint8_t *str)
{
    unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart1,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
void Usart2_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&huart2,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
//重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

//重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{		
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}




