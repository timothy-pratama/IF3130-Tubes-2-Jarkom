/*
 * SenderThread.h
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#ifndef SenderThread_H_
#define SenderThread_H_

#include "Thread/Thread.h"
#include "Thread/Condition.h"
#include "Socket/ActiveSocket.h"
#include <string.h>
#include <vector>

class SenderThread: public Thread {
public:
	SenderThread(ActiveSocket *socket);
	void run();
	virtual ~SenderThread();
	void send(string s);
	void cancel();
private:
	vector<string> sendingQueue;
	Condition *condition;
	ActiveSocket *socket;
	int numberOfBlockingThread;

};

#endif /* SenderThread_H_ */
