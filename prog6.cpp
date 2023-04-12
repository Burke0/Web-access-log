/*
 * prog6.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: Alex
 */

#include "accesslog.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
int main()
{
	string line;
	int numLogs=0;
	ifstream logFile;
	logFile.open("web.log");
	if(logFile.fail())
		cerr<<"File could not open successfully"<<endl;
	else
		while(logFile.good())
		{
			getline(logFile, line);
			numLogs++;
		}
	logFile.close();
	logFile.open("web.log");
	if(logFile.fail())
		cerr<<"File could not open successfully"<<endl;
	AccessLog *aLog=new AccessLog[numLogs];
	for(int i=0; i<numLogs; i++)//populates AccessLogs
	{
		logFile>>aLog[i];
	}
	for(int i=0; i<numLogs-1; i++)//simple bubble sort
	{
		for(int j=0; j<numLogs-1; j++)
		{
			if(aLog[j+1]>aLog[j])
				swap(aLog[j], aLog[j+1]);
		}
	}
	for(int i=0; i<numLogs; i++)//outputs AccessLogs in appropriate format
	{
		cout<<aLog[i]<<endl;
	}
	delete [] aLog;
	aLog=nullptr;

	return 0;
}

