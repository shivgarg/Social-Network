/*
 * Generator.cpp
 *
 *  Created on: 26 Sep 2013
 *      Author: shivam
 */



using namespace std;
int r = 0;
int facRANDOM,studRANDOM,courseRANDOM,friendRANDOM;
int entryno = 1;

int numberofsems = 0;
int j = 0;
#include "global1.h"
#include "main_2.h"
vector<string> stud_name,stud_surname;
vector<string> prof_name,prof_surname;
vector<UNIV> universities;

int setEnviro(char * envfile)
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
	data= fopen(envfile,"rb");//argv[2],"rb");
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
            strcpy((d->deps), dep);
            d->number_of_sems_floated = 0;
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
            
			char t[90];
			fscanf(data,"%s",j->name);
			if(!allinterest[j->name])
			{
				allinterest[j->name] = j;
				fscanf(data,"%f",&(universities.back().depts[op].interests[(allinterest[j->name])]));
			}
			else
			{
				delete j;
			}
      	}
		else if(temp1=="RANDOMSEED")
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
            for(std::vector<course*>::iterator c=(*it).allcourses.begin();c!=(*it).allcourses.end();c++)
            {
                (*c)->dep = &((*it).depts[(*c)->deps]);
                if(strcmp(((*c)->deps),k->second.name)!=0)
                {
                    k->second.nondepcourses.push_back(*c);//   IMPORTANT
                }
                else
                {
                    k->second.depcourses.push_back(*c);
                }
            }
        }
    }
    /*-----------------------------*/
    return 0;
    
    }
