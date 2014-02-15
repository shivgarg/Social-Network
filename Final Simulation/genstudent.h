/*
 * genstudent.h
 *
 *  Created on: 16 Nov 2013
 *      Author: cs1120252
 */

#ifndef GENSTUDENT_H_
#define GENSTUDENT_H_

#include "global1.h"
#include "main_2.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <utility>
#include <vector>
#include <time.h>
#include <algorithm>
/*! \file genstudent.h
\brief Generates student nodes and assigns random interest to them.
Delete students after 4 years.
*/
//! A function taking two arguments and returning void. It assigns random interests to a student.
/*!
 \param st Student node
 \param department Department of the student
 \return Void

*/
void randominterest_st(student* st, dept* department);
//! A function taking five arguments and returning void. It generates student nodes.
/*!
 \param univer University of the student
 \param depart Department of the student
 \param seed   Student random seed
 \param batch  Current entry year for which students are being created
 \param stupy  Student per year that need to be generated 
 \return Void

*/
void genstuof1dept(float stupy ,struct UNIV * univer , struct dept* depart, int seed,int batch );
//! A function taking zero arguments and returning void. It increase the current year by one.
/*!
 \return Void

*/
void increase_year();
//! A function taking zero arguments and returning void. It kill the students after every four year.
/*!
 \return Void

*/
void kill();
//! A function taking zero arguments and returning void. It is called for cleanup at the end.
/*!
 \return Void
*/
void kill_all();
#endif /* GENSTUDENT_H_ */
