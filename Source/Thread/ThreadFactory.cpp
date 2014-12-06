/*
 * ThreadFactory.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#include "Thread/ThreadFactory.h"
ThreadFactory *ThreadFactory::instance = 0;

ThreadFactory::ThreadFactory() {

}

ThreadFactory::~ThreadFactory() {
	for (int i=0;i<senderThreadList.size();i++) {
		free (senderThreadList[i]);
	}
}

SenderThread *ThreadFactory::getNewSenderThread(ActiveSocket *socket){
	SenderThread *newSenderThread = new SenderThread(socket);
	senderThreadList.push_back(newSenderThread);
	return newSenderThread;
}

void ThreadFactory::deleteSenderThread(SenderThread *senderThread) {
	vector<SenderThread*>::iterator siterator;
	for (siterator = senderThreadList.begin();siterator!=senderThreadList.end();siterator++){
		if ((*siterator)==senderThread){
			senderThreadList.erase(siterator);
			break;
		}
	}
}

ThreadFactory* ThreadFactory::getInstance() {
	if (instance ==0){
		ThreadFactory::instance = new ThreadFactory();
	}
	return ThreadFactory::instance;
}

