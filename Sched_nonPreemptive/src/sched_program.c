#include "STD_TYPES.h"
#include "sched_interface.h"
#include "sched_config.h"
#include "systick_interface.h"

typedef struct
{
	SCHED_systask_info_t const * task;
	u32 remainToExec;
	u32 periodTicks;
	u32 state;
} SCHED_systask_t;

/* array defined in the config.c file */
extern const SCHED_systask_info_t tasks_config[SCHED_MAX_TASKS];

/* array of tasks */
static SCHED_systask_t  systask[SCHED_MAX_TASKS];

/* raised when tick time is over */
static volatile u8 os_flag = 0;


static void SCHED_SetOSFlag(void);

static void SCHED_Loop(void);


void SCHED_Init(void)
{
	u8 i;
	for(i = 0; i < SCHED_MAX_TASKS; i++)
	{
		/* refer to the task runnable */
		systask[i].task = & tasks_config[i];

		/* first delay hybd2 emta */
		systask[i].remainToExec = tasks_config[i].delayMs / SCHED_TICK_TIME;

		/* deh hygy kol 2d eh :D */
		systask[i].periodTicks = tasks_config[i].apptask->periodicTimeMs / SCHED_TICK_TIME;

		/* malnash d3wa beh nw */
		systask[i].state = 0;
	}
}

void SCHED_Start(void)
{
	//henna 3mla cast leh  64 3shan by3ml overflow feh multiplication feh 2rkam el kbeera
		//b3d keda hanrg3ha tany cast u32 3shan div :D cute ana
		u32 counts_timer = (u32)(( (u64) SCHED_TICK_TIME * SCHED_AHB_CLK) / 8000);

		STK_Init();
		STK_configLoadVal(counts_timer - 1);
		STK_setClkSrc(STK_CLKSRC_DIV_8);
		STK_controlInterrupt(STK_INTERRUPT_ENABLE);
		STK_setCallBack(&SCHED_SetOSFlag);
		STK_controlState(STK_STATE_ENABLE);

		while (1)
		{
			SCHED_Loop();
		}
}

static void SCHED_SetOSFlag(void)
{
	os_flag = 1;
}

static void SCHED_Loop(void)
{
	u8 i;

	if (os_flag == 1) /* if OS flag was raised */
	{
		os_flag = 0; /* reset the flag */

		for (i = 0; i < SCHED_MAX_TASKS; i++) /* foreach task */
		{
			if(systask[i].remainToExec == 0) /* if task has timed out */
			{
				systask[i].task->apptask->runnable(); /* call its runnable */
				systask[i].remainToExec = systask[i].periodTicks; /* reset its remaining ticks */
			}

			/* decrement the remaining ticks counter */
			systask[i].remainToExec --;
		}
	}
	else /* if OS flag was not raised */
	{

	}

}
