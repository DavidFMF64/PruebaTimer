/*
 * soft_timer.c
 *
 *  Created on: 28/5/2019
 *      Author: David
 */




/****************************** C SOURCE FILE ********************************
** Project	: AX00															**
** Filename	: TIMER.C														**
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

#define _TIMER_C

/*****************************************************************************/
/**						MODULES USED										**/
/*****************************************************************************/

#include "soft_timer.h"


/*****************************************************************************/
/**						DEFINITIONS AND MACROS								**/
/*****************************************************************************/


/*****************************************************************************/
/**						TYPEDEFS AND STRUCTURES								**/
/*****************************************************************************/
typedef struct
{
	u32 duration;
	u32 counter;
	EnumTimerBase timeBase;
	EnumTimerState currentState;
} TypeTimer;


/*****************************************************************************/
/**						PROTOTYPES OF LOCAL FUNCTIONS						**/
/*****************************************************************************/


/*****************************************************************************/
/**						LOCAL VARIABLES										**/
/*****************************************************************************/
static TypeTimer softTimer[TIMER_MAX];

/*****************************************************************************/
/**						EXPORTED FUNCTIONS									**/
/*****************************************************************************/
/*****************************************************************************/
void InterruptSysTick(void)
/*****************************************************************************/
/*
 * Hardware timer interruption
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */
{
	u8 index;
	bool decTimer;

	// Update software timers
	for (index = 0; index < TIMER_MAX; index++)
	{
		// Checks if the timer is runnig
		if (softTimer[index].currentState != TIMER_STATE_RUNNING) { continue; }

		decTimer = FALSE;
		softTimer[index].counter++;
		switch (softTimer[index].timeBase)
		{
			case TIMER_BASE_1ms:
				if (softTimer[index].counter >= TICS_PER_MILISECOND) { decTimer = TRUE; }
				break;
			case TIMER_BASE_1s:
				if (softTimer[index].counter >= TICS_PER_SECOND) { decTimer = TRUE; }
				break;
			case TIMER_BASE_1min:
				if (softTimer[index].counter >= TICS_PER_MINUTE) { decTimer = TRUE; }
				break;
			case TIMER_BASE_1hour:
				if (softTimer[index].counter >= TICS_PER_HOUR) { decTimer = TRUE; }
				break;
			default:
				decTimer = TRUE;
				break;
		}
		if (decTimer == FALSE) { continue; }

		softTimer[index].counter = 0;
		softTimer[index].duration--;
		if (softTimer[index].duration == 0)	{ softTimer[index].currentState = TIMER_STATE_FLAGGED; }
	}
}



/*****************************************************************************/
ErrorStatus InitAndResetSoftwareTimers(void)
/*****************************************************************************/
/*
 * This function initializes the defined software timers
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */
{
	u8 index;
	ErrorStatus retValue = SUCCESS;

	// Bucle for all timers declared in Timer.h
	for (index = 0; index < TIMER_MAX; index++)
	{
		// Timer duration
		softTimer[index].duration = 0;
		// Timer counter
		softTimer[index].counter = 0;
		// Timer State
		softTimer[index].currentState = TIMER_STATE_STOPPED;
	}

	return (retValue);
}


/*****************************************************************************/
void StartSoftwareTimer(EnumTimer index, u32 val, EnumTimerBase base)
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
{
	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) { return; }
	if (val == 0) { return; }
	if (base >= TIMER_BASE_MAX) { return; }

	// The timmer is stopped before programming the new values for the software timer
	softTimer[index].currentState = TIMER_STATE_STOPPED;
	// Base of time
	softTimer[index].timeBase = base;
	// Timer duration
	softTimer[index].duration = val;
	// Timer current counter
	softTimer[index].counter = 0;
	// Timer State
	softTimer[index].currentState = TIMER_STATE_RUNNING;
}


/*****************************************************************************/
ErrorStatus StopSoftwareTimer(EnumTimer index)
/*****************************************************************************/
/*
 * This function stops one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */
{
	ErrorStatus retValue = SUCCESS;

	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) { return(ERROR); }

	// Timer duration
	softTimer[index].duration = 0;
	// Timer counter
	softTimer[index].counter = 0;
	// Timer State
	softTimer[index].currentState = TIMER_STATE_STOPPED;

	return (retValue);
}


/*****************************************************************************/
void PauseSoftwareTimer(EnumTimer index)
/*****************************************************************************/
/*
 * This function pauses one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */
{
	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) { return; }

	// Timer State
	softTimer[index].currentState = TIMER_STATE_PAUSED;
}


/*****************************************************************************/
void ContinueSoftwareTimer(EnumTimer index)
/*****************************************************************************/
/*
 * This function continues after pausing one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		N/A
 */
{
	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) { return; }

	// Timer State
	if (softTimer[index].duration > 0)	{ softTimer[index].currentState = TIMER_STATE_RUNNING; }
	else								{ softTimer[index].currentState = TIMER_STATE_FLAGGED; }
}

/*****************************************************************************/
EnumTimerState GetTimer(EnumTimer index)
/*****************************************************************************/
/*
 * This function gets the state of one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		State of the timer
 */
{
	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) return TIMER_STATE_STOPPED;

	return softTimer[index].currentState;
}



/*****************************************************************************/
bool GetTimerTicks(EnumTimer index, u32* ticks)
/*****************************************************************************/
/*
 * This function gets the current ticks of one software timer
 *
 * Parameters:	index		Index of the timer
 *
 * Returns:		Timer ticks
 */
{
	// Comprova les variables d'entrada
	if (index >= TIMER_MAX) { return(FALSE); }
	else
	{
		if(GetTimer(index) != TIMER_STATE_STOPPED)
		{
			(*ticks) = softTimer[index].duration;
			return(TRUE);
		}
		else { return(FALSE); }
	}
}


/*****************************************************************************/
ErrorStatus IniTimer(void)
/*****************************************************************************/
/*
 * This function initializes all hardware timers
 *
 * Parameters:	None
 *
 * Returns:		N/A
 */
{
	ErrorStatus retValue = SUCCESS;

	// Starts the hardware timer
	if (InitAndResetSoftwareTimers() == ERROR)  { retValue = ERROR; }

	return (retValue);
}



/*****************************************************************************/
/**						EOF													**/
/*****************************************************************************/
