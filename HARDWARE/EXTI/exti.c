#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//Mini STM32������
//�ⲿ�ж� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/01  
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved	  
////////////////////////////////////////////////////////////////////////////////// 	  
 
 
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ


    //GPIOC2	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

////    //GPIOA2	  �ж����Լ��жϳ�ʼ������
////  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);

////  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
////  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//EXTI_Trigger_Rising_Falling;
////  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		
////   	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
////  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
////  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
////  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
////  	NVIC_Init(&NVIC_InitStructure); 
}

 
//void EXTI0_IRQHandler(void)
//{
//  delay_ms(10);    //����
//	if(WK_UP==1)
//	{	  
//		LED0=!LED0;
//		LED1=!LED1;	
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
//}
// void EXTI9_5_IRQHandler(void)
//{			
//	delay_ms(10);   //����			 
//	if(KEY0==0)	{
//		LED0=!LED0;
//	}
// 	 EXTI_ClearITPendingBit(EXTI_Line5);    //���LINE5�ϵ��жϱ�־λ  
//}

u8 lock_jiance_flag;
void EXTI9_5_IRQHandler(void)
{
	//SEGGER_RTT_printf(0, "EXTI1_IRQHandler\n"); 
  //delay_ms(10);    //����			 
  //if(GI_2==0)//
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) ==1)	
	{
		SEGGER_RTT_printf(0, "2-high-EXTI6_IRQHandler\n"); 
		lock_jiance_flag=1;
		//LED2_LOCK = !LED2_LOCK;
		//LED1=!LED1;
	}
	else
	{
		SEGGER_RTT_printf(0, "2-low-EXTI6_IRQHandler\n"); 
		//LED1=!LED1;
	}
	
	
	EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE15��·����λ   EXTI9_5_IRQn
}