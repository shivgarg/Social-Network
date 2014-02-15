/*
 * Semaphore.h
 *
 *  Created on: 16 Nov 2013
 *      Author: cs1120252
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/*! \file Semaphore.h
\brief A Documented file.
Details.
*/
//! A function taking two arguments and returning an integer value.
/*!
 \param t Used to generate a semaphore.
 \param s Number of semaphores in a semaphore array.
 \return id of the semaphore

*/
int open_sem( key_t t, int s );
//! A function taking one argument and having void return type.
/*!
\param  a semaphore id
	acquire lock over the semaphore by decreasing semaphore value.

\return void

*/

void getSem(int a);
//! A function taking one argument and having void return type.
/*!
\param d release lock over the semaphore by increasing semaphore value.

\return void

*/
void relSem(int d);


#endif /* SEMAPHORE_H_ */
