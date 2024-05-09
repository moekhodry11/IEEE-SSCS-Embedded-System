/****************************************************************/
/***************  Name   : Mohamed Khodary **********************/
/***************  Date   : 17/10/2023      **********************/
/***************  SWC    : RCC		       **********************/
/*************** Version : 1.0             **********************/
/****************************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*******************************************************************************
 *                      Registers Definitions                                  *
 *******************************************************************************/
//i just used 5 regiesters from the RCC regiesters
#define RCC_CR *((volatile u32 *)0x40021000) //this regester is used to enable the clock for the system
#define RCC_CFGR *((volatile u32 *)0x40021004) //this regester is used to configure the clock for the system
#define RCC_CIR *((volatile u32 *)0x40021008)
#define RCC_APB2RSTR *((volatile u32 *)0x4002100C)
#define RCC_APB1RSTR *((volatile u32 *)0x40021010)
#define RCC_AHBENR *((volatile u32 *)0x40021014) //this regester is used to enable the clock for the peripherals connected to the AHB bus
#define RCC_APB2ENR *((volatile u32 *)0x40021018) //this regester is used to enable the clock for the peripherals connected to the APB2 bus
#define RCC_APB1ENR *((volatile u32 *)0x4002101C) //this regester is used to enable the clock for the peripherals connected to the APB1 bus
#define RCC_BDCR *((volatile u32 *)0x40021020)
#define RCC_CSR *((volatile u32 *)0x40021024)

/*******************************************************************************
 *                      Hash Defines For Conguration                           *
 *******************************************************************************/

/* Clock Types  */
#define RCC_HSE_CRYSTAL 0 //this is the type of the clock that is connected to the system from an external crystal oscillator 
#define RCC_HSE_RC 1 //this is the type of the clock that is connected to the system from an external RC oscillator
#define RCC_HSI 2   //this is the type of the clock that is generated from the internal RC oscillator
#define RCC_PLL 3  //this is the type of the clock that is generated from the internal RC oscillator and it is used to increase the frequency of the system clock

/* PLL Options */
#define RCC_PLL_HSI_DIV_2 0 //this is the option that is used to select the clock source for the PLL from the HSI clock divided by 2
#define RCC_PLL_HSE_DIV_2 1 //this is the option that is used to select the clock source for the PLL from the HSE clock divided by 2
#define RCC_PLL_HSE 2 //this is the option that is used to select the clock source for the PLL from the HSE clock

#endif
