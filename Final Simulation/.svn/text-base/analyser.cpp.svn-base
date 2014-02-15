#include "analyser.h"
#include "Semaphore.h"
using namespace std;

int floyd();
int qwerty =0;
void clique(int);
void shortest_path(int,int);
void largestshortestpath();
void list_short_path(int,int);
int importance(int);
void printimp(int i);
void moreimp(int);
int* dijstra(int);
int shortpath(int,int);
int * shortestdist;
int * previous;
vector<int> shortestpath;
vector<studnode> studgraph;
map<string,facnode> facgraph;
int m=0;
bool jkl=false;
int ** shortdist;
int **path;
int ** countpath;
int main(int args,char**argv)
{	int j=open_sem(111,1);
	int i = 0;
	ifstream gml(argv[1],ifstream::in);
	while(gml.good())
	{
		i++;
		string h;
		getline(gml,h);
		if(i != 5565)
		
		if(h[1]=='n')
		{
			
			int i=0;
			bool isStud=false;
			studnode (*st) =new studnode();
			facnode (*fac)=new facnode();
			getline(gml,h);
			while(h!="</node>")
			{	string tmp;
				tmp=h.substr(16,h.length()-23);
				
				switch(i)
				{
					case 0:
						if(tmp=="Student")
						{
							isStud=true;
						}
						break;
					case 1:
						if(isStud)
							(*st).name=tmp;
						else
							(*fac).name=tmp;
						break;
					case 2:
						if(isStud)
							(*st).surname=tmp;
						else
							(*fac).surname=tmp;
						break;
					case 3:
						if(isStud)
							(*st).entryno=atoi(tmp.c_str());
						else
							(*fac).entryno=atoi(tmp.c_str());
							break;
					case 4:
						if(isStud)
							(*st).batch=atoi(tmp.c_str());
						break;
					case 5:
						if(isStud)
							(*st).year=atoi(tmp.c_str());
						break;
					case 6:
						if(isStud)
							(*st).roomNo=atoi(tmp.c_str());
						else
							(*fac).roomNo=atoi(tmp.c_str());
						break;
					case 7:
						if(isStud)
							(*st).floor=tmp[0];
						break;
					case 8:
						if(isStud)
							(*st).hostel=tmp;
						else
							(*fac).hostel=tmp;
						break;
					case 9:
						if(isStud)
							(*st).dept=tmp;
						else
							(*fac).dept=tmp;
						break;
					case 10:
						if(isStud)
							(*st).univ=tmp;
						else
							(*fac).univ=tmp;
						break;
					case 11:
						if(isStud)
						{
							char * temp=(char *)tmp.c_str();
							char *a;
							a=strtok(temp,"$");
							while(a!=NULL)
							{
								((*st)).interests.push_back(string(a));
								a=strtok(NULL,"$");
							}
						}
						else
						{
							char * temp=(char *)tmp.c_str();
							char *a;
							a=strtok(temp,"$");
							while(a!=NULL)
							{
								((*fac)).interests.push_back(string(a));
								a=strtok(NULL,"$");
							}
						}
						break;
					case 12:
						if(isStud)
						{
							char * temp=(char *)tmp.c_str();
							char *a;
							a=strtok(temp,"$");
							while(a!=NULL)
							{
								((*st)).courses.push_back(string(a));
								a=strtok(NULL,"$");
							}
						}
						else
						{
							char * temp=(char *)tmp.c_str();
							char *a;
							a=strtok(temp,"$");
							while(a!=NULL)
							{
								((*fac)).courses.push_back(string(a));
								a=strtok(NULL,"$");
							}
						}
						break;
				}
			
				getline(gml,h);
				i++;
			}
			if(isStud)
				studgraph.push_back(*st);
			else
				facgraph[(*fac).name]=*fac;
			delete st;
			delete fac;	
			
		}
		else if(h[1]=='e')
		{	
			size_t s=h.find("source");
			int t=(int)s;
			string vertex1 = "";
			while(h[t+9]!='"')
			{
				vertex1.push_back(h[t+9]);
				t++;
			}
			s=h.find("target");
			t=(int)s;
			string vertex2 = "";
			while(h[t+9]!='"')
			{
				vertex2.push_back(h[t+9]);
				t++;
			}
			int v1=atoi(vertex1.c_str());
			
			int v2 =atoi(vertex2.c_str());
			studgraph[v1].friends.push_back(v2);
			
		}
		
	}
	/*for(std::vector <studnode> ::iterator it=studgraph.begin();it!=studgraph.end();it++)
	{
		cout << (*it).name<< " " <<(*it).surname<<" "<<(*it).entryno<< endl;
		cout << "friends with : "<< endl;
		for(std::vector <int> :: iterator k=(*it).friends.begin();k!=(*it).friends.end();k++)
			{
				cout <<studgraph[*k].entryno<< " ";
			}
			cout << endl;
		
	}*/
	
	int offset=studgraph[0].entryno;
	
	relSem(j);//mandatory
	getSem(j);
	cout << "Processing Data"<< endl;
	floyd();
	relSem(j);
	
	sleep(1);
	FILE * filename;
	ofstream outputfile;
	int qtype=0,stid1=0,stid2=0;
	char a[20],b[20];
	while(true)
	{
	getSem(j);
	for(int q=0;q<20;q++)
	{
		a[q]='\0';
		b[q]='\0';
	}
	filename=fopen("query.txt","rb");
	fscanf(filename,"%d",&qtype);
	fscanf(filename,"%d",&stid1);
	fscanf(filename,"%s",a);
	fscanf(filename,"%d",&stid2);
	fscanf(filename,"%s",b);
	fclose(filename);
	string g(a);
	string h(b);
	//cout << g << endl;
	//cout << h << endl;
	//cout <<studgraph[stid1-offset].univ<< endl;
	//cout << (studgraph[stid1-offset].univ!=g)<< endl;
	if(stid1!=-1 && (stid1-offset<0 || stid1-offset>=studgraph.size()))
	{
		cout << "Student one does not exist in graph"<< endl;
		qtype=-2;
	}
	else if(stid1!=-1 && studgraph[stid1-offset].univ!=g)
	{
		cout << "The person does not exist in the graph"<< endl;
		cout << "Did you mean "<< studgraph[stid1-offset].univ<< endl;
		qtype=-2;
	}
	if(stid2!=-1 && (stid2-offset<0 || stid2-offset>=studgraph.size()))
	{
		cout << "Student two does not exist in graph"<< endl;
		qtype=-2;
	}
	
	else if(stid2!=-1 && studgraph[stid2-offset].univ!=h)
	{
		cout << "The person does not exist in the graph"<< endl;
		cout << "Did you mean "<< studgraph[stid2-offset].univ<< endl;
		qtype=-2;
	}
//cout << "after "<< endl;
	
	/*outputfile.open("query.txt");
	outputfile << "DONE"<< endl;
	outputfile.close();*/
	switch(qtype)
	{
		
		case -1:
			relSem(j);
			semctl(j, 0, IPC_RMID,NULL);
			exit(0);
			break;
		case 1:
			clique(stid1-offset);
			break;
		case 2:
			
			qwerty = 2;
	
			shortest_path(stid1-offset,stid2-offset);
			break;
		case 3:
			qwerty = 3;
			m = 0;
			list_short_path(stid1-offset,stid2-offset);
			if(jkl)
			{
				cout <<studgraph[stid2-offset].name<<" "<<studgraph[stid2-offset].surname<<"("<<studgraph[stid2-offset].entryno<<","<<studgraph[stid2-offset].univ<<")"<<endl;
				jkl = false;
			}
			
			break;
		case 4:
			largestshortestpath();
			break;
		case 5:
			printimp(stid1-offset);
			break;
		case 6:
			moreimp(stid1-offset);
			break;	
		default :
			break;
	}
	relSem(j);
	sleep(2);
}
}
int shortpath(int id1,int id2){
	int c = 0;
	bool unvisited[studgraph.size()];
	shortestdist = new int[studgraph.size()];
    previous = new int[studgraph.size()];
	
	vector<int> unvisitednodes;
	int i;

	for(i = 0; i < studgraph.size();i++){
		unvisited[i] = true;
		previous[i] = 0;
		if(i == id1){
			shortestdist[i] =0;
		}
		else{
			shortestdist[i] = 10000;
			
		}
	}
	//if (shortdist[176] == 10000)
	int tmp;
	unvisitednodes.push_back(id1);
	while(unvisitednodes.size() != 0){
		int ad = unvisitednodes.back();
		unvisitednodes.pop_back();
		unvisited[ad] = false;
		for(std::vector<int> ::iterator it = (studgraph[ad].friends).begin();it!=(studgraph[ad].friends).end();it++ ){
			tmp = shortestdist[ad] + 1;
			if(tmp < shortestdist[(*it)] && unvisited[(*it)]){
				shortestdist[(*it)] = tmp;
				previous[(*it)] = ad;
				unvisitednodes.push_back((*it));
			}
		}
			}
	
		delete(shortestdist);//*****
	int prev;
	int * prevfr = previous;
	prev  = id2;
	int count;
	while (prev != id1){
		count++;
		prev = prevfr[prev];
		if(qwerty == 3)
		{
			cout << prev;
		}
		shortestpath.push_back(prev);
	}
	shortestpath.clear();//*******
	if(qwerty == 2)
	{
		cout << "shortest dist : "<<count << endl;
	}
	qwerty = 0;
	delete(previous);//************
	return count;

}
/*
int shortpath(int id1,int id2){
	int prev;
	int * prevfr = dijstra(id1);
	prev  = id2;
	int count;
	while (prev != id1){
		count++;
		prev = prevfr[prev];
		cout << prev;
		shortestpath.push_back(prev);
	}
	shortestpath.clear();//*******
	cout << count << endl;
	return count;
}
*/
int floyd()
{	
	shortdist=new int*[studgraph.size()];
	path=new int*[studgraph.size()];
	countpath=new int*[studgraph.size()];
	for(int u=0;u<studgraph.size();u++)
	{
		shortdist[u]=new int[studgraph.size()];
		path[u]=new int[studgraph.size()];
		countpath[u]=new int[studgraph.size()];
	}
	for(int i=0;i<studgraph.size();i++)
	{
		for(int j=0;j<studgraph.size();j++)
			{
				if(i==j)
					shortdist[i][i]=0;
				else
					shortdist[i][j]=100000;
				path[i][j]=-1;
				countpath[i][j]=0;
			}
		countpath[i][i] = 1;
		}
	for(int o=0;o<studgraph.size();o++)
		for(int f=0;f<studgraph[o].friends.size();f++)
		{
			shortdist[o][studgraph[o].friends[f]]=1;
			path[o][studgraph[o].friends[f]]=-2;
			countpath[o][studgraph[o].friends[f]]=1;
		}
	for(int y=0;y<studgraph.size();y++)
			{
			for(int b=0;b<studgraph.size();b++)
				{ 
				for(int k=0;k<studgraph.size();k++)
				{
					if(shortdist[b][y]+shortdist[y][k]<shortdist[b][k])
					{
						shortdist[b][k]=shortdist[y][k]+shortdist[b][y];
						path[b][k]=y;
						countpath[b][k]=1;
					}
					else if((shortdist[b][y]+shortdist[y][k]==shortdist[b][k])&&(y!=b)&&(y!=k)&&(k!=b))
					{
						countpath[b][k]+=1;
					}
				}		
			}
		}
	//return 0;
}

void shortest_path(int i,int j)
{	if(shortdist[i][j] >= 10000)
	{
		cout<<"They are not connected."<<endl;
	}
	else
	{
		cout<< "Shortest distance between "<<studgraph[i].name<<" "<<studgraph[i].surname<<" and "<<studgraph[j].name<<" "<<studgraph[j].surname<<" is "<<shortdist[i][j]<<endl;
	}
}

void list_short_path(int i,int j)
{	
	if(shortdist[i][j]>=100000)
	{	cout << "No path between the these people"<< endl;
		return ;
	}
	else if(shortdist[i][j]==1)
	{
		jkl=true;
		if(m==0)
		{
			cout <<studgraph[i].name<<" "<<studgraph[i].surname<<"("<<studgraph[i].entryno<<","<<studgraph[i].univ<<")"<<" --> ";
		}
		else
		{
			cout <<studgraph[i].name<<" "<<studgraph[i].surname<<"("<<studgraph[i].entryno<<","<<studgraph[i].univ<<")"<<" --> ";
		}
	}
	else
	{	
		jkl=true;
		m++;
		list_short_path(i,path[i][j]);
		//cout << studgraph[path[i][j]].name<<" "<<studgraph[path[i][j]].surname <<"("<<studgraph[path[i][j]].entryno<<","<<studgraph[path[i][j]].univ<<")"<<" --> ";
		list_short_path(path[i][j],j);
	}
	
}
void last(int i,int j)
{
	cout << studgraph[path[i][j]].name<<" "<<studgraph[path[i][j]].surname <<"("<<studgraph[path[i][j]].entryno<<","<<studgraph[path[i][j]].univ<<")"<<endl;
}
int importance(int i)
{
	int ans=0;
	for(int b=0;b<studgraph.size();b++)
	{	
		for(int v=b+1;v<studgraph.size();v++)
			{
				if(shortdist[b][v]>=100000)
				{
					continue;
				}
				
				else if(shortdist[b][i]+shortdist[i][v]==shortdist[b][v])//&&(i != b)&&(i != v))
					{
						
						ans+=countpath[b][i]*countpath[i][v];
					}
			}
	}
return ans;		
}

void printimp(int i)
{
		cout << "Importance of "<< studgraph[i].name <<" "<< studgraph[i].surname<< " is " <<importance(i)<< endl;
	
}
void moreimp(int i)
{
	vector<int> more;
	int imp=importance(i);
	for(std::vector<int> ::iterator it=(studgraph[i].friends).begin();it!=(studgraph[i].friends).end();it++)
	{
		int temp=importance(*it);
		if(temp>imp)
			more.push_back(*it);
	}
	cout << "No. of friends having more importance are : "<<more.size()<< endl;
	cout << "Friends list is : "<< endl;
	for (int f=0;f<more.size();f++)
	{
		cout << studgraph[more[f]].name<< " "<< studgraph[more[f]].surname<< " entry no.: "<< studgraph[more[f]].entryno<<endl;
	}
}
void largestshortestpath()
{
	int min=std::numeric_limits<int>::min();
	for(int h=0;h<studgraph.size();h++)
		for(int o=h;o<studgraph.size();o++)
		{
			if(shortdist[h][o]>=100000)
			{
				continue;
			}
			if(shortdist[h][o]>min)
				min=shortdist[h][o];
		}
	if(min != 0)	
	{
		cout << "The maximum of shortest path is : "<<min<<endl;
	}
	else
	{
		cout << "The graph is disconnected."<<min<<endl;
	}
	
}
bool checkfriends(int i,int j)
{
	for(int k=0;k<studgraph[i].friends.size();k++)
	{
		if(studgraph[i].friends[k]==j)
		{
			return true;
		}
	}
	return false;
}
vector<int> compute_clique(int,int,vector<int>);
void clique(int i)
{
	vector<int> tempclique;
	vector<int> g;
	tempclique.push_back(i);
	g=compute_clique(i,0,tempclique);
	cout<< "Clique size is "<< g.size()<< endl;
	cout << "Members of clique are :"<< endl;
	for(int b=0;b<g.size();b++)
	{
		cout << studgraph[g[b]].name<<" "<< studgraph[g[b]].surname<< endl;
	}
}

vector<int> compute_clique(int i,int j ,vector<int> l)
{
	vector<int> a;
	vector<int> b;
	if(j==studgraph[i].friends.size())
	{
		return l;
	}
	a=compute_clique(i,j+1,l);
	bool dc=false;
	for(int f=0;f<l.size();f++)
	{
		if(!(checkfriends(l[f],studgraph[i].friends[j])))
		{
			dc=true;
		}
	}
	if(!dc){
	
	l.push_back(studgraph[i].friends[j]);
	b=compute_clique(i,j+1,l);
	if(a.size()>b.size())
	{
		return a;
	}
	else
	{
		return b;
	}
	}
	else
	{
	return a;
	}
	
}
