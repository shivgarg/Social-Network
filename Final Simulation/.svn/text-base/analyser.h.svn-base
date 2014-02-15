/*
 * analyser.h
 *
 *  Created on: 16 Nov 2013
 *      Author: cs1120252
 */

#ifndef ANALYSER_H_
#define ANALYSER_H_

#include <string>
#include <limits>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <map>
/*! \file analyser.h
\brief This file does analysis of graph
*/
using namespace std;



/** @struct studnode
 *  @brief This structure stores data of students*/
 /**  @var studnode::name 
 *  Member 'name' contains name of Student*/
 /**  @var  studnode::surname 
 *  Member 'surname' contains surname of student.*/
 /** 	@var	studnode::hostel
 * 	Member 'hostel' contains hostel assigned to the student.*/
 /** 	@var 	studnode::roomNo
 * 	Member 'roomNo' contains room no. in the hostel*/
 /** 	@var	studnode::entryno
 * 	Member 	'entryno' contains entry no of the student */
 /** 	@var	studnode::dept
 * 	Member 	'dept' contains Department of the student */
   /** 	@var	studnode::univ
 * 	Member 	'unic' contains University of of the student */
  /** 	@var	studnode::batch
 * 	Member 	'batch' contains batch of the student */
   /** 	@var	studnode::year
 * 	Member 	'year' contains the year of degree the student is pursuing*/
  /** 	@var	studnode::floor
 * 	Member 	'floor' contains entry no of the student */
  /** 	@var	studnode::interest
 * 	Member 	'interest' contains the interests of the student */
  /** 	@var	studnode::courses
 * 	Member 	'courses' contains courses of the student currently he/she is pursuing */
  /** 	@var	studnode::friends
 * 	Member 	'firends' contains friend list of the student */
 
  

struct studnode
{
	
	string name;
	string surname;
	string hostel,dept,univ;
	int batch,year,roomNo,entryno;
	char floor;
	vector<string> interests,courses;
	vector<int> friends;
};
/** @struct facnode
 *  @brief This structure stores data of Faculty*/
 /**  @var facnode::name 
 *  Member 'name' contains name of Faculty*/
 /**  @var  facnode::surname 
 *  Member 'surname' contains surname of Faculty.*/
 /** 	@var	facnode::hostel
 * 	Member 'hostel' contains house assigned to the Faculty.*/
 /** 	@var	facnode::entryno
 * 	Member 	'entryno' contains entry no(id) of the Faculty */
 /** 	@var	facnode::dept
 * 	Member 	'dept' contains Department of the Faculty */
   /** 	@var	facnode::univ
 * 	Member 	'univ' contains University of of the Faculty */
  /** 	@var	facnode::interests
 * 	Member 	'interests' contains the interests of the Faculty */
  /** 	@var	facnode::courses
 * 	Member 	'courses' contains courses of the Faculty currently he/she is taking */
  struct facnode
{
	string name;
	string surname;
	string entryno,hostel,dept,univ;
	int roomNo;
	vector<string> interests,courses;
	
};
//! A function taking two arguments and returning int *
/*!	It prints shortest path between id1 and id2 using Djikstra's algorithm.    */

/*!
 \param id1 Id of first student
 \param id2 Id of second student
 \return int

*/

int shortpath(int id1,int id2);

//! A function taking no arguments and returning int *
/*!	It implements Floyd-Warshall  */

/*!
 \return int

*/

int floyd();
//! A function taking two arguments and returning void *
/*!	It prints shortest path between id1 and id2 using floyd's algorithm.    */

/*!
 \param i Id of first student
 \param j Id of second student
 \return void

*/

void shortest_path(int i,int j);
//! A function taking two arguments and returning void *
/*!	It prints a single but shortest path between id1 and id2    */

/*!
 \param i Id of first student
 \param j Id of second student
 \return void

*/

void list_short_path(int i,int j);
//! A function taking one arguments and returning int *
/*!	It returns the importance of student*/

/*!
 \param i Id of student
 \return int

*/

int importance(int i);
//! A function taking one arguments and returning void *
/*!	It prints the number and list of friends who are more important than the given student*/

/*!
 \param i Id of student
 \return void

*/
void moreimp(int i);
//! A function taking no arguments and returning void *
/*!	It prints the largest of all shortest paths in the graph*/

/*!
 \return void

*/

void largestshortestpath();
//! A function taking two arguments and returning bool *
/*!	It tells whether i and j are friends or not */

/*!
 \param i Id of first friend.
 \param j Id of second friend.
 \return bool

*/

bool checkfriends(int i,int j);
//! A function taking one arguments and returning void *
/*!	It finds the largest possible clique of the given person and print the members of the clique  */

/*!
 \param i Id of student
 \return void 

*/

void clique(int i);

#endif /* ANALYSER_H_ */
