

#include "global1.h"
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
			(v1->friends).erase((v1->friends).begin() + u);
		}
	}
	//graphmatrix[v1][v2] = false;
	//graphmatrix[v2][v1] = false;
	numedges--;
}

int graph::no_of_friends(student* v1){
	int ans = (v1->friends).size();
	return ans;
}

bool graph::already_friends(student *v1, student *v2){
	bool arefriends = false;
	for(std::vector<student*>::iterator k = (v1->friends).begin() ; k < (v1->friends).end() ; k++){
		if((*k) == v2){
			arefriends =true;
		}
	}
	return arefriends;
}
