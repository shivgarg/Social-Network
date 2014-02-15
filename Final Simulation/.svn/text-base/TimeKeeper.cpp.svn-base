	/*
 * TimeKeeper.cpp
 *
 *  Created on: 8 Oct 2013
 *      Author: shivam
 */
#include "TimeKeeper.h"


using namespace std;

/*! \mainpage CSP301 :: Graph Simulation and Query Matching
 *
 * \section intro_sec Introduction
 *
 * This product aims to simulate and then do query analysis on the graph.
 */
int duration;

int p;
int main(int args, char** argv)
{

	        pid_t childpid;
	        duration=0;
	        setEnviro(argv[1]);
	        int simruntime=(atoi(argv[2]))*60*24*366 -1 ;
	        cout << "Simulation run time   "<<simruntime<< endl;
			
			cout<< "Environment Set"<< endl;
	        if((childpid = fork()) == -1)
	        {
	                perror("fork");
	                exit(1);
	        }

	        if(childpid == 0)
	        {
	           
	            pthread_t genthread;
	        	pthread_create(&genthread,NULL,&readpp,(void*)&simruntime);
				pthread_join(genthread,NULL);
				//readpp((void*)&simruntime);
				return 0;
	        }
	        else
	        {
				p=open_sem(111,1);
				key_t timetogen,gentotime;
				timetogen=ftok("TimeKeeper.cpp",'a');
				gentotime=ftok("generator.cpp",'b');
				int msgtimtogen,msggentotim;
				msgtimtogen=open_queue(timetogen);
				msggentotim=open_queue(gentotime);
				mymsgbuf input,output;
				relSem(p);
				bool waitmsg[4];
				priority_queue< pair<int,int> ,vector<pair<int,int> >,pq_operand> schedule;

				for(int g=0;g<4;g++)
				{
					pair<int,int> as;
					as.first=g+1;
					as.second=0;
					schedule.push(as);
				}

				pair<int,int> temp,tmp1;input.mtype=1;
				while(true)
				{
						temp=schedule.top();
						while(temp.second<duration )
						{
							schedule.pop();
							temp=schedule.top();
						}

						duration=temp.second;
						getSem(p);
						cout << "CURRENT TIME "<< duration<< endl;
						relSem(p);
						(input).thdid=temp.first;
						input.waketime=temp.second;
						waitmsg[temp.first-1]=true;
						schedule.pop();
						send_msg(msgtimtogen,&input);
						
						getSem(p);
						cout << "TIME KEEPER  SENT TO GENERATOR FOR "<< input.thdid<< " AT TIME "<< input.waketime<< endl;
						relSem(p);
						if(duration>simruntime)
						{	getSem(p);
							cout << "Simulation Finished"<< endl;
							relSem(p);
							break;
						}
						while((!schedule.empty()) && (duration==schedule.top().second))
						{
							tmp1=schedule.top();
							(input).thdid=tmp1.first;
							input.waketime=tmp1.second;
							waitmsg[tmp1.first-1]=true;
							getSem(p);
							cout << "TIME KEEPER  SENT TO GENERATOR FOR "<<input.thdid<<" AT TIME  "<<input.waketime<< endl;
							relSem(p);
							send_msg(msgtimtogen,&input);
							schedule.pop();
							
						}
							for(int i=0;i<4;i++)
							{	
								if(waitmsg[i])
								{
									getSem(p);
								cout << "WAITING   FOR  THREAD "<<i+1<< endl;
								relSem(p);
								rec_msg(msggentotim,&output,1);
								
								pair<int,int> tmp;
								tmp.first=output.thdid;

								tmp.second=output.waketime;
								getSem(p);
								cout << "TIMEKEEPER RECIEVES "<<tmp.first<<"  "<<" WAKEUP TIME  "<< tmp.second<< endl;
								relSem(p);
								schedule.push(tmp);
								waitmsg[i]=false;
								}
							
						}

						
				}
				getSem(p);
				cout << "Timekeeper is outside the loop\n";
				relSem(p);
				sleep(1);
				
	        }
	        
	       }



