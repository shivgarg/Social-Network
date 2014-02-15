/*
 * TimeKeeper.h
 *
 *  Created on: 17 Nov 2013
 *      Author: cs1120252
 */

#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_



#include <pthread.h>
#include <unistd.h>

#include <iostream>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "generator.h"
#include <typeinfo>
#include <utility>
#include <sys/mman.h>


#include <queue>
#include "graphml.h"
#include <vector>

/*! A comparator class for prioirty queue to schedule tasks*/
class pq_operand
{
public:
	 //! Comparater taking two pair of ints and returning a bool value.
/*!
	\param n1 : A pointer to pair of integers
	\param n2: A pointer to pair of integers
	\return Bool
*/
    bool operator()(pair<int,int> &n1,pair<int,int> &n2)
    {

      if(n1.second<n2.second)
      return false;
      else if(n1.second==n2.second)
      {
    	  if(n1.first<n2.first)
    	  {
    		  return false;
    	  }
    	  else
    		  return true;
      }
      else
      return true;

    }
};

#endif /* TIMEKEEPER_H_ */
