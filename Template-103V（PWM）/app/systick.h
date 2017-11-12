/*********************************************************************************************************
*
* File                : systick.h
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

#ifndef __SYSTICK_H
#define __SYSTICK_H 

/* Includes ------------------------------------------------------------------*/	   
#include "stm32f10x.h"

/* Private function prototypes -----------------------------------------------*/
void Delay_Init(void);
void Delayms(__IO uint32_t nTime);
void Delayus(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/






























