//
//  main.cpp
//  print
//
//  Created by Abhinav Deep Singh on 14/10/13.
//  Copyright (c) 2013 Abhinav Deep Singh. All rights reserved.
//
#include <string.h>
#include <iostream>
#include <fstream>
#include "global1.h"
#include "graphml.h"
//vector<faculty*>allfaculty;
//vector<student*>allstudents;
using namespace std;

void graphconverter()
{
    int edge_id = 0;
    int n = 0;
    ofstream outputFile;
    outputFile.open("graph.graphml");
    
    outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    outputFile << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"  "<<endl;
    outputFile << "            xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "<<endl;
    outputFile << "            xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "<<endl;
    outputFile << "                                http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\" " << endl;
    outputFile << "  <key id=\"d00\" for=\"node\" attr.name=\"Stud_Fac\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d01\" for=\"node\" attr.name=\"Name\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d02\" for=\"node\" attr.name=\"Surname\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d03\" for=\"node\" attr.name=\"EntryNo.\" attr.type=\"int\"/>"<<endl;
    outputFile << "  <key id=\"d04\" for=\"node\" attr.name=\"Batch\" attr.type=\"int\"/>"<<endl;
    outputFile << "  <key id=\"d05\" for=\"node\" attr.name=\"Year\" attr.type=\"int\"/>"<<endl;
    outputFile << "  <key id=\"d06\" for=\"node\" attr.name=\"RoomNo.\" attr.type=\"int\"/>"<<endl;
    outputFile << "  <key id=\"d07\" for=\"node\" attr.name=\"Floor\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d08\" for=\"node\" attr.name=\"Hostel\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d09\" for=\"node\" attr.name=\"Department\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d10\" for=\"node\" attr.name=\"University\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d11\" for=\"node\" attr.name=\"Interests\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <key id=\"d12\" for=\"node\" attr.name=\"Courses\" attr.type=\"string\"/>"<<endl;
    outputFile << "  <graph id=\"G\" edgedefault=\"undirected\">"<<endl;
    
    for(unsigned long i = 0; i < allstudents.size(); i++) //print
    {
        allstudents[i]->location_in_allstudents = i;
    }
    
    for(unsigned long i = 0; i < allstudents.size(); i++) //print
    {
        string interests= "";
        string courses = "";
        for(std::vector<interest*>::iterator in=(allstudents[i]->intrst).begin();in!=(allstudents[i]->intrst).end();in++)
        {
            interests = interests +"$"+(*in)->name;
        }
        for(std::vector<course*>::iterator c=(allstudents[i]->sem_dep_courses_taken).begin();c!=(allstudents[i]->sem_dep_courses_taken).end();c++)
        {
            courses = courses +"$"+(*c)->name;
        }
        for(std::vector<course*>::iterator c=(allstudents[i]->sem_non_dep_courses_taken).begin();c!=(allstudents[i]->sem_non_dep_courses_taken).end();c++)
        {
            courses = courses +"$"+(*c)->name;
        }
        outputFile << "<node id=\"n"<<i<< " \" >"<<endl;
        outputFile << "<data key=\"d00\">"<<"Student"<<"</data>"<<endl;
        outputFile << "<data key=\"d01\">"<<allstudents[i]->name<<"</data>"<<endl;
        outputFile << "<data key=\"d02\">"<<allstudents[i]->surname<<"</data>"<<endl;
        outputFile << "<data key=\"d03\">"<<allstudents[i]->Entry_No<<"</data>"<<endl;
        outputFile << "<data key=\"d04\">"<<allstudents[i]->Batch<<"</data>"<<endl;
        outputFile << "<data key=\"d05\">"<<allstudents[i]->Year<<"</data>"<<endl;
        outputFile << "<data key=\"d06\">"<<allstudents[i]->room_no<<"</data>"<<endl;
        outputFile << "<data key=\"d07\">"<<allstudents[i]->floor<<"</data>"<<endl;
        outputFile << "<data key=\"d08\">"<<allstudents[i]->host->name<<"</data>"<<endl;
        outputFile << "<data key=\"d09\">"<<allstudents[i]->dep->name<<"</data>"<<endl;
        outputFile << "<data key=\"d10\">"<<allstudents[i]->uni->name<<"</data>"<<endl;
        outputFile << "<data key=\"d11\">"<<interests<<"</data>"<<endl;
        outputFile << "<data key=\"d12\">"<<courses<<"</data>"<<endl;
        outputFile << "</node>"<<endl;
        
       
        
    }
    
    n = allstudents.size();
    for(unsigned long i = 0; i < allfaculty.size(); i++) //print
    {
        string interests= "";
        string courses = "";
        for(std::vector<interest*>::iterator in=(allfaculty[i]->intrst).begin();in!=(allfaculty[i]->intrst).end();in++)
        {
            interests = interests +"$"+(*in)->name;
        }
        for(std::vector<course*>::iterator c=(allfaculty[i]->courses_taken).begin();c!=(allfaculty[i]->courses_taken).end();c++)
        {
            courses = courses +"$"+(*c)->name;
        }
        outputFile << "<node id=\"n"<<n+i<<"\">"<<endl;
        outputFile << "<data key=\"d00\">"<<"Faculty"<<"</data>"<<endl;
        outputFile << "<data key=\"d01\">"<<allfaculty[i]->name<<"</data>"<<endl;
        outputFile << "<data key=\"d02\">"<<allfaculty[i]->surname<<"</data>"<<endl;
        outputFile << "<data key=\"d03\">"<<allfaculty[i]->employee_code<<"</data>"<<endl;
        outputFile << "<data key=\"d04\">"<<""<<"</data>"<<endl;
        outputFile << "<data key=\"d05\">"<<""<<"</data>"<<endl;
        outputFile << "<data key=\"d06\">"<<allfaculty[i]->plotno<<"</data>"<<endl;
        outputFile << "<data key=\"d07\">"<<""<<"</data>"<<endl;
        outputFile << "<data key=\"d08\">"<<allfaculty[i]->house->name<<"</data>"<<endl;
        outputFile << "<data key=\"d09\">"<<allfaculty[i]->department->name<<"</data>"<<endl;
        outputFile << "<data key=\"d10\">"<<allfaculty[i]->uni->name<<"</data>"<<endl;
        outputFile << "<data key=\"d11\">"<<interests<<"</data>"<<endl;
        outputFile << "<data key=\"d12\">"<<courses<<"</data>"<<endl;
        outputFile << "</node>"<<endl;
        
    }
	for(unsigned long i = 0; i < allstudents.size(); i++) //print
    {
		for(std::vector<student*>::iterator fr=(allstudents[i]->friends).begin();fr!=(allstudents[i]->friends).end();fr++)
        {
            outputFile << "<edge id=\"e"<<edge_id<<"\" source=\"n"<<i<<"\" target=\"n"<<(*fr)->location_in_allstudents<<"\"/>"<<endl;
            edge_id++;
        }
    }
    outputFile << "  </graph>"<<endl;
    outputFile << "</graphml>"<<endl;
    outputFile.close();
    cout << "Done!\n";
    
 //   return 0;
}
