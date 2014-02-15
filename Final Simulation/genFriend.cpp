#include "genFriend.h"
#include "global1.h"
#include "Semaphore.h"
graph *g = new graph(allstudents.size());
unsigned int iDisplay;
std::default_random_engine engine(friendRANDOM);
std::uniform_int_distribution<int>distribution(1);

int genFriends(void * args){
	int y = 0;
	int z = 0;
	int ra = 0;
	
	int ac = 0;
	int i = allstudents.size();
    int rperson = distribution(engine)%i;
    int raccept = distribution(engine) % 100;
    int u;
    int v;
    student* randomperson = allstudents.at(rperson);
    student* arandomperson;
    while(randomperson->intrst.size() == 0)
    {
        rperson = distribution(engine)%i;
        randomperson = allstudents.at(rperson);
    }
    int rprob = distribution(engine)%100;
    
    if(rprob < (randomperson->uni->open)*100)
    { ra = 0;// random
        int anranperson = distribution(engine) % i;
        while (rperson == anranperson)
        {
            anranperson = distribution(engine) % i;
        }
        arandomperson = allstudents.at(anranperson);
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
            
            bool coursematch = false;
            int q;
            int ty = 0;
            bool sem = false;
            for (u = 0; u < randomperson->sem_dep_courses_taken.size();u++)
            {   for (v = 0; v < arandomperson->sem_dep_courses_taken.size();v++)
                {   if (!strcmp(randomperson->sem_dep_courses_taken.at(u)->name,arandomperson->sem_dep_courses_taken.at(v)->name))
                    {
                        coursematch = true;
                        ty = u;
                        sem = true;
                        break;
                    }
                }
                
                for (q = 0;q < arandomperson->sem_non_dep_courses_taken.size();q++)
                {   if (!strcmp(randomperson->sem_dep_courses_taken.at(u)->name,arandomperson->sem_non_dep_courses_taken.at(q)->name))
                    {   coursematch = true;
                        ty = u;
                        sem = true;
                        break;
                    }
                }
            }
            
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
            
            if (!strcmp(arandomperson->dep->name, randomperson->dep->name) || !strcmp(arandomperson->host->name,randomperson->host->name) || intrstmatch|| coursematch)
            {
                
                // send request
              getSem(p);
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to random person" << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                cout << rperson << " " << anranperson << endl;
                relSem(p);
                if (!strcmp(arandomperson->dep->name,
							randomperson->dep->name)) {
                    getSem(p);
                    cout << "Share common department" << endl;
                    relSem(p);
                }
                if (intrstmatch) {
					getSem(p);
                    cout << "Share common interest of "
                    << arandomperson->intrst.at(y)->name << endl;
                    relSem(p);
                }
                if (coursematch && sem) {
                  getSem(p);
                    cout << "Share common course : "
                    << randomperson->sem_dep_courses_taken.at(ty)->name
                    << endl;
                    relSem(p);
                }
                if (coursematch && !sem) {
                    getSem(p);
                    cout << "Share common course : "
                    << randomperson->sem_non_dep_courses_taken.at(ty)->name << endl;
                    relSem(p);
                }
                if (!strcmp(arandomperson->host->name,
							randomperson->host->name)) {
                    getSem(p);
                    cout << "Share common neighborhood" << endl;
                    relSem(p);
                }
                
                if (raccept < arandomperson->uni->friendliness * 100) {
					// accept request
                    g->create_edge(arandomperson, randomperson);
                    getSem(p);cout << ": accepted" << endl;relSem(p);
                } else
                   { getSem(p);cout << ": rejected" << endl;relSem(p);}
                
            }

            // if not returned till now then friend request to send with out_probablity
            else {
                
                // send request
                getSem(p);
                cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to random person" << endl;
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                cout << rperson << " " << anranperson << endl;
                
                cout << "No commanalities" << endl;
                relSem(p);
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    getSem(p);cout << ": accepted" << endl;relSem(p);
                } else
                   { getSem(p);cout << ": rejected" << endl;relSem(p);}
                
            }
		}
        
	}
    
    else{
       
        int op0 = (randomperson->uni->open)*100;
        int op =  100 - (randomperson->uni->open)*100;
        float op1 = op/4;
        if(rprob >=  op0 && rprob < (op0 + op1)){
			
			ra = 1; // common dep
            int l = randomperson->dep->dep_stud.size();
            if(l <= 1){
				goto label1;
			}
            int anranperson =distribution(engine)%l;
            arandomperson = randomperson->dep->dep_stud.at(anranperson);
            
            while (randomperson == arandomperson)
        {
            anranperson = distribution(engine) % l;
            arandomperson = randomperson->dep->dep_stud.at(anranperson);
            
        }
            if(!(g->already_friends(randomperson,arandomperson))){
              getSem(p);
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
                cout << rperson << " " << anranperson << endl;
                relSem(p);
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                  getSem(p);  cout << ": accepted" << endl;relSem(p);
                } else
						{getSem(p);cout << ": rejected" << endl;relSem(p);}
            }
        }
        else if(rprob >=  (op0 +op1) && rprob < (op0 + op1 +op1)){
		
			
			ra = 2; // common hos
			int l = randomperson->host->hostel_stud.size();
			if(l <= 1){
				goto label1;
			}
            int aranperson= distribution(engine)%l;
            arandomperson = randomperson->host->hostel_stud.at(aranperson);
    
            while (randomperson == arandomperson)
        {

            aranperson = distribution(engine) % l;
            arandomperson = randomperson->host->hostel_stud.at(aranperson);
            
        }

			
            if(!(g->already_friends(randomperson,arandomperson))){
               getSem(p);
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
                cout << rperson << " " << aranperson << endl;
                relSem(p);
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                    getSem(p);cout << ": accepted" << endl;relSem(p);
                } else
                    {getSem(p);cout << ": rejected" << endl;relSem(p);}
            }
        }
        else if(rprob >= (op0 + op1 + op1) && rprob < (op0 +op1 +op1 +op1)){
			
			ra = 3;//common intrest
            int q = distribution(engine)%(randomperson->intrst.size());
            
            int l = allinterest[randomperson->intrst[q]->name]->interest_stud.size();
            if(l <= 1){
				goto label1;
			}
          
            int aranperson = distribution(engine)%l;
            arandomperson = allinterest[randomperson->intrst[q]->name]->interest_stud.at(aranperson);
            
            while (randomperson == arandomperson)
        {
            aranperson = distribution(engine) % l;
            arandomperson = allinterest[randomperson->intrst[q]->name]->interest_stud.at(aranperson);
            
        }
          getSem(p);  cout<<"friends selected a  person   same  "<<(*arandomperson).name<< endl;relSem(p);
           
            if(!(g->already_friends(randomperson,arandomperson))){
             getSem(p);   cout
                << "____________________________________________________"
                << endl;
                cout << "Request sent to person having same interest of "
                << randomperson->intrst.at(q)->name << endl;
                
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                cout << rperson << " " << aranperson << endl;
                relSem(p);
                if (raccept < arandomperson->uni->friendliness * 100) {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                  getSem(p);  cout << ": accepted" << endl;relSem(p);
                } else
                    {getSem(p);cout << ": rejected" << endl;relSem(p);}
            }
        }
        else {
		
			
			int aranperson ;
	
            ra=4;//common course
            int temp = distribution(engine)%100;
            if(temp < 50){

				int q = distribution(engine)%(randomperson->sem_dep_courses_taken.size());
				
				int l = randomperson->sem_dep_courses_taken.at(q)->course_stud.size();
				if(l <= 1){
					goto label1;
				}
			    aranperson = distribution(engine)%l;
			    arandomperson = randomperson->sem_dep_courses_taken.at(q)->course_stud.at(aranperson);
				while (randomperson == arandomperson)
        {
            aranperson = distribution(engine) % l;
            arandomperson = randomperson->sem_dep_courses_taken.at(q)->course_stud.at(aranperson);
        }
                 getSem(p);cout<<"friends selected a  person same dept course    "<<(*arandomperson).name<< endl;relSem(p);
				if(!(g->already_friends(randomperson,arandomperson)))
                {getSem(p);
                    cout
                    << "____________________________________________________"
                    << endl;
                    cout << "Request sent to person having same course of "
                    << randomperson->sem_dep_courses_taken.at(q)->name
                    << endl;relSem(p);
				}
            }
            else {
              getSem(p);  cout << randomperson->sem_non_dep_courses_taken.size()<< endl;relSem(p);
                if(randomperson->sem_non_dep_courses_taken.size()==0)
                {
					goto label1;
				}
                int q = distribution(engine)% (randomperson->sem_non_dep_courses_taken.size());
               getSem(p); cout << randomperson->sem_non_dep_courses_taken.size()<< endl;relSem(p);
                int l = randomperson->sem_non_dep_courses_taken.at(q)->course_stud.size();
                if (l <= 1){
					goto label1;
				}
               getSem(p); cout<< l<< endl;	    relSem(p);
                aranperson = distribution(engine)%l;
			    arandomperson = randomperson->sem_non_dep_courses_taken.at(q)->course_stud.at(aranperson);
		
				while (randomperson == arandomperson)
        {
            aranperson = distribution(engine) % l;
            arandomperson = randomperson->sem_non_dep_courses_taken.at(q)->course_stud.at(aranperson);
        }
                if(!(g->already_friends(randomperson,arandomperson)))
                {getSem(p);
                    cout
                    << "____________________________________________________"
                    << endl;
                    cout << "Request sent to person having same course of "
                    << randomperson->sem_non_dep_courses_taken[q]->name
                    << endl;relSem(p);
                }
            }
            if(!(g->already_friends(randomperson,arandomperson)))
            {getSem(p);
                cout << randomperson->name << "(" << randomperson->uni->name
                << "," << randomperson->dep->name
                << ") sends request to " << arandomperson->name
                << "(" << arandomperson->uni->name << ","
                << arandomperson->dep->name << ")" << endl;
                cout << rperson << " " << aranperson << endl;
                relSem(p);
                if (raccept < arandomperson->uni->friendliness * 100)
                {
                    // accept request
                    g->create_edge(arandomperson, randomperson);
                  getSem(p); cout << ": accepted" << endl;relSem(p);
                } else
                 {getSem(p);   cout << ": rejected" << endl;relSem(p);}
                
			}
        }
           }
          label1:
    float dr = randomperson->uni->friendshiprate*pow(2.713,-(*(static_cast<int *>(args))*randomperson->uni->friendshiprate));
    return (int)dr;

	
}
