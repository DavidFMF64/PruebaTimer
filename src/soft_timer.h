/****************************** C SOURCE FILE ********************************
** Project	: AX00															**
** Filename	: TIMER.H														**
** Version	: 1.00															**
** Date		: February 29, 2009												**
** Comments	: Main module													**
******************************************************************************
** Copyright (c) 2009, BioSystems S.A.										**
** All rights reserved.														**
******************************************************************************

VERSION HISTORY:
----------------
Version		: 1.00
Date		: February 29, 2009
Revised by	:
Description	: Original version

******************************************************************************/

#ifndef _TIMER_H
#define _TIMER_H

/*****************************************************************************/
/**						MODULES USED										**/
/*****************************************************************************/


/*****************************************************************************/
/**						DEFINITIONS AND MACROS								**/
/*****************************************************************************/

typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;

/* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;



/*****************************************************************************/
/**						TYPEDEFS AND STRUCTURES								**/
/*****************************************************************************/

#define SYSTICK_PERIOD_100us	(10000)	//0.1ms
#define SYSTICK_PERIOD_1ms		(1000)	//1ms
#define SYSTICK_PERIOD_10ms		(100)	//10ms
#define SYSTICK_PERIOD_100ms	(10)	//100ms

#define SYSTICK_PERIOD				(SYSTICK_PERIOD_1ms)


// Los timers software se basaran en el SysTick
#if (SYSTICK_PERIOD == SYSTICK_PERIOD_1ms)
	#define TICS_PER_MILISECOND		(1)
#endif



#define TICS_PER_SECOND				(1000*(TICS_PER_MILISECOND))
#define TICS_PER_MINUTE				(60*(TICS_PER_SECOND))
#define TICS_PER_HOUR				(60*(TICS_PER_MINUTE))


typedef enum
{
	TIMER_BASE_100us = 0,
	TIMER_BASE_1ms,
	TIMER_BASE_1s,
	TIMER_BASE_1min,
	TIMER_BASE_1hour,
	TIMER_BASE_MAX
} EnumTimerBase;

typedef enum
{
	TIMER_STATE_FLAGGED = 0,
	TIMER_STATE_RUNNING,
	TIMER_STATE_PAUSED,
	TIMER_STATE_STOPPED,
	MAX_TIMER_STATE
} EnumTimerState;

typedef enum
{
    TIMER_MEASURE_WELL_TICK=0,
    TIMER_FST_MOV_TICK=1,
    TIMER_FST_MED_TICK=2,
    TIMER_DELAY_TICK = 3,
    TIMER_ADC_TERMO=4,
	TIMER_MAX
} EnumTimer;

#if (SYSTICK_PERIOD == SYSTICK_PERIOD_1ms)
typedef enum
{
	TIMER_MEASURE_WELL_TICK_VALUE_1ms       = 800,  //RESTO DE MEDIDAS
    TIMER_MEASURE_FIRST_WELL_TICK_VALUE_1ms = 300,  //PRIMERA MEDIDA
    TIMER_MEASURE_MOV_TICK_VALUE_1ms = 300,
    TIMER_MEASURE_MED_TICK_VALUE_1ms = 500,
    TIMER_FST_300ms = 300,
    TIMER_FST_800ms = 800,
    TIMER_DELAY_TICK_VALUE_1ms = 100,
    TIMER_DELAY10ms_TICK_VALUE_1ms = 10,
    TIMER_ADC_TERMO_10ms=10,
	TIMER_MAX_VALUE_1ms
} EnumTimerValues_ms;
#endif




/*****************************************************************************/
/**						EXPORTED VARIABLES									**/
/*****************************************************************************/
#ifndef _TIMER_C
	#define DECL extern
#else
	#define DECL
#endif

/*****************************************************************************/
/**						EXPORTED FUNCTIONS									**/
/*****************************************************************************/
/*****************************************************************************/
DECL void InterruptSysTick(void);
/*****************************************************************************/
/*
 * System Timer Hardware interruption
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */

/*****************************************************************************/
DECL ErrorStatus IniTimer(void);
/*****************************************************************************/
/*
 * This function initializes all hardware timers
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */


/*****************************************************************************/
DECL ErrorStatus InitAndResetSoftwareTimers(void);
/*****************************************************************************/
/*
 * This function initializes the defined software timers
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */


/*****************************************************************************/
DECL void StartSoftwareTimer(EnumTimer index, u32 val, EnumTimerBase base);
/*****************************************************************************/
/*
 * This function starts one software timer
 *
 * Parameters:	index		Index of the timer
 *				val			Value for the timer
 *				base		Time base of the timer
 *
 * Returns:		N/A
 */


/*****************************************************************************/
DECL ErrorStatus StopSoftwareTimer(EnumTimer index);
/*****************************************************************************/
/*
 * This function stops one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */


/*****************************************************************************/
DECL void PauseSoftwareTimer(EnumTimer index);
/*****************************************************************************/
/*
 * This function pauses one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */



/*****************************************************************************/
DECL void ContinueSoftwareTimer(EnumTimer index);
/*****************************************************************************/
/*
 * This function continues after pausing one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */


/*****************************************************************************/
DECL EnumTimerState GetTimer(EnumTimer index);
/*****************************************************************************/
/*
 * This function gets the state of one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		State of the timer
 */


/*****************************************************************************/
DECL bool GetTimerTicks(EnumTimer index, u32* ticks);
/*****************************************************************************/
/*
 * This function gets the current ticks of one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		Timer ticks
 */



#undef DECL
#endif

/*****************************************************************************/
/**						EOF													**/
/*****************************************************************************/


