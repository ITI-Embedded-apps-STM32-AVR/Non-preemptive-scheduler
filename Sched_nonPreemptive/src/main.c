#include "STD_TYPES.H"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "diag/Trace.h"
#include "os_interface.h"

void aycallback_1(void);
void aycallback_2(void);

task_t  const task1 = {
		.runnable = &aycallback_1,
		.periodctime = 30000,
};

task_t const task2 = {
		.runnable = &aycallback_2,
		.periodctime = 30000,
};

void main()
{
	//enble HSE, and PORTC
	RCC_Init();
	RCC_EnablePreiphiralClock(2, 4);
	sched_Init();
	sched_Start();

}

void aycallback_1(void)
{
	trace_printf("ay string we do it :D thanks sarazzz>_<\n");
}

void aycallback_2(void)
{
	trace_printf("thanks sarazzz enk cuteness  >_<\n");
}
