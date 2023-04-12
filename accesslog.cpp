/*
 * accesslog.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: Alex
 */
#include "accesslog.h"
#include<iostream>
#include <iomanip>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
AccessLog::AccessLog()//initializes all variables
{
	clientIp="";
	clientMethod="";
	requestedResource="";
	protocol="";
	pageLink="";
	serverStatusCode="";
	accessMonth="";
	accessDay=0;
	accessYear=0;
	objectSize=0;
}

bool AccessLog::operator >(const AccessLog& right)const//overloaded > comparison operator to sort with
{
	return (this->clientIp>right.clientIp);
}
/**********************************************************
* Description: extraction operator >> overloaded to populate an accessLog object from one line of log file
* Input: input stream and AcessLog passed by reference
* Output: it returns input stream populated with data
**********************************************************/
istream& operator >>(istream& log, AccessLog& datlog)
{
	string junkline;
	log>>datlog.clientIp;
	getline(log, junkline,'[');
	getline(log,junkline,'/');
	datlog.accessDay=atoi(junkline.c_str());
	getline(log, datlog.accessMonth,'/');
	getline(log,junkline,':' );
	datlog.accessYear=atoi(junkline.c_str());
	getline(log,junkline,'"');
	if(log.peek()=='-')
	{
		datlog.clientMethod="-";
		datlog.requestedResource="-";
		datlog.protocol="-";
		log.ignore(3);
	}
	else
	{
	log>>datlog.clientMethod;
	log.ignore();
	log>>datlog.requestedResource;
	getline(log,datlog.protocol,'"');
	}
	log>>datlog.serverStatusCode;
	getline(log,junkline,'"');
	datlog.objectSize=atof(junkline.c_str());
	getline(log,datlog.pageLink,'"');
	getline(log,junkline);
	return log;
}

/**********************************************************
* Description: Overloaded insertion << operator to display one AccessLog object in the required format
* Input: output stream and AccessLog object passed by reference
* Output: It returns the output stream
**********************************************************/
ostream& operator <<(ostream& out, const AccessLog& datlog)
{
	out<<left<<setw(14)<<datlog.clientIp<<datlog.accessDay<<"-"<<datlog.accessMonth<<"-"<<datlog.accessYear<<" "<<setw(8)<<datlog.clientMethod<<setw(50)<<datlog.requestedResource<<setw(14)<<datlog.protocol<<setw(14);
	if(datlog.serverStatusCode[0]==49)
		out<<"Informational";
	else if(datlog.serverStatusCode[0]==50)
		out<<"Successful";
	else if(datlog.serverStatusCode[0]==51)
		out<<"Redirection";
	else if(datlog.serverStatusCode[0]==52)
		out<<"Client Error";
	else if(datlog.serverStatusCode[0]==53)
		out<<"Server Error";
	out<<setw(14)<<setprecision(0)<<fixed<<datlog.objectSize<<" "<<datlog.pageLink;

	return out;
}

