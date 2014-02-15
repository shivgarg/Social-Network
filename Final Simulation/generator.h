/*
 * generator.h
 *
 *  Created on: 9 Oct 2013
 *      Author: shivam
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <typeinfo>
#include <utility>
#include <sys/mman.h>
#include "graphml.h"
#include <queue>
#include <vector>
#include "genFriend.h"
#include "main_2.h"
#include "message_temp.h"
#include "genstudent.h"
#include "genCourse.h"
#include <stdlib.h>
#include <map>
#include "genfac.h"
#include "Semaphore.h"
/*! \file generator.h
\brief Calls all the generate functions
Details.
*/
//! A function taking one arguments and returning void *
/*!	It calls the generate faculty function and sends alarm request to timekeeper  */

/*!
 \param args given due to pthread_create.
 \return void * due to pthread.

*/

void * generateFaculty(void * args);


//! A function taking one arguments and returning void *
/*!	It calls the generate Students function and sends alarm request to timekeeper  */

/*!
 \param args given due to pthread_create.
 \return void * due to pthread.

*/


void * generateStudents(void * args);
//! A function taking one arguments and returning void *
/*!	It calls the generate courses function and sends alarm request to timekeeper  */

/*!
 \param args given due to pthread_create.
 \return void * due to pthread.

*/
void * generateCourses(void * args);
//! A function taking one arguments and returning void *
/*!	It calls the generate friends function and sends alarm request to timekeeper  */

/*!
 \param args given due to pthread_create.
 \return void * due to pthread.

*/
void * genFen(void * args );
//! A function taking one arguments and returning void *
/*!	It recieves message from timekeeper and signals the thread */
/*!
 \param args it takes parameter simulation run time.
 \return void * due to pthread.

*/
void *  readpp(void * args);


#endif /* GENERATOR_H_ */
