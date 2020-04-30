/**
 * @file  sched_config.h
 * @brief This file is to be used as an implementation of the scheduler configuration.
 *
 * @author MSN
 * @date Mar 31, 2020
 *
 */

#ifndef SCHED_CONFIG_H_
#define SCHED_CONFIG_H_


#define  SCHED_MAX_TASKS   2

#define  SCHED_TICK_TIME   2

#define  SCHED_AHB_CLK     8000000


typedef struct
{
	SCHED_task_t const * apptask;
	u32                  delayMs;
} SCHED_systask_info_t;

#endif /* SCHED_CONFIG_H_ */
