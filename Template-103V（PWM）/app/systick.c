/*********************************************************************************************************
*
* File                : systick.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "systick.h"
#include <core_cm3.h>

/* Private variables ---------------------------------------------------------*/	 
static __IO uint32_t TimingDelay;

void Delay_Init(void)
{
  if (SysTick_Config(SystemCoreClock / 1000000))//1us  72M/1000000*T(1/f=72M, ±÷”÷‹∆⁄)£¨T=1/72us
	//if (SysTick_Config(SystemCoreClock / 1000))//1ms
  { 
    /* Capture error */ 
    while (1);
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delayms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime*1000;

  while(TimingDelay != 0);
}

void Delayus(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
















