#include "genstudent.h"

string floor1[]= {"A","B","C","D"};


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
            st->intrst.push_back(hos->first);
            allinterest[hos->first->name]->interest_stud.push_back(st);
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
        st->floor = floor1[st->Batch%4];                             //floor
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
			//cout << " *****1 Dept : " << k->second.name << " | Strength : " << k->second.dep_stud.size()<< endl;
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
          //  cout << " *****2 Dept : " << k->second.name << " | Strength : " << k->second.dep_stud.size()<< endl;
            
		}
        if(b != 0)
        {
			for(std::vector<string>::iterator hos=(*it).hostel.begin();hos!=(*it).hostel.end();hos++)
			{
			//	cout << " !!!!!3 HOS : " << (*it).hostel_struct[*hos].name << " | Strength : " << (*it).hostel_struct[*hos].hostel_stud.size()<< endl;
            	
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
			//	cout << " !!!!!4 HOS : " << (*it).hostel_struct[*hos].name << " | Strength : " << (*it).hostel_struct[*hos].hostel_stud.size()<< endl; 
          }

	}
       for(std::vector<course*>::iterator c=(*it).allcourses.begin(); c!=(*it).allcourses.end(); c++)
	   {
		  // cout << " &&&&&5 co : " <<(*c)->name << " | Strength : " << (*c)->course_stud.size()<< endl;
            for(std::vector<student*>::iterator st = ((*c)->course_stud).begin(); st != ((*c)->course_stud).end(); st++)
            {
                if( ((*st)->Year) == 5)
                {
                    std::vector<student*>::iterator temp1 = st;
                    (*c)->course_stud.erase(st);
                    st = --temp1;
                }
            }
            	//	   cout << " &&&&&6 co : " <<(*c)->name << " | Strength : " << (*c)->course_stud.size()<< endl;
		}
   }
       for(std::map<string,interest*>::iterator ty=allinterest.begin(); ty != allinterest.end(); ty++)
       {
		   //	cout << " @@@@@7 int : " << ty->second->name << " | Strength : " << (ty->second->interest_stud).size()<< endl;
            for(std::vector<student*>::iterator st = (ty->second->interest_stud).begin(); st != (ty->second->interest_stud).end(); st++)
            {
                if( ((*st)->Year) == 5)
                {
                    std::vector<student*>::iterator temp1 = st;
                    (ty->second->interest_stud).erase(st);
                    st = --temp1;
                }
            }
          //  cout << " @@@@@8 int : " << ty->second->name << " | Strength : " << (ty->second->interest_stud).size()<< endl;
            
		}
    
    //kill from hostel  done
    //kill from interest done
    //kill from courses done
    
    //IMPORTANT
    //kill from friends list or graph CHIRAG check!!!!

            
    for(std::vector<student*>::iterator stu = allstudents.begin(); stu != allstudents.end(); stu++)
    {
		//cout << " ^^^^^^9 fr : " << (*stu)->name << " | Strength : " << (*stu)->friends.size()<< endl;
		//cout << "The person k" << " Entry : " << (*stu)->Entry_No << " Batch" << (*stu)->Batch<<endl;        
        for(std::vector<student*>::iterator fr = (*stu)->friends.begin(); fr != (*stu)->friends.end(); fr++)
        {
		//	cout << "The person k" << (*fr)->name << " Entry : " << (*fr)->Entry_No << " Batch" << (*fr)->Batch<<endl;    
            if( ((*fr)->Year) == 5)
            {
				std::vector<student*>::iterator temp1 = fr;
                (*stu)->friends.erase(fr);
                fr = --temp1;
             //   cout << "killed"<<endl; 
            }

        }
        	//	cout << " ^^^^^^10 fr : " << (*stu)->name << " | Strength : " << (*stu)->friends.size()<< endl;
    }
    //cout << " total Strength : " << allstudents.size()<< endl;

    for(std::vector<student*>::iterator stu = allstudents.begin(); stu != allstudents.end(); stu++)
    {
	
        if((*stu)->Year == 5)
        {
            free (*stu);
            std::vector<student*>::iterator temp = stu;
            allstudents.erase(stu);
            stu = --temp;
        }
    }
    
   // cout << " total Strength : " << allstudents.size()<< endl;
}

void kill_all()
{
    delete (g);

    for(std::vector<UNIV>::iterator uni = universities.begin(); uni != universities.end(); uni++)
    { 
        
        (*uni).depts.clear();
        (*uni).hostel.clear();
        (*uni).hostel_struct.clear();
        (*uni).houselocality.clear();
        (*uni).house_struct.clear();
        for(std::vector<course*>::iterator c=(*uni).allcourses.begin(); c!=(*uni).allcourses.end(); c++)
        {
         delete (*c);
        }
        (*uni).allcourses.clear();
    }
    universities.clear();
    for(std::map<string,interest*>::iterator ty=allinterest.begin(); ty != allinterest.end(); ty++)
    {
        delete (ty->second);
    }
    allinterest.clear();
    for(std::vector<student*>::iterator stu = allstudents.begin(); stu != allstudents.end(); stu++)
    {    
        delete (*stu);
    }
    allstudents.clear();
    for(std::vector<faculty*>::iterator fac = allfaculty.begin(); fac != allfaculty.end(); fac++)
    {    
        delete (*fac);
    }
    allfaculty.clear();
}
