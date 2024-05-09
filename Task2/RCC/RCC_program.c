/****************************************************************/
/***************  Name   : Mohamed Khodary **********************/
/***************  Date   : 17/10/2023      **********************/
/***************  SWC    : RCC		       **********************/
/*************** Version : 1.0             **********************/
/****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void MRCC_voidInitSysClock(void)
{
#if RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	RCC_CR = 0x00010000; /* Enable HSE with no bypass */
	RCC_CFGR = 0x00000001; /* Select HSE as system clock */

#elif RCC_CLOCK_TYPE == RCC_HSE_RC
	RCC_CR = 0x00050000; /* Enable HSE with bypass */
	RCC_CFGR = 0x00000001; /* Select HSE as system clock */

#elif RCC_CLOCK_TYPE == RCC_HSI
	RCC_CR = 0x00000081; /* Enable HSI + Trimming = 0 */
	RCC_CFGR = 0x00000000; /* Select HSI as system clock */

#elif RCC_CLOCK_TYPE == RCC_PLL 
	/* Choose the clock input to the PLL */
#if RCC_PLL_INPUT == RCC_PLL_HSI_DIV_2 
	SET_BIT(RCC_CFGR, 16);


#elif RCC_PLL_INPUT == RCC_PLL_HSE_DIV_2 
	SET_BIT(RCC_CFGR, 17);
	CLR_BIT(RCC_CFGR, 16);


#elif RCC_PLL_INPUT == RCC_PLL_HSE 
	SET_BIT(RCC_CFGR, 16);
	SET_BIT(RCC_CFGR, 17);

#endif

#else
#error("You chosed Wrong Clock type")
#endif
}

void MRCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	//Copy_u8BusId is the bus that the peripheral is connected to like AHB, APB1, APB2
	//Copy_u8PerId is the peripheral that we want to enable its clock like GPIOA, GPIOB, GPIOC, ...
	if (Copy_u8PerId <= 31) //this is the maximum number of the peripherals that can be connected to the AHB, APB1, APB2 buses
	{
		switch (Copy_u8BusId)
		{
		case RCC_AHB:
			SET_BIT(RCC_AHBENR, Copy_u8PerId);
			break;
		case RCC_APB1:
			SET_BIT(RCC_APB1ENR, Copy_u8PerId);
			break;
		case RCC_APB2:
			SET_BIT(RCC_APB2ENR, Copy_u8PerId);
			break;
		}
	}

	else
	{
		/* Return Error */
	}
}

void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31)
	{
		switch (Copy_u8BusId)
		{
		case RCC_AHB:
			CLR_BIT(RCC_AHBENR, Copy_u8PerId);
			break;
		case RCC_APB1:
			CLR_BIT(RCC_APB1ENR, Copy_u8PerId);
			break;
		case RCC_APB2:
			CLR_BIT(RCC_APB2ENR, Copy_u8PerId);
			break;
		}
	}

	else
	{
		/* Return Error */
	}
}

void MRCC_voidSoftReset(void)
{
	
}
