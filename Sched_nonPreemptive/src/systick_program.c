#include "STD_TYPES.h"
#include "systick_interface.h"


#define STK_BASEADDR              0xE000E010

#define STK_CTRL                  (*(volatile u32 *) (0x00 + STK_BASEADDR))
#define STK_LOAD                  (*(volatile u32 *) (0x04 + STK_BASEADDR))
#define STK_VAL                   (*(volatile u32 *) (0x08 + STK_BASEADDR))
#define STK_CALIB                 (*(volatile u32 *) (0x0C + STK_BASEADDR))

#define COUNTFLAG_MASK     0x00010000
#define CLKSOURCE_MASK     0x00000004
#define TICKINT_MASK       0x00000002
#define ENABLE_MASK        0x00000001

STK_callBack_t STK_callBack;


void STK_Init(void)
{
	//disable  systick
	STK_CTRL &= ~ENABLE_MASK;  

	//diable interrupt of sysytick
	STK_CTRL &= ~TICKINT_MASK;

	//reset zero flag, and current value
	STK_VAL = 0;

	//reset reload value
	STK_LOAD = 0;

	//reset call back
	STK_callBack = 0;
	//set processor clock to AHB
	STK_CTRL &= ~CLKSOURCE_MASK;
}

void STK_configLoadVal(u32 val)
{
	STK_LOAD = val;
}

void STK_controlState(u32 state)
{
	u32 localReg = STK_CTRL;
	localReg &= ~ENABLE_MASK;
	localReg |= state;
	STK_CTRL = localReg;
}

void STK_setCallBack(STK_callBack_t ptr)
{
	STK_callBack = ptr;
}

void STK_controlInterrupt(u32 state)
{
	u32 localReg = STK_CTRL;
	localReg &= ~TICKINT_MASK;
	localReg |= state;
	STK_CTRL = localReg;
}

u32 STK_getVal(void)
{
	return STK_VAL;
}

u8 STK_getZeroFlag(void)
{
	return (!!(STK_CTRL & COUNTFLAG_MASK));
}

void STK_setClkSrc(u32 src)
{
	u32 localReg = STK_CTRL;
	localReg &= ~CLKSOURCE_MASK;
	localReg |= src;
	STK_CTRL = localReg;
}

void STK_setTimeUS(u32 time, u32 AHB_CLK)
{
   (void)time;
   (void)AHB_CLK;
}

void SysTick_Handler(void)
{
	//read register to clear flag
	volatile u32 local = STK_CTRL;
	//ana 3arf eno mwgood bs malksh da3wa blash tetl3 warning :D 3shan mesh most5dm
	(void)local ;

	if (STK_callBack)
	{
		STK_callBack();
	}
	else
	{

	}
}
