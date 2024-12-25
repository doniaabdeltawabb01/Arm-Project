/*
 * SysTick.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Donia
 */

#include"SysTick.h"


static volatile void(*g_CallBackPtr)(void)=NULL_PTR;

void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
       SYSTICK_RELOAD_REG  = 15999* a_TimeInMilliSeconds;       /* Set the Reload value with 15999999 to count 1 Second */
       SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
       /* Configure the SysTick Control Register
        * Enable the SysTick Timer (ENABLE = 1)
        * Disable SysTick Interrupt (INTEN = 1)
        * Choose the clock source to be System Clock (CLK_SRC = 1) */
       SYSTICK_CTRL_REG   |= 0x07;
}

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
    SysTick_Init(a_TimeInMilliSeconds);
    while(!(SYSTICK_CTRL_REG & (1<<16)));
}

void SysTick_Handler(void){
    if(g_CallBackPtr!=NULL_PTR){
        (*g_CallBackPtr)();
    }
}
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    g_CallBackPtr=Ptr2Func;
}
void SysTick_Stop(void){
    SYSTICK_CTRL_REG = 0;
}
void SysTick_Start(void){
    SYSTICK_CTRL_REG   |= 0x07;
}
void SysTick_DeInit(void){
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG = 0;
}
