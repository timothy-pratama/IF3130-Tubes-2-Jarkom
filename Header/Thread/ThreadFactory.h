/*
 * ThreadFactory.h
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#ifndef THREADFACTORY_H_
#define THREADFACTORY_H_

#include "Socket/ActiveSocket.h"
#include "Thread/SenderThread.h"
#include <vector>
using namespace std;

class ThreadFactory {
public:
	virtual ~ThreadFactory();
	SenderThread *getNewSenderThread(ActiveSocket *socket);
	void deleteSenderThread(SenderThread *senderThread);
	static ThreadFactory* getInstance();
private:
	ThreadFactory();
	vector<SenderThread*> senderThreadList;
	static ThreadFactory *instance;
};

#endif /* THREADFACTORY_H_ */
