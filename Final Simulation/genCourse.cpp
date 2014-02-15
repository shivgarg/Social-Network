#include "genCourse.h"
#include "global1.h"
void floatCourses(int course_random)
{
   pthread_mutex_lock(&courseaffac);
    	if(!alloafgen)
    	{
    		pthread_cond_wait(&condcoraffac,&courseaffac);
    	}
    	pthread_mutex_unlock(&courseaffac);


	for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
        for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            std::vector<faculty*>::iterator fc = k->second.fac.begin();
            for(std::vector<faculty*>::iterator fc = k->second.fac.begin();fc!=(k->second.fac).end();fc++)
            {
              //  cout<<"DEP"<<(*fc)->department->name<<" NAME "<<(*fc)->name<<endl;
            }
            
            for(std::vector<course*>::iterator st=(k->second.depcourses).begin();st!=(k->second.depcourses).end();st++)
            {   
                (*st)->floated = false;
                float r;
                if(numberofsems == 0)
                {
                    r =  2*(((float) rand() / (RAND_MAX)));
                   // cout<<"RAM"<<r<<endl;
                    
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
pthread_mutex_lock(&courseafStud);
    	if(!alloafStud)
    	{
    		pthread_cond_wait(&condcorafStud,&courseafStud);
    	}
    	alloafStud=0;
    	pthread_mutex_unlock(&courseafStud);

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
      /*      for(std::vector<student*>::iterator st=(k->second.dep_stud).begin();st!=(k->second.dep_stud).end();st++)
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
