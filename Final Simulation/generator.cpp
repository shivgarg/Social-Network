/*
 * generator.cpp
 *
 *  Created on: 9 Oct 2013
 *      Author: shivam
 */
 
#include "generator.h"
#include "global1.h"
int curr_time;
key_t gentotime,timetogen;
int msgtimtogen,msggentotim,fromStud,fromCourse;
pthread_mutex_t timeconvey,courseaffac,courseafStud;
using namespace std;
int runThdStud=0,runThdCourse=0,runThdFriend=0,alloafgen=0,runThdfac=0,alloafStud=0;
vector<faculty*>allfaculty;
vector<student*>allstudents;
map<string,interest*> allinterest;
pthread_cond_t condcoraffac,condcorafStud;
pthread_mutex_t facMutex,StudMutex,CourseMutex,FriendMutex,AllocMutex;
pthread_cond_t facCond,StudCond,CourseCond,FriendCond,AllocAfGen;
void * generateFaculty(void * args)
{	
	mymsgbuf opl;
	(opl).mtype=1;
	(opl).thdid=1;
	while(true)
	{
			pthread_mutex_lock(&facMutex);
			
	if(!runThdfac)
			{	pthread_cond_wait(&facCond,&facMutex);
			}
			runThdfac=0;
			pthread_mutex_unlock(&facMutex);
		getSem(p);
		cout << "generating faculty"<< endl;
			relSem(p);
    for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
			
            genfacof1dept(&*it, &k->second, facRANDOM);
		}
	}

	/*for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
	{
		for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
		{
            cout<<"DEP"<<k->second.name<<endl;
           for(std::vector<faculty*>:: iterator hj=k->second.fac.begin();hj!=k->second.fac.end();hj++)
           {
        	   cout <<(*hj)->employee_code <<"  "<<(*hj)->name<<"  "<<(*hj)->surname<< endl;
           }
		}
	}*/
	
	pthread_mutex_lock(&courseaffac);
   if(!alloafgen)
    {	//cout <<"Hererererrererrerererererererererer\n";
    	
    	alloafgen=1;
    	pthread_cond_signal(&condcoraffac);
    	
    }
    pthread_mutex_unlock(&courseaffac);
	(opl).waketime=-1;
	pthread_mutex_lock(&timeconvey);
	getSem(p);
	cout << "Fac thread msg to timekeep for waketime time "<<opl.waketime<< endl;
	relSem(p);
		send_msg(msggentotim,&opl);
	pthread_mutex_unlock(&timeconvey);
	
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

int Y = 2012;
void * generateStudents(void * args)
{	
	mymsgbuf iol;
	iol.mtype=1;
	iol.thdid=2;
	while(true)
	{
		pthread_mutex_lock(&StudMutex);
		if(!runThdStud)
		{		
			pthread_cond_wait(&StudCond,&StudMutex);
		}
		runThdStud=0;
		pthread_mutex_unlock(&StudMutex);
		fromStud=1;
		getSem(p);
		cout <<"GENERATING STUDENTS"<< endl;
		relSem(p);
		
		increase_year();
        for(std::vector<UNIV>::iterator it=universities.begin();it!=universities.end();it++)
		{
			for(std::map<string,dept>::iterator k=(*it).depts.begin(); k!=(*it).depts.end(); k++)
			{
				genstuof1dept(k->second.studperyr, &*it, &k->second,studRANDOM, Y); //year dhang se dena
			}
		}
		//cout << "before kill students \n";
		++Y;
		kill();
		getSem(p);
		cout << "Finished student work"<< endl;
		relSem(p);
		pthread_mutex_lock(&courseafStud);
    	
    		pthread_cond_signal(&condcorafStud);
    		alloafStud=1;
    	
    	pthread_mutex_unlock(&courseafStud);
		fromStud=0;
		iol.waketime=curr_time+527040;
		getSem(p);
		cout <<"STUDENT WAKE ME UP " <<iol.waketime<< endl;
		relSem(p);
		pthread_mutex_lock(&timeconvey);
		
			send_msg(msggentotim,&iol);
		pthread_mutex_unlock(&timeconvey);
		

	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
void * generateCourses(void * args)
{	mymsgbuf qwe;
	qwe.mtype=1;
	qwe.thdid=3;
	//cout << "i m here"<< endl;
	while(true)
	{
	
		pthread_mutex_lock(&CourseMutex);
		
		if(!runThdCourse)
		{
			pthread_cond_wait(&CourseCond,&CourseMutex);
		}
		runThdCourse=0;
		pthread_mutex_unlock(&CourseMutex);
		fromCourse=1;
		pthread_mutex_lock(&courseafStud);
		if(curr_time%527040!=0)
		{
			alloafStud=1;
		}
		
    	pthread_mutex_unlock(&courseafStud);
    	getSem(p);
		cout << "GENERATING COURSES "<< endl;
		relSem(p);
		
		floatCourses(courseRANDOM);
			allocateCourses(courseRANDOM);
		fromCourse=0;
	
		qwe.waketime=curr_time+263520;
		
		pthread_mutex_lock(&timeconvey);
		getSem(p);
		cout << "COURSES WAKE ME UP AT :"<< qwe.waketime<< endl;
		relSem(p);
				
			send_msg(msggentotim,&qwe);
			
		pthread_mutex_unlock(&timeconvey);
	}
}

void * genFen(void * args)
{mymsgbuf fen;
	fen.mtype=1;
	fen.thdid=4;
	int tmp2;
	bool FriAfAll=1;
	while(true)
	{
		pthread_mutex_lock(&FriendMutex);
		if(!runThdFriend)
		{
			pthread_cond_wait(&FriendCond,&FriendMutex);
		}
		runThdFriend=0;
		pthread_mutex_unlock(&FriendMutex);
		
		if(curr_time%263520==0)
		{
			FriAfAll==1;
		}
		if(FriAfAll)
		{
			FriAfAll=0;
			while(fromStud || fromCourse)
			{
				continue;
			}
		}
		getSem(p);
		cout << "Generating Friends"<< endl;
		relSem(p);
		
		tmp2=genFriends((void*)(&curr_time));
		if(tmp2==0)
		{
			tmp2=60;//Choose accordingly:: 300=>1217; 100=>3681; 75=>4819; 65=> 5631;
		}
		fen.waketime=curr_time+tmp2;
		getSem(p);
		cout << "Friends wake me up at "<< fen.waketime<<  endl;
		relSem(p);
		pthread_mutex_lock(&timeconvey);
				
		send_msg(msggentotim,&fen);
		pthread_mutex_unlock(&timeconvey);



	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------GRAPHS-------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

void *  readpp(void * args)
{	
		timetogen=ftok("TimeKeeper.cpp",'a');
		gentotime=ftok("generator.cpp",'b');
		msgtimtogen=open_queue(timetogen);
		msggentotim=open_queue(gentotime);
		curr_time=0;
		int qwert=*static_cast<int *>(args);
		pthread_mutex_init(&facMutex,NULL);
		pthread_mutex_init(&StudMutex,NULL);
		pthread_mutex_init(&CourseMutex,NULL);
		pthread_mutex_init(&FriendMutex,NULL);
		pthread_mutex_init(&timeconvey,NULL);
		pthread_mutex_init(&courseaffac,NULL);
		pthread_mutex_init(&courseafStud,NULL);
		pthread_cond_init(&facCond,NULL);
		pthread_cond_init(&condcorafStud,NULL);	
		pthread_cond_init(&StudCond,NULL);
		pthread_cond_init(&CourseCond,NULL);
		pthread_cond_init(&FriendCond,NULL);
		pthread_t genStud,genFac,genCourses,genFriends;
		pthread_create(&genFac,NULL,&generateFaculty,NULL);
		pthread_create(&genStud,NULL,&generateStudents,NULL);
		pthread_create(&genCourses,NULL,&generateCourses,NULL);
		pthread_create(&genFriends,NULL,&genFen,NULL);
		pthread_detach(genFac);
		pthread_detach(genStud);
		pthread_detach(genCourses);
		pthread_detach(genFriends);
		int thd;bool recmsgs[4];mymsgbuf recieve;
		p=open_sem(111,1);
		while(true)
		{	
			rec_msg(msgtimtogen,&recieve,1);
			thd=recieve.thdid;
			curr_time=recieve.waketime;
			if(curr_time>qwert)
			{
				msgctl(msgtimtogen,IPC_RMID,NULL);
				msgctl(msggentotim,IPC_RMID,NULL);
				for(unsigned long position = 0 ; position < allstudents.size();position++)
				{
				allstudents[position]->location_in_allstudents = position;
				}
				kill();
				getSem(p);
				cout << "Generating GraphML"<< endl;
				cout << "Cleaning UP"<< endl;
				relSem(p);
				pthread_cancel(genFac);
				pthread_cancel(genStud);
				pthread_cancel(genCourses);
				pthread_cancel(genFriends);
				pthread_mutex_destroy(&facMutex);
				pthread_mutex_destroy(&StudMutex);
				pthread_mutex_destroy(&CourseMutex);
				pthread_mutex_destroy(&FriendMutex);
				pthread_mutex_destroy(&timeconvey);
				pthread_mutex_destroy(&courseaffac);
				pthread_mutex_destroy(&courseafStud);
				pthread_cond_destroy(&facCond);
				pthread_cond_destroy(&StudCond);
				pthread_cond_destroy(&CourseCond);
				pthread_cond_destroy(&FriendCond);
				pthread_cond_destroy(&condcorafStud);
				semctl(p, 0, IPC_RMID,NULL);

				graphconverter();
				kill_all();
				
				pthread_exit(NULL);
			}
			getSem(p);
			cout << "GENERATOR RECIEVES FOR "<<thd<<" TIME TO WAKE  : "<<curr_time<< endl;
			relSem(p);
		switch(thd)
		{
			case 1:
			{
				pthread_mutex_lock(&facMutex);
				runThdfac=1;
				pthread_cond_signal(&facCond);
				pthread_mutex_unlock(&facMutex);
				getSem(p);
				cout << "FACULTY  SIGNALLED\n";
				relSem(p);
				break;
			}
			case 2:
			{
				pthread_mutex_lock(&StudMutex);
				runThdStud=1;
				pthread_cond_signal(&StudCond);
				pthread_mutex_unlock(&StudMutex);
				getSem(p);
				cout << "Year : "<< (2012+curr_time/527040)<< endl;
				cerr << "Year : "<< (2012+curr_time/527040)<< endl;
				cout << "STUDENT  SIGNALLED\n";
				relSem(p);
				break;
			}
			case 3:
			{
				pthread_mutex_lock(&CourseMutex);
				runThdCourse=1;
				pthread_cond_signal(&CourseCond);
				pthread_mutex_unlock(&CourseMutex);
				getSem(p);
				cout << "COURSES  SIGNALLED\n";
				relSem(p);
				break;
			}
			case 4:
			{
				pthread_mutex_lock(&FriendMutex);
				runThdFriend=1;
				pthread_cond_signal(&FriendCond);
				pthread_mutex_unlock(&FriendMutex);
				getSem(p);
				cout << "FRIEND  SIGNALLED\n";
				relSem(p);
				break;
			}
		}
	}
	
	
	
	
}
