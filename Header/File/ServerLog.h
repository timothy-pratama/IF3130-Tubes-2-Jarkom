/*
 * ServerLog.h
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#ifndef SERVERLOG_H_
#define SERVERLOG_H_
#include <string>
#include <ctime>
#include <cstdio>
#include "Thread/Mutex.h"

using namespace std;
class ServerLog {
public:
	ServerLog();
	virtual ~ServerLog();
	static ServerLog * getInstance();
	void write(string logEntry);

private:
	FILE *logFilePointer;
	static const string fileLocation;
	char timeBuffer[100];
	Mutex lock;
	static ServerLog* instance;
};

#endif /* SERVERLOG_H_ */
