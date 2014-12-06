/*
 * ServerLog.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#include "File/ServerLog.h"
#include <iostream>
using namespace std;

const string ServerLog::fileLocation = "Log/ServerLog";
ServerLog *ServerLog::instance = 0;

ServerLog::ServerLog() {
	logFilePointer = fopen(fileLocation.c_str(),"ab+");
}

ServerLog::~ServerLog() {
	fclose(logFilePointer);
}

ServerLog *ServerLog::getInstance() {
	if (instance==0){
		instance = new ServerLog();
	}
	return instance;
}

void ServerLog::write(string message) {
	lock.lock();
	time_t result = time(NULL);
	struct tm tm = *localtime(&result);
	sprintf(timeBuffer,"%d-%d-%d %d:%d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min);
	string logMessage(timeBuffer);
	logMessage.append(" ").append(message);
	fprintf(logFilePointer,"%s\n",logMessage.c_str());
        fflush(logFilePointer);
	lock.unlock();
}
