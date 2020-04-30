/**
 * @file  sched_interface.h
 * @brief This file is to be used as an implementation of the scheduler driver.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef SCHED_INTERFACE_H_
#define SCHED_INTERFACE_H_

typedef void(*SCHED_task_runnable_t)(void);

typedef struct
{
	SCHED_task_runnable_t  runnable;
	u32              periodicTimeMs;
} SCHED_task_t;

/**
 * @brief Initialize scheduler
 * @param void
 * @return void
 */
void SCHED_Init(void);

/**
 * @brief Start the scheduler
 * @param void
 * @return void
 */
void SCHED_Start(void);

#endif /* SCHED_INTERFACE_H_ */
