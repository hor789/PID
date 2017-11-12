/******************** (C) COPYRIGHT 2012 WildFire Team **************************
LED0----PB0
LED1----PB1
LED2----PB14 
TX----PA9
RX----PA10
pwm----(TIM3 OC2) PB5

 波特率：115200 ,在配置中需要打开mircolib否则无法通信
 这里串口中断为发送数据自动返回，若不需要可以在Usart1_Init()中屏蔽NVIC
 
//prer:分频数:0~7(只有低3位有效!)
//分频因子=4*2^prer.但最大值只能是256!  
//rlr:重装载寄存器值:1~4096(低11位有效)
   Tout=((4*2^prer)*rlr)/40 (ms)
   IWDG_Init(4,625);//与分频数为64,重载值为625,溢出时间为1s,必须在1s内喂狗
	 
	 TIM3_PWM_Init(899,0);Freq=SYS_clk/((arr+1)*(psc+1))=72M/(900*1)=72K
	 TIM_SetCompare2(TIM3,pwmval); PWM占空比crr/arr+1=pwmval/arr+1,或者修改TIM_OCInitStructure.TIM_Pulse
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "systick.h"
#include "usart1.h"
#include "wdg.h"
#include "pwm.h"
int main(void)
{	
	u16 pwmval=450;
	LED_GPIO_Config();
	Motor_GPIO_Config();
	Usart1_Init();
	Delay_Init();
	//IWDG_Init(4,625);
	TIM3_PWM_Init(899,0);
	printf("\r\n USART1 Interrupt("__DATE__ " - " __TIME__ ")\r\n");
	GPIO_WriteBit(GPIOB,GPIO_Pin_0, 0);
	Delayms(100);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0, 1);
	//GPIO_WriteBit(GPIOE,GPIO_Pin_8, 1);
	while (1)
	{
   IWDG_Feed();	
	 TIM_SetCompare2(TIM3,pwmval);
	 GPIO_WriteBit(GPIOB,GPIO_Pin_0, 0);
	 Delayms(500);
	 IWDG_Feed();	
	 GPIO_WriteBit(GPIOB,GPIO_Pin_0, 1);
	 Delayms(500);
	}
}




/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
