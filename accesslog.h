/*
 * accesslog.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Alex
 */

#ifndef ACCESSLOG_H_
#define ACCESSLOG_H_
#include <string>

using namespace std;
class AccessLog
{
	friend istream& operator >>(istream&, AccessLog&);
	friend ostream& operator <<(ostream&, const AccessLog&);
	private:
	string clientIp, clientMethod;
	string requestedResource, protocol, pageLink;
	string accessMonth, serverStatusCode;
	int accessDay, accessYear;
	double objectSize;

	public:
	AccessLog();
	bool operator >(const AccessLog&)const;
};




#endif /* ACCESSLOG_H_ */
