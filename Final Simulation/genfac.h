/*
 * genfac.h
 *
 *  Created on: 16 Nov 2013
 *    Author: Shivam 2012CS10252
 */

#ifndef GENFAC_H_
#define GENFAC_H_
#include "global1.h"
#include "main_2.h"
/*! \file genfac.h
\brief Generates faculty nodes and assigns random interest to them
Details.
*/
//! A function taking two arguments and returning void. It assigns random interests to a faculty from the interests of his department.
/*!
 \param fc Faculty node
 \param department Department of the faculty
 \return Void

*/
void randominterest_fac(faculty* fc, dept* department);
//! A function taking three arguments and returning void. Generates faculty nodes
/*!
 \param seed Random Seed Integer 
 \param depart Department for which faculty are generated
 \param univ University for which faculty are generated
 \return Void

*/
void genfacof1dept(struct UNIV * univer , struct dept* depart, int seed);


#endif /* GENFAC_H_ */
