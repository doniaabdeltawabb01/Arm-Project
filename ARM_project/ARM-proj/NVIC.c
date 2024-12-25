/*
 * NVIC.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Donia
 */

//Includes
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"
//#include "gpio.h"

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    //checks the IRQ num
    if((IRQ_Num >  NUM_OF_IRQ)||(IRQ_Num <= FRIST_IRQ) ){

    }
    else{
        //enable Interrupt request for specific IRQ
        uint8 offset=IRQ_Num/ BITS_NUM;
        volatile uint32 *address = &NVIC_EN0_REG + offset; //adding NVIC equation
        uint32 IRQ_bit = IRQ_Num % BITS_NUM;      //settinng IRQ_bit
        *address |= (1U << IRQ_bit);          //enable NVIC

    }
}
/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    if((IRQ_Num > NUM_OF_IRQ)||(IRQ_Num <= FRIST_IRQ) ){

    }
    else{
        //enable Interrupt request for specific IRQ
        uint8 offset=IRQ_Num/ BITS_NUM;
        volatile uint32 *address = &NVIC_EN0_REG + offset; //adding NVIC equation
        uint32 IRQ_bit = IRQ_Num % BITS_NUM;      //settinng IRQ_bit
        *address &=~ (1U << IRQ_bit);             //DISABLE NVIC

    }
}
/*********************************************************************
 * Service Name: NVIC_NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table ,
                    IRQ_Priority - Number of the priority needed (0-7)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set Interrupt Priority for specific IRQ
 **********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num,NVIC_IRQPriorityType IRQ_Priority){
    if((IRQ_Num > NUM_OF_IRQ)||(IRQ_Num <= FRIST_IRQ) ||  (IRQ_Priority > MAX_PRI) || (IRQ_Priority < MIN_PRI)){

    }
    else{
        uint8 offset = IRQ_Num / INTERRUPT_NUM_PRLN;
        volatile uint32 *address = &NVIC_PRI0_REG + (offset*INTERRUPT_NUM_PRLN);
        uint8 position = ((IRQ_Num % INTERRUPT_NUM_PRLN) * BITS_NUM_PRLN_INTURRUPT)+ PRLN_RESERVED_BITS ;
        *address = (*address & ~(PR_BITS_HEX <<position)) | (IRQ_Priority<<position);
    }
}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table ,

 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt for specific IRQ
 **********************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Num){

    if((Exception_Num < NON_PROGRAMABLE) || (Exception_Num > 6))
        {
            /*DO NOTHING*/
        }
        else
        {
            NVIC_SYSTEM_SYSHNDCTRL |= (1<<(Exception_Num+13));
        }
}
/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table ,

 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt for specific IRQ
 **********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
    if((Exception_Num < NON_PROGRAMABLE) || (Exception_Num > 6))
        {

        }
        else
        {
            NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<(Exception_Num+13));
        }
}
/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in):  Exception_Num - Number of the IRQ from the target vector table ,
                     Exception_Priority - Number of the priority needed (0-7)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set Priority Exception for specific IRQ
 **********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
    if((Exception_Num < FRIST_EXCEPTION_NUM ) ||(Exception_Num > NUM_OF_EXCEPTIONS) ||  (Exception_Priority > MAX_PRI) || (Exception_Priority < MIN_PRI) )
    {

    }
    else
    {
        if(Exception_Num <= NON_PROGRAMABLE )
        {

        }
        else{
            /*
             * uint8 offset = IRQ_Num / INTERRUPT_NUM_PRLN;
        volatile uint32 *address = &NVIC_PRI0_REG + (offset*INTERRUPT_NUM_PRLN);
        uint8 position = ((IRQ_Num % INTERRUPT_NUM_PRLN) * BITS_NUM_PRLN_INTURRUPT)+ PRLN_RESERVED_BITS ;
        *address = (*address & ~(PR_BITS_HEX <<position)) | (IRQ_Priority<<position);
             */
            uint8 offset = Exception_Num / INTERRUPT_NUM_PRLN;
            volatile uint32 *address = &NVIC_SYSTEM_PRI1_REG + (offset*INTERRUPT_NUM_PRLN)-INTERRUPT_NUM_PRLN;
            uint8 position = ((Exception_Num % INTERRUPT_NUM_PRLN) * BITS_NUM_PRLN_INTURRUPT)+ PRLN_RESERVED_BITS ;
            *address = (*address & ~(PR_BITS_HEX <<position)) | (Exception_Priority<<position);
        }
    }
}
