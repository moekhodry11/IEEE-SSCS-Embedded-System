# Task2

![Capture](https://github.com/moekhodry11/IEEE-SSCS-Embedded-System/assets/86708003/f44411b9-8381-482f-84ee-985aee8e106a)


# Memory map
## i have to get the base address of the RCC (clock in enabled by deafult)
![image](https://github.com/moekhodry11/IEEE-SSCS-Embedded-System/assets/86708003/f6722626-dc12-4dcf-bcd1-0a6f42f91126)

![image](https://github.com/moekhodry11/IEEE-SSCS-Embedded-System/assets/86708003/597eb7fb-0a79-419c-8cfb-873606f8a213)

![image](https://github.com/moekhodry11/IEEE-SSCS-Embedded-System/assets/86708003/613b253f-5cc0-4e45-9f12-4c7d14460619)

## RCC base add. 0x4002 1000
```c
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
```

## My RCC Functions
```c
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void MRCC_voidInitSysClock(void); //this function is used to initialize the system clock
void MRCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId); //this function is used to enable the clock for the peripherals
void MRCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId); //this function is used to disable the clock for the peripherals
void MRCC_voidSoftReset(void); //this function is used to reset the system
```

## Initialize System Clock

```c
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
```
## Enable Clock
```c
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
```

## Disable Clock
```c
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
```

# problems faced
i was not able to make the reset function, i tried to set and clear some bits in RCC_RC and RCC_CSR reg. but didnt work
when i asked chatGpt, it told me i cant make a software reset using RCC 
![image](https://github.com/moekhodry11/IEEE-SSCS-Embedded-System/assets/86708003/8112551f-4fb1-4fe8-9558-d91238d36466)
