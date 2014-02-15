/*
 * global1.h
 *
 *  Created on: 8 Oct 2013
 *      Author: shivam
 */

#ifndef GLOBAL1_H_
#define GLOBAL1_H_


extern "C"
 {
    #include <pthread.h>
    #include <unistd.h>
 }
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <map>
#include <utility>

#include "Semaphore.h"
#include <cstdlib>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;
/*! \file global1.h
\brief Contains all the structs, classes and global variables used all over the simulation
*/
//! Vector containing names and surnames of students .
/*!
Used in random assignment of names to students
*/
extern vector<string> stud_name,stud_surname;

//! Mutexes .
/*!
To lock various symbols
*/
extern pthread_mutex_t facMutex,StudMutex,CourseMutex,FriendMutex,courseaffac,courseafStud,friAfAll;

//! Conditional variables .
/*!
For pausing threads 
*/
extern pthread_cond_t facCond,StudCond,CourseCond,FriendCond,condcoraffac,condcorafStud,friAf;

//! Random seed for faculty,student,course and friend .
/*!
Same as the ones in input file.
*/
extern int facRANDOM,studRANDOM,courseRANDOM,friendRANDOM,p;

//!
/*!
These are used as variables to check whether thread is to be run or not.
*/
extern int runThdStud,runThdCourse,runThdFriend,alloafgen,runThdfac,alloafStud;

//!  
/*!
These are keys used to open message queues.
*/
extern key_t gentotime,timetogen;

//! Id's of students and faculty .
/*!
Both faculty and students are given their Id's sequentially
*/
extern int entryno, facultyid,numberofsems;
extern vector<string> stud_name,stud_surname;

//! Vector containing names and surnames of faculty .
/*!
Used in random assignment of names to faculty.
*/
extern vector<string> prof_name,prof_surname;
struct dept;
struct UNIV;
struct student;
struct faculty;

/** @struct interest
 *  @brief This structure stores all the data of intersets*/
 /**    @var interest::name 
 *  Member 'name' contains name of interest*/
 /**    @var interest::interest_stud 
 *  Member 'interest_stud' contains list of students with that interest.*/
 /** 	@var interest::interest_fac
 * 	Member 'interest_fac' contains list of faculty with that interest.*/
 
struct interest
{
    char name[90];
    vector<student*> interest_stud;
    vector<faculty*> interest_fac;
};

/** @struct hostels
 *  @brief This structure stores all the data of hostels*/
 /**    @var hostels::name 
 *  Member 'name' contains name of hostel.*/
 /**    @var hostels::we
 *  Member 'we' denotes floor.*/
 /** 	@var hostels::hostel_stud
 * 	Member 'hostel_stud' contains list of students living in that hostel.*/

struct hostels
{
    char name[30];
    int we[4];
    vector<student*> hostel_stud;
};

/** @struct houses
 *  @brief This structure stores all the data of faculty houses*/
 /**    @var houses::name 
 *  Member 'name' contains name of house*/
 /**    @var houses::fill 
 *  Member 'fill' denotes no. of faculty in this house locality.*/
 /** 	@var houses::house_fac
 * 	Member 'house_fac' contains list of faculty with that house locality.*/
 
struct houses
{
    char name[30];
    int fill;
    vector<faculty*> house_fac;
};

 /** @struct course
 *  @brief This structure stores all the data of course nodes*/
 /**  	@var course::freq
 *  Member 'freq' contains frequency with which course needs to be floated*/
 /**  	@var course::name 
 *  Member 'name' denotes name of the course.*/
 /** 	@var course:: number_of_sem_floated
 * 	Member 'number_of_sem_floated' gives no. of sems this course is floated.*/
 /** 	@var course:: deps
 * 	Member 'deps' gives the name of department of that course.*/
  /** 	@var course:: unis
 * 	Member 'unis' gives the name of university of this course.*/
  /** 	@var course:: dep
 * 	Member 'dep' gives the department node.*/
  /** 	@var course:: couse_stud
 * 	Member 'course_stud' stores all the students registered in the course .*/ 
  /** 	@var course:: floated
 * 	Member 'floated' denoting whether course is floated or not.*/
  /** 	@var course:: instructor
 * 	Member 'instructor' gives the faculty node of prof taking that course.*/
 
struct course
{
	float freq;
	char name[20];
    int number_of_sems_floated;
    char deps[20];
    char unis[100];
    dept* dep;
    vector<student*> course_stud;
    bool floated;
    faculty* instructor;
};

 /** @struct student
 *  @brief This structure stores all the data of student nodes*/
 /**  	@var student::Entry_No
 *  Member 'Entry_No' gives the id of the student*/
 /**  	@var student::Year 
 *  Member 'Year' denotes year of entry.*/
 /** 	@var student:: Batch
 * 	Member 'Batch' gives the current year.*/
 /** 	@var student:: name
 * 	Member 'name' gives the name of that student.*/
  /** 	@var student:: surname
 * 	Member 'surname' gives the surname of that student.*/
  /** 	@var student:: dep
 * 	Member 'dep' gives the department node.*/
   /** 	@var student:: uni
 * 	Member 'uni' gives the university node.*/
  /** 	@var student:: host
 * 	Member 'host' gives the hostel of te student .*/ 
  /** 	@var student:: floor
 * 	Member 'floor' gives the floor number.*/
  /** 	@var student:: room_no
 * 	Member 'room_no' gives the room number.*/
   /** 	@var student:: location_in_allstudents
 * 	Member 'location_in_allstudents' gives the index where this student is placed in the all_students vector.*/
  /** 	@var student:: intrst
 * 	Member 'intrst' gives the interests of that student.*/
  /** 	@var student:: sem_dep_courses_taken
 * 	Member 'sem_dep_courses_taken' gives the department courses the student is registered in.*/
  /** 	@var student:: sem_non_dep_courses_taken
 * 	Member 'sem_non_dep_courses_taken' gives the other department courses the student is registered in.*/
  /** 	@var student:: friends
 * 	Member 'friends' gives all the friends of that student.*/
 
struct student
{
    int Entry_No;
    int Year;
    int Batch;
    char* name;// char
    char* surname;
    dept* dep;
    UNIV* uni;
    hostels* host;
    string floor;
    int room_no;
    unsigned long location_in_allstudents;
    vector<interest*> intrst;
    vector<course*> sem_dep_courses_taken;// to be added
    vector<course*> sem_non_dep_courses_taken;// to be added
    vector<student*> friends;
};


 /** @struct faculty
 *  @brief This structure stores all the data of faculty nodes*/
 /**  	@var faculty::employee_code
 *  Member 'employee_code' gives the id of the faculty*/
 /** 	@var faculty:: name
 * 	Member 'name' gives the name of that faculty.*/
  /** 	@var faculty:: surname
 * 	Member 'surname' gives the surname of that faculty.*/
  /** 	@var faculty:: department
 * 	Member 'department' gives the department node of that faculty.*/
   /** 	@var faculty:: uni
 * 	Member 'uni' gives the university node of that faculty.*/
  /** 	@var faculty:: house
 * 	Member 'house' gives the house loaclity of that faculty .*/ 
  /** 	@var faculty:: plotno
 * 	Member 'plotno' gives the plot number on which faculty lives.*/
  /** 	@var faculty:: room_no
 * 	Member 'room_no' gives the room number.*/
   /** 	@var faculty:: intrst
 * 	Member 'intrst' gives the interests of that faculty.*/
  /** 	@var faculty:: set_of_interest
 * 	Member 'set_of_interest' is a mapping of name of the interest with node of that interest .*/
  /** 	@var faculty:: courses_taken
 * 	Member 'courses_taken' gives the courses taken by the faculty.*/
 
struct faculty 
{
    int employee_code;
    char* name;// char
    char* surname;
    dept* department;
    UNIV* uni;
    houses* house;
    int plotno;
    vector<interest*> intrst;
    map<string,float> set_of_interests;
    vector<course*> courses_taken;
};


 /** @struct dept
 *  @brief This structure stores all the data of department nodes*/
 /** 	@var dept:: name
 * 	Member 'name' gives the name of that department.*/
  /** 	@var dept:: numfac
 * 	Member 'numfac' gives the number of faculty in that department.*/
  /** 	@var dept:: studperyr
 * 	Member 'studperyr' gives the students that enter in the department per year.*/
   /** 	@var dept:: semdeptcourse
 * 	Member 'semdeptcourse' gives the credits a student needs to do in his department.*/
   /** 	@var dept:: semnondeptcourse
 * 	Member 'semnondeptcourse' gives the credits a student needs to do in courses of other department.*/
  /** 	@var dept:: depcourses
 * 	Member 'depcourses' gives all the courses in that department .*/ 
  /** 	@var dept:: fac
 * 	Member 'fac' gives all the faculty nodes in that departmnt.*/
  /** 	@var dept:: dep_stud
 * 	Member 'dep_stud' gives all the student nodes in that department.*/
   /** 	@var dept:: interests
 * 	Member 'interests' gives the interests in that department.*/

 
struct dept
{
	char name[10];
	float numfac,studperyr,semdeptcourse,semnondeptcourses;
	vector<course*> depcourses;
    vector<course*> nondepcourses;
    vector<faculty*> fac;
    vector<student*> dep_stud;
	map<interest*,float> interests;
};
 
/** @struct UNIV
 *  @brief This structure stores all the data of university nodes*/
 /** 	@var UNIV:: name
 * 	Member 'name' gives the name of that university.*/
  /** 	@var UNIV:: hostel
 * 	Member 'hostel' gives all the hostels in that university.*/
  /** 	@var UNIV:: hostel_struct
 * 	Member 'hostel_struct' is a mapping from name of the hostel to hostel node.*/
   /** 	@var UNIV:: houselocality
 * 	Member 'houselocality' gives all the faculty houses in that university.*/
   /** 	@var UNIV:: house_struct
 * 	Member 'house_struct' is a mapping from name of the house to house node.*/
   /** 	@var UNIV:: depts
 * 	Member 'depts' is the mapping of department name to the department node.*/
  /** 	@var UNIV:: allcourses
 * 	Member 'allcourses' gives all the courses that department .*/ 
  /** 	@var UNIV:: interest1
 * 	Member 'interest1' is a mapping of name of the interest with node of that interest .*/

struct UNIV{
	char name[100];
    vector<string> hostel;
	map<string,hostels> hostel_struct;
	vector<string> houselocality;
    map<string,houses> house_struct;
	float friendshiprate,open,friendliness;
	map<string,dept> depts;
    vector<course*> allcourses;
    map<string,float> interest1;

};

//! Vector containing all the university nodes .
extern vector<UNIV> universities;
//! Vector containing all the faculty nodes.
extern vector<faculty*> allfaculty;
//! Vector containing all the student nodes.
/*!
This vector gets updated after every kill and generate.
*/
extern vector<student*> allstudents;
//! Vector containing all the interest 
/*!
Interests are globbal across universities.
*/
extern map<string,interest*> allinterest;


//! A graph class.
/*!
class description.
*/

class graph{
	private:

	public:
		//! number of vertices variable.
		/*!
		would be same as no. of students
		*/
		int numvertices;
		//! number of edges variable.
		/*!
		 gives estimate of no. of friends
		*/		
		int numedges;
		bool** graphmatrix;
		//! A constructor.
		/*!
		*/
		graph(int i);
		//! A constructor.
		/*!
		*/
		~graph();
		//! A normal member taking two arguments and returning a void value.
		/*!
		\param v1 first student.
		\param v2 second student.
		Adds student 1 to friendlist of 2 and vice-versa 
		\return void
		*/
		void create_edge(student* v1, student* v2);
		//! A normal member taking two arguments and returning a void value.
		/*!
		\param v1 first student.
		\param v2 second student.
		Removes student v1 to friendlist of v2 and vice-versa 
		\return void
		*/
		void del_edge(student* v1,student* v2);
		//! A normal member taking one argument and returning an int value.
		/*!
		\param v1 a student.
		Gives no. of friends of student v1 
		\return void
		*/
		int no_of_friends(student* v1);
		//! A normal member taking one argument and returning an int array.
		/*!
		\param v1 a student.
		Gives all the friends of student v1 
		\return void
		*/
		int* list_of_friends(student* v2);
		//! A normal member taking two arguments and returning a bool value.
		/*!
		\param v1 a student.
		\param v2 a student.
		Checks whether the two people are already friends or not. 
		\return void
		*/
		bool already_friends(student* v1, student* v2);

};

extern graph *g;


#endif /* GLOBAL1_H_ */
