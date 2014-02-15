
#include "genfac.h"
int emplcode = 1;
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
            fc->intrst.push_back(hos->first);
            allinterest[hos->first->name]->interest_fac.push_back(fc);
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

