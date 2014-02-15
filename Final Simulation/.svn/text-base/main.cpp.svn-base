/*
 * Generator.cpp
 *
 *  Created on: 26 Sep 2013
 *      Author: shivam
 */


extern "C"
{
#include <pthread.h>
#include <unistd.h>
}
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include "global1.h"
#include "graphml.h"
#include "graph.h"
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;
int r = 0;
int facRANDOM,studRANDOM,courseRANDOM,friendRANDOM;
int entryno = 1;
int emplcode = 1;
int numberofsems = 0;
int j = 0;
vector<faculty*>allfaculty;
vector<student*>allstudents;
map<string,interest*> allinterest;
time_t a;
vector<string> stud_name,stud_surname;
vector<string> prof_name,prof_surname;
vector<UNIV> universities;
string floors[] = {"A","B","C","D"};




/*--------------------------------------------FACULTY----------------------------------------------------------------*/
void randominterest_fac(faculty* fc, dept* department)
{
    for(std::map<interest*,float>::iterator hos=department->interests.begin();hos!=department->interests.end();hos++)
    {
        int p = false;
        double q = ((double) rand() / (RAND_MAX));
        if(q<=hos->second)
        {
            p = true;
        }
        if(p)
        {
            allinterest[hos->first->name]->interest_fac.push_back(fc);
            fc->intrst.push_back(allinterest[hos->first->name]);
            fc->set_of_interests[hos->first->name] = hos->second;
        }
    }
    
}


   void genfacof1dept(struct UNIV * univer, struct dept* depart, int seed)
    {
        srand(seed);
        for(unsigned int i = 0; i < depart->numfac; i++)
        {
            
            faculty* fc = new faculty;
            fc->employee_code = i + emplcode;
             string fname= "qwerty";
            
            fc->name = (char *)prof_name[rand()%prof_name.size()].c_str();      //random name
            fc->surname =(char *)prof_surname[rand()%prof_surname.size()].c_str();  //random surname
            fc->uni = univer;
            fc->department =  depart;
            
            string house = univer->houselocality[rand()%(univer->houselocality.size())];   //random hostel
            fc->house = &(univer->house_struct[house]);
            int k = fc->house->fill;
            k++;
            fc->house->fill = k;
            fc->plotno = k;                                            //plot no.
            
            allfaculty.push_back(fc);
            fc->house->house_fac.push_back(fc);
            depart->fac.push_back(fc);
            randominterest_fac(fc, depart);                                 //interest
        }
        emplcode = emplcode + depart->numfac;
        
    }

void generateFaculty()
{
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            
            genfacof1dept(&*it, &k->second, facRANDOM);
		}
	}
}







/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------STUDENT------------------------------------------------------------*/


 void randominterest_st(student* st, dept* department)
{
    for(std::map<interest*,float>::iterator hos=department->interests.begin();hos!=department->interests.end();hos++)
    {
        int p = false;
        double q = ((double) rand() / (RAND_MAX));
        if(q<=hos->second)
        {
            p = true;
        }
        if(p)
        {
            allinterest[hos->first->name]->interest_stud.push_back(st);
            st->intrst.push_back(allinterest[hos->first->name]);
        }
    }
}

void genstuof1dept(float stupy,struct UNIV * univer, struct dept* depart, int seed, int batch)
{
    unsigned long total =  allstudents.size();
    srand(seed);
    int year = 1;
    for(unsigned int i = 0; i < depart->studperyr; i++)
    {
        
        student* st = new student;
        st->Entry_No = i + entryno;
        st->Batch = batch;
        st->name = (char *)stud_name[rand()%stud_name.size()].c_str();      //random name
        st->surname =(char *)stud_surname[rand()%stud_surname.size()].c_str();  //random surname
        st->uni = univer;
        st->dep =  depart;
        
        string hstl = univer->hostel[rand()%(univer->hostel.size())];   //random hostel
        st->host = &(univer->hostel_struct[hstl]);
        st->floor = floors[st->Batch%4];                             //floor
        int k = st->host->we[st->Batch%4];
        k++;
        st->host->we[st->Batch%4] = k;
        st->room_no = k;                                            //room no.
        
        st->Year = year;
        allstudents.push_back(st);
        st->host->hostel_stud.push_back(st);        
        depart->dep_stud.push_back(st);
        randominterest_st(st, depart);                                 //interest
        
    }
    entryno = entryno + depart->studperyr;
    
}
void increase_year()
{
    for(unsigned long i = 0; i < allstudents.size(); i++)
    {
        allstudents[i]->Year += 1;
    }
}
void kill()
{
    int b = 0;
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
        for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            for(std::vector<student*>::iterator st = (k->second.dep_stud).begin(); st != (k->second.dep_stud).end(); st++)
            {
                if( ((*st)->Year) == 5)
                {
                    b = (*st)->Batch;
                    std::vector<student*>::iterator temp1 = st;
                    k->second.dep_stud.erase(st);
                    st = --temp1;
                }
            }
		}
        if(b != 0)
        {
           for(std::vector<string>::iterator hos=(*it).hostel.begin();hos!=(*it).hostel.end();hos++)
          {
             (*it).hostel_struct[*hos].we[b%4]=0;
              
              for(std::vector<student*>::iterator st = ((*it).hostel_struct[*hos]).hostel_stud.begin(); st != ((*it).hostel_struct[*hos]).hostel_stud.end(); st++)
              {
                  if( ((*st)->Year) == 5)
                  {
                      std::vector<student*>::iterator temp1 = st;
                      (*it).hostel_struct[*hos].hostel_stud.erase(st);
                      st = --temp1;
                  }
              }
 
          }
       }
       for(std::map<string,interest*>::iterator ty=allinterest.begin(); ty != allinterest.end(); ty++)
       {
            for(std::vector<student*>::iterator st = (ty->second->interest_stud).begin(); st != (ty->second->interest_stud).end(); st++)
            {
                if( ((*st)->Year) == 5)
                {
                    std::vector<student*>::iterator temp1 = st;
                    (ty->second->interest_stud).erase(st);
                    st = --temp1;
                }
            }
		}
    }
    //kill from hostel  done
    //kill from interest done
    //kill from courses
    
    //IMPORTANT
    //kill from friends list or graph CHIRAG

    for(std::vector<student*>::iterator stu = allstudents.begin(); stu != allstudents.end(); stu++)
    {
        for(std::vector<student*>::iterator fr = (*stu)->friends.begin(); fr != (*stu)->friends.end(); fr++)
        {
            if( ((*fr)->Year) == 5)
            {
                std::vector<student*>::iterator temp1 = fr;
                (*stu)->friends.erase(fr);
                fr = --temp1;
            }

        }
        if((*stu)->Year == 5)
        {
            delete (*stu);
            std::vector<student*>::iterator temp = stu;
            allstudents.erase(stu);
            stu = --temp;
        }
    }
}

int Y = 2012;
void generateStudents()
{
    increase_year();
    
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            genstuof1dept(k->second.studperyr, &*it, &k->second,studRANDOM, Y); //year dhang se dena
		}
	}
    ++Y;
    kill();
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------COURSES-------------------------------------------------------------*/
void floatCourses(int course_random)
{
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
        for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            std::vector<faculty*>::iterator fc = k->second.fac.begin();
            /*for(std::vector<faculty*>::iterator fc = k->second.fac.begin();fc!=(k->second.fac).end();fc++)
            {
                cout<<"DEP"<<(*fc)->department->name<<" NAME "<<(*fc)->name<<endl;
            }*/
            
            for(std::vector<course*>::iterator st=(k->second.depcourses).begin();st!=(k->second.depcourses).end();st++)
            {   
                (*st)->floated = false;
                float r;
                if(numberofsems == 0)
                {
                    r =  2*(((float) rand() / (RAND_MAX)));
                  //  cout<<"RAM"<<r<<endl;
                }
                else
                {
                    //cout << " number "<< (*st)->number_of_sems_floated <<" hg s"<<numberofsems<<endl;
                    r =  (2*( (float) ( (float)((*st)->number_of_sems_floated) /(float)numberofsems) ));
                    //cout<<r<<endl;
                }
                if(r <= ((*st)->freq))
                {
                    // srand(course_random);
                    (*st)->floated = true;
                    (*st)->instructor = *fc;
                    (*fc)->courses_taken.push_back(*st);
                    (*st)->number_of_sems_floated += 1;
                    if(fc != k->second.fac.end()-1)
                    {
                        fc++;
                    }
                    else
                    {
                        fc = k->second.fac.begin();
                    }
                }
               // cout<<r<<" FLOATED "<<(bool)((*st)->floated)<<"   "<<"FREQ:: "<<(*st)->freq<<" "<<(*st)->name<<" "<<(*fc)->name<<" NO:: "<<(*st)->number_of_sems_floated<<" TOTAL::  "<<numberofsems+1<<endl;
            }
        }
    }
    numberofsems++;
}
void allocateCourses(int course_random)
{
    srand(course_random);
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
        for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            for(std::vector<student*>::iterator st=(k->second.dep_stud).begin();st!=(k->second.dep_stud).end();st++)
            {
                (*st)->sem_dep_courses_taken.clear();
                (*st)->sem_non_dep_courses_taken.clear();
                int total_dc = k->second.depcourses.size();
                int dc_taken = (int)(k->second.semdeptcourse);//min
                double dc = ((double) rand() / (RAND_MAX))+(int)(k->second.semdeptcourse);
                //cout<<dc<<endl;
                if(dc <= (k->second.semdeptcourse) )
                {
                    dc_taken += 1;
                }
                for(int i = 0; i < dc_taken; i++)
                {
                  course *c =  (k->second.depcourses[rand()%total_dc]);
                    if(c->floated == true)
                    {
                        c->course_stud.push_back(*st);
                        (*st)->sem_dep_courses_taken.push_back(c);
                    }
                    else
                    {
                        if(i < 0)
                        {
                            i = -1;
                        }
                        else
                        {
                            i--;
                        }
                    }
                }
                
                int total_ndc = k->second.nondepcourses.size();
                int ndc_taken = (int)(k->second.semnondeptcourses);//min
                double ndc = ((double) rand() / (RAND_MAX))+(int)(k->second.semnondeptcourses);
                if(ndc <= (k->second.semnondeptcourses) )
                {
                    ndc_taken += 1;
                }
                for(int i = 0; i < ndc_taken; i++)
                {
                    course *c =  (k->second.nondepcourses[rand()%total_ndc]);
                    if(c->floated == true)
                    {
                        c->course_stud.push_back(*st);
                        (*st)->sem_non_dep_courses_taken.push_back(c);
                    }
                    else
                    {
                        if(i < 0)
                        {
                            i = -1;
                        }
                        else
                        {
                            i--;
                        }
                        
                    }
                }
            }
            /*for(std::vector<student*>::iterator st=(k->second.dep_stud).begin();st!=(k->second.dep_stud).end();st++)
            {
                cout<<(*st)->Entry_No<<" "<<(*st)->name<<endl;
                cout<<"DEP"<<endl;
                for(std::vector<course*>::iterator stc=(*st)->sem_dep_courses_taken.begin();stc!=(*st)->sem_dep_courses_taken.end();stc++)
                {
                    cout<<(*stc)->name<<endl;
                }
                cout<<"NONDEP"<<endl;
                for(std::vector<course*>::iterator stc=(*st)->sem_non_dep_courses_taken.begin();stc!=(*st)->sem_non_dep_courses_taken.end();stc++)
                {
                    cout<<(*stc)->name<<endl;
                }
            }*/
            
        }
    }
    
}
void generateCourses()
{
   floatCourses(courseRANDOM);
   allocateCourses(courseRANDOM);
}

/*--------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------GRAPHS-------------------------------------------------------*/

graph::graph(int o){
	int y= 0;
	numvertices = o;
	graphmatrix = new bool*[o];
	for(y = 0; y < o; y++){
		graphmatrix[y] = new bool[o];
	}
}

graph::~graph(){
	for (int j = 0; j < numvertices; j++)
		delete[] graphmatrix[j];
	delete[] graphmatrix;
}

void graph::create_edge(student* v1, student* v2){
	v1->friends.push_back(v2);
	v2->friends.push_back(v1);
	//graphmatrix[v1][v2] = true;
	//graphmatrix[v2][v1] = true;0
	numedges++;
}

void graph::del_edge(student* v1, student* v2){
	for(int u = 0; u < v1->friends.size();u++){
		if(v1->friends.at(u) == v2){
			v1->friends.erase(v1->friends.begin() + u);
		}
	}
	//graphmatrix[v1][v2] = false;
	//graphmatrix[v2][v1] = false;
	numedges--;
}

int graph::no_of_friends(student* v1){
	int ans = v1->friends.size();
	return ans;
}

bool graph::already_friends(student *v1, student *v2){
	bool arefriends = false;
	for(std::vector<student*>::iterator k = v1->friends.begin() ; k < v1->friends.end() ; k++){
		if((*k) == v2){
			arefriends =true;
		}
	}
	return arefriends;
}

//int* graph::list_of_friends(int v1){
//	int size = no_of_friends(v1);
//	int* list;
//	list = new int[size];
//	int temp = 0;
//	for (int u = 0; u < numvertices; u++) {
//		if (graphmatrix[v1][u]){
//			list[temp] = u;
//			temp++;
//		}
//	}
//	return list;
//}

graph *g = new graph(allstudents.size());

void generateFriends(vector<UNIV> *universities){
	int y = 0;
	int z = 0;
	srand(friendRANDOM);
	friendRANDOM += 2;
	friendRANDOM = friendRANDOM%150;
	//for(vector<UNIV>::iterator k = (*universities).begin(); k != (*universities).end();k++){
    int i = allstudents.size();
    int rperson = rand()%i;
    int u;
    int v;
    student* randomperson = allstudents.at(rperson);
    while(randomperson->intrst.size() == 0)
    {
        rperson = rand()%i;
        randomperson = allstudents.at(rperson);
    }
    int rprob = rand()%100;
    //cout << "hello " << endl;
    
    if(rprob < (randomperson->uni->open)*100)
    {
        int anranperson = rand() % i;
        while (rperson == anranperson)
        {
            anranperson = rand() % i;
        }
        student* arandomperson = allstudents.at(anranperson);
        if(!(g->already_friends(randomperson,arandomperson)))
        {
            bool intrstmatch = false;
            for (u = 0; u < randomperson->intrst.size(); u++)
            {
                for (v = 0; v < arandomperson->intrst.size(); v++)
                {
                    if (!strcmp(arandomperson->intrst.at(v)->name,randomperson->intrst.at(u)->name))
                    {
                        intrstmatch = true;
                        y = v;
                        break;
                    }
                }
            }
           // cout<<"check"<<endl;
            
            bool coursematch = false;
            int q;
            int ty = 0;
            bool sem = false;
      //      cout << "ok" << endl;
            for (u = 0; u < randomperson->sem_dep_courses_taken.size();u++)
            {//cout << "chal ja bhai" << endl;
                for (v = 0; v < arandomperson->sem_dep_courses_taken.size();v++)
                {//cout << arandomperson->sem_dep_courses_taken.size() << "this is it " << endl;
                    if (!strcmp(randomperson->sem_dep_courses_taken.at(u)->name,arandomperson->sem_dep_courses_taken.at(v)->name))
                    {
                        coursematch = true;
                        ty = u;
                        sem = true;
               //         cout << "i m in" << endl;
                        break;
                    }
                }
                //cout << "i m out" << endl;
                
                for (q = 0;q < arandomperson->sem_non_dep_courses_taken.size();q++)
                {//cout << arandomperson->sem_dep_courses_taken.size() << "this is not it " << endl;
                    if (!strcmp(randomperson->sem_dep_courses_taken.at(u)->name,arandomperson->sem_non_dep_courses_taken.at(q)->name))
                    {//cout << " i m in in 2" << endl;
                        coursematch = true;
                        ty = u;
                        sem = true;
                        break;
                    }
                }
            }
            //cout << coursematch << " " << intrstmatch << endl;
            
            for (u = 0; u < randomperson->sem_non_dep_courses_taken.size();u++)
            {
                for (v = 0; v < arandomperson->sem_dep_courses_taken.size();
                     v++) {
                    if (!strcmp(randomperson->sem_non_dep_courses_taken.at(u)->name,arandomperson->sem_dep_courses_taken.at(v)->name))
                    {
                        coursematch = true;
                        sem = false;
                        ty = u;
                        break;
                    }
                }
                for (q = 0;q < arandomperson->sem_non_dep_courses_taken.size();q++)
                {
                    if (!strcmp(randomperson->sem_non_dep_courses_taken.at(u)->name,arandomperson->sem_non_dep_courses_taken.at(q)->name))
                    {
                        coursematch = true;
                        sem = false;
                        ty = u;
                        break;
                    }
                }
            }
            
            //cout << intrstmatch << endl;
            if (!strcmp(arandomperson->dep->name, randomperson->dep->name) || !strcmp(arandomperson->host->name,randomperson->host->name) || intrstmatch|| coursematch)
            {
                
                // send request
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to random person" << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                if (!strcmp(arandomperson->dep->name,
							randomperson->dep->name)) {
                    cout << "Share common department" << endl;
                }
                if (intrstmatch) {
                    cout << "Share common interest of "
                    << arandomperson->intrst.at(y)->name << endl;
                }
                if (coursematch && sem) {
                    cout << "Share common course : "
                    << randomperson->sem_dep_courses_taken.at(ty)->name
                    << endl;
                }
                if (coursematch && !sem) {
                    cout << "Share common course : "
                    << randomperson->sem_non_dep_courses_taken.at(ty)->name << endl;
                }
                if (!strcmp(arandomperson->host->name,
							randomperson->host->name)) {
                    cout << "Share common neighborhood" << endl;
                }
                //				else {
                //					x = 3;
                //					cout << "Share common course" << endl;
                //				}
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
                
            }

            // if not returned till now then friend request to send with out_probablity
            else {
                
                // send request
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to random person" << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                cout << "No commanalities" << endl;
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
                
            }
		}
       // cout<<"check45"<<endl;
        
	}
    
    else{
        
        int op0 = (randomperson->uni->open)*100;
        int op =  100 - (randomperson->uni->open)*100;
        float op1 = op/4;
        if(rprob >=  op0 && rprob < (op0 + op1)){
            int l = randomperson->dep->dep_stud.size();
            int anranperson = rand()%l;
            student* arandomperson = randomperson->dep->dep_stud.at(
                                                                    anranperson);
            if(!(g->already_friends(randomperson,arandomperson))){
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to person belonging to same dept"
                << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
            }
        }
        else if(rprob >=  (op0 +op1) && rprob < (op0 + op1 +op1)){
            int l = randomperson->host->hostel_stud.size();
            int aranperson= rand()%l;
            student* arandomperson = randomperson->host->hostel_stud.at(
                                                                        aranperson);
            if(!(g->already_friends(randomperson,arandomperson))){
                cout
                << "____________________________________________________"
                << endl;
                cout
                << "Request sent to person belonging to same hostel :: "
                << randomperson->host->name << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
            }
        }
        else if(rprob >= (op0 + op1 + op1) && rprob < (op0 +op1 +op1 +op1)){
            int q = rand()%(randomperson->intrst.size());
            int l = allinterest[randomperson->intrst[q]->name]->interest_stud.size();
            int aranperson = rand()%l;
            student* arandomperson = randomperson->intrst.at(q)->interest_stud.at(
                                                                                  aranperson);
            if(!(g->already_friends(randomperson,arandomperson))){
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to person having same interest of "
                << randomperson->intrst.at(q)->name << endl;
                
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
            }
        }
        else {
            student* arandomperson;
            int temp = rand()%100;
            if(temp < 50){
				int q = rand()%(randomperson->sem_dep_courses_taken.size());
				int l = randomperson->sem_dep_courses_taken.at(q)->course_stud.size();
				int aranperson = rand()%l;
				arandomperson =
                randomperson->sem_dep_courses_taken.at(q)->course_stud.at(aranperson);
				if(!(g->already_friends(randomperson,arandomperson)))
                {
                    cout
                    << "____________________________________________________"
                    << endl;
                    cout << "Request sent to person having same course of "
                    << randomperson->sem_dep_courses_taken.at(q)->name
                    << endl;
				}
            }
            else {
                int q = rand()
                % (randomperson->sem_non_dep_courses_taken.size());
                int l = randomperson->sem_non_dep_courses_taken.at(q)->course_stud.size();
                int aranperson = rand() % l;
                arandomperson =
                randomperson->sem_non_dep_courses_taken.at(q)->course_stud.at(
                                                                              aranperson);
                if(!(g->already_friends(randomperson,arandomperson)))
                {
                    cout
                    << "____________________________________________________"
                    << endl;
                    cout << "Request sent to person having same course of "
                    << randomperson->sem_non_dep_courses_taken[q]->name
                    << endl;
                }
            }
            if(!(g->already_friends(randomperson,arandomperson)))
            {
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                int raccept = rand() % 100;
                if (raccept < arandomperson->uni->friendliness * 100)
                {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    cout << ": accepted" << endl;
                } else
                    cout << ": rejected" << endl;
                
			}
        }
    }
	//}
}



/*--------------------------------------------------------------------------------------------------------------------*/

int main()
{
    FILE * names;
    names=fopen("Indian_Names.txt","rb");
    while(!feof(names))
    {
        char temp[20];
        fscanf(names,"%s",temp);
        stud_name.push_back(temp);
    }
    fclose(names);
    
    names=fopen("Indian_Surnames.txt","rb");
    while(!feof(names))
    {
        char temp[20];
        fscanf(names,"%s",temp);
        stud_surname.push_back(temp);
    }
    fclose(names);
    names=fopen("Prof_Names.txt","rb");
    while(!feof(names))
    {
        char temp[20];
        fscanf(names,"%s",temp);
        prof_name.push_back(temp);
    }
    fclose(names);
    
    names=fopen("Prof_Surnames.txt","rb");
    while(!feof(names))
    {
        char temp[20];
        fscanf(names,"%s",temp);
        prof_surname.push_back(temp);
    }
    fclose(names);
    
	int num_days= 365;// atoi(argv[1]);
	FILE * data;
	data= fopen("SocialNetworkEnv.inp","rb");//argv[2],"rb");
    string op = "";
	while(!feof(data))
	{
		char temp[80];
		fscanf(data,"%s",temp);
		string temp1(temp);
		if(temp1=="UNIVERSITY")
		{	UNIV a;
			fscanf(data,"%s",a.name);
			universities.push_back(a);
            
		}
		else if(temp1=="DEPARTMENT")
		{
			dept a;
			fscanf(data,"%s",a.name);
			fscanf(data,"%f %f %f %f",&a.numfac,&a.studperyr,&a.semdeptcourse,&a.semnondeptcourses);
            op = a.name;
			universities.back().depts[a.name]=a;
            
		}
		else if(temp1=="HOSTEL")
		{
            hostels h;
			fscanf(data,"%s",h.name);
			universities.back().hostel_struct[h.name] = h;
            universities.back().hostel.push_back(h.name);
            
		}
		else if(temp1=="COURSE")
		{
			course *d = new course;
			char dep[10];// = new char[];
            fscanf(data,"%s",d->name);
			fscanf(data,"%s",dep);
			fscanf(data,"%f",&(d->freq));
           // d->unis = (universities.back().name);
            strcpy((d->deps), dep);
            d->number_of_sems_floated = 0;
         //   cout<<d.name<<d.deps<<endl;
            universities.back().allcourses.push_back(d);
            
		}
		else if(temp1=="HOUSELOCALITY")
		{
            houses h;
			fscanf(data,"%s",h.name);
			universities.back().house_struct[h.name] = h;
            universities.back().houselocality.push_back(h.name);
		}
		else if(temp1=="FRIENDSHIPRATE")
		{
			fscanf(data,"%f",&(universities.back().friendshiprate));
		}
		else if(temp1=="OPENNESS")
		{
			fscanf(data,"%f",&(universities.back().open));
		}
		else if(temp1=="FRIENDLINESS")
		{
			fscanf(data,"%f",&(universities.back().friendliness));
		}
		else if(temp1=="INTEREST")
		{
            interest* j = new interest;
            //interest* i;
            
			char t[90];
			fscanf(data,"%s",j->name);
            allinterest[j->name] = j;
            float h;
      		fscanf(data,"%f",&h);
            universities.back().depts[op].interests[(allinterest[j->name])] = h;
      	}
		else if(temp1=="RANDOMSEED")//temp1
		{
			fscanf(data,"%d %d %d %d", &facRANDOM,&studRANDOM,&courseRANDOM,&friendRANDOM);
		}
	}
    
    
    
    /*-----------------------------*/
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		for(std::vector<string>::iterator hos=(*it).hostel.begin();hos!=(*it).hostel.end();hos++)
		{
            (*it).hostel_struct[*hos].we[0] = 0;
            (*it).hostel_struct[*hos].we[1] = 0;
            (*it).hostel_struct[*hos].we[2] = 0;
            (*it).hostel_struct[*hos].we[3] = 0;
		}
        for(std::vector<string>::iterator hos=(*it).houselocality.begin();hos!=(*it).houselocality.end();hos++)
		{
            (*it).house_struct[*hos].fill = 0;
        }
        for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            //cout<<(*it).name<<" "<<k->second.name<<endl;
           for(std::vector<course*>::iterator st=(k->second.depcourses).begin();st!=(k->second.depcourses).end();st++)
            {
                //cout<<(*st)->name<<" "<<(*st)->dep->name<<endl;
                
            }
            cout<<(*it).name<<k->second.name<<endl;
            for(std::vector<course*>::iterator c=(*it).allcourses.begin();c!=(*it).allcourses.end();c++)
            {
               //cout<<(*c)->name<<" "<<(*c)->deps<<" "<<(*c)->freq<<endl;
                (*c)->dep = &((*it).depts[(*c)->deps]);
                if(strcmp(((*c)->deps),k->second.name)!=0)
                {
                    cout<<"NONDEP"<<(*c)->name<<" token  "<<k->second.nondepcourses.size()<<endl;
                    k->second.nondepcourses.push_back(*c);//   IMPORTANT
                }
                else
                {
                                        cout<<"DEP"<<(*c)->name<<" token2  "<<k->second.depcourses.size()<<endl;
            //        cout<<"DEP"<<(*c).dep->name<<"  "<<k->second.name<<endl;
                    k->second.depcourses.push_back(*c);
                }
                
                
            }
        }
    }
	generateFaculty();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    generateStudents();
    for(int i = 0; i <= 5; i++)
    {
        generateCourses();
        //cout<<i<<endl;
        
    }
   // generateCourses();
   // generateCourses();
   // generateCourses();
   // generateCourses();
    /*-----------------------------*/
    
    
   // cout<<"RUN"<<endl;
    for(std::map<string,interest*>::iterator in=allinterest.begin(); in!=allinterest.end(); in++)
    {
        //cout<<"allinterest "<<" :: "<<(in->second)->name<<(in->second->interest_stud.size())<<endl;
        //cout<<"FACULTY"<<endl;
        for(std::vector<faculty*>::iterator st=(in->second->interest_fac).begin();st!=(in->second->interest_fac).end();st++)
        {
            //cout<<(*st)->employee_code<<" "<<(*st)->name<<endl;
        }
        //cout<<"student"<<endl;
        for(std::vector<student*>::iterator st=(in->second->interest_stud).begin();st!=(in->second->interest_stud).end();st++)
        {
          //cout<<(*st)->Entry_No<<" "<<(*st)->name<<endl;
        }
    }
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		//cout << (*it).name<< endl;
		//cout<<"allinterest"<<allinterest.size()<<endl;
        int o = 0;
        for(std::map<string,interest*>::iterator in=allinterest.begin(); in!=allinterest.end(); in++)
		{
            o++;
          //  cout<<"allinterest "<<o<<" :: "<<(in->second)->name<<endl;
        }
        for(std::map<string,float>::iterator in=(*it).interest1.begin(); in!=(*it).interest1.end(); in++)
		{
            //cout<<(*it).name<<in->first<<(in->second)<<endl;
            // cout<<o<<" :: "<<(in->second)->name<<endl;
        }
		for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
           //cout << k->first<<"  name  "<< k->second.name<< endl;
           // cout << "no of fac"<<k->second.numfac<< " "<<" courses " <<k->second.semdeptcourse<<" non courses "<<k->second.semnondeptcourses<<" dep_stud pryr "<<k->second.studperyr<< endl;
           // for(std::map<interest*,float>::iterator hos=(k->second).interests.begin();hos!=(k->second).interests.end();hos++)
            {
             //   cout << "INT"<<hos->first->name<<" :: "<<(hos->second)<<endl;
            }
           // genstuof1dept(k->second.studperyr, &*it, &k->second, 5, 2012,1);
            for(std::vector<faculty*>::iterator st=(k->second.fac).begin();st!=(k->second.fac).end();st++)
            {
                //cout<<" Department :: "<<(*st)->department->name<<" EmployeeCode :: "<<(*st)->employee_code<<" Name :: "<<(*st)->name<<" "<<(*st)->surname<<" House :: "<<(*st)->house->name<<" Plot :: "<<(*st)->plotno<<endl;
                
                for(std::vector<interest*>::iterator in=((*st)->intrst).begin();in!=((*st)->intrst).end();in++)
                {
                 //   cout<<(*in)->name<<endl;
                //  cout<<++j<<(*st)->name<<" "<<(*st)->employee_code<<(*st)->department->name<<endl;
                }
            }
            //cout<<k->second.name<<endl;
            for(std::vector<course*>::iterator c=k->second.depcourses.begin();c!=k->second.depcourses.end();c++)
            {
                //cout<<"ALLAH"<<(*c)->name<<" "<<(*c)->deps<<" "<<(*c)->freq<<endl;
                
            }
          //  cout<<"student"<<endl;
            for(std::vector<student*>::iterator st=(k->second.dep_stud).begin();st!=(k->second.dep_stud).end();st++)
            {
            //    cout<<(*st)->Entry_No<<" "<<(*st)->name<<" "<<(*st)->surname<<endl;
                for(std::vector<interest*>::iterator in=((*st)->intrst).begin();in!=((*st)->intrst).end();in++)
                {
              //      cout<<" "<<(*in)->name<<(*in)->interest_stud.size()<<endl;
                    //cout<<++j<<(*st)->name<<" "<<(*st)->employee_code<<(*st)->department->name<<endl;
                }
            }
		}
        for(std::vector<course*>::iterator c=(*it).allcourses.begin();c!=(*it).allcourses.end();c++)
        {
      //      cout<<(*c)->name<<" "<<(*c)->dep->name<<" "<<(*c)->freq<<endl;
                        
        }
        
	}
    int io = 1;
    for(std::map<string,interest*>::iterator in=allinterest.begin(); in!=allinterest.end(); in++)
    {
        //cout<<io<<" allinterest "<<" :: "<<(in->second)->name<<endl;
        io++;
        //cout<<"BEGIN"<<endl;
        int j = 0;
        for(std::vector<student*>::iterator st=(in->second->interest_stud).begin();st!=(in->second->interest_stud).end();st++)
        {
            //  cout<<++j<<(*st)->name<<" "<<(*st)->Batch<<(*st)->dep->name<<(*st)->Entry_No<<endl;
        }
        for(std::vector<faculty*>::iterator st=(in->second->interest_fac).begin();st!=(in->second->interest_fac).end();st++)
        {
            //  cout<<++j<<(*st)->name<<" "<<(*st)->employee_code<<(*st)->department->name<<endl;
        }
        //cout<<"END"<<endl;
    }

    
    for(unsigned long i = 0; i < allstudents.size(); i++) //print
    {
               //cout<<"Entry No. :: "<<allstudents[i]->Batch<<allstudents[i]->dep->name<<allstudents[i]->Entry_No<<" Year :: "<<allstudents[i]->Year<<" NAME :: "<<allstudents[i]->name<<" "<<allstudents[i]->surname<<" Department :: "<<allstudents[i]->dep->name<<" University :: "<<allstudents[i]->uni->name<<" Hostel :: "<<allstudents[i]->host->name<<" Room :: "<<allstudents[i]->floor<<allstudents[i]->room_no<<endl;
    }
    for(unsigned long i = 0; i < allfaculty.size(); i++) //print
    {
     //  cout<<allfaculty[i]->uni->name<<" Department :: "<<allfaculty[i]->department->name<<" EmployeeCode :: "<<allfaculty[i]->employee_code<<" Name :: "<<allfaculty[i]->name<<" "<<allfaculty[i]->surname<<" House :: "<<allfaculty[i]->house->name<<" Plot :: "<<allfaculty[i]->plotno<<endl;
        //      cout<<"Entry No. :: "<<allstudents[i]->Batch<<allstudents[i]->dep->name<<allstudents[i]->Entry_No<<" Year :: "<<allstudents[i]->Year<<" NAME :: "<<allstudents[i]->name<<" "<<allstudents[i]->surname<<" Department :: "<<allstudents[i]->dep->name<<" University :: "<<allstudents[i]->uni->name<<" Hostel :: "<<allstudents[i]->host->name<<" Room :: "<<allstudents[i]->floor<<allstudents[i]->room_no<<endl;
    }
//kill();
    int uv =0;
    while(uv < 15000){
        
        generateFriends(&universities);
        uv++;
    }
    
   graphconverter();//check edges.
    return 0;
}
