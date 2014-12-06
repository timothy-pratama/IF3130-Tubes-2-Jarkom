/*
 * SenderThread.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#include "Thread/SenderThread.h"

SenderThread::SenderThread(ActiveSocket *socket):Thread(true){
	this->socket = socket;
	condition = new Condition();
}

SenderThread::~SenderThread() {
	delete condition;
}

void SenderThread::run() {
	while (true){
		condition->lock();
		while(sendingQueue.size()==0) {
			condition->wait();
		}
		printf("%d\n",socket->getSocketFileDescriptor());
		for (int i=0;i<sendingQueue.size();i++) {
			cout<<"[DEBUG INFO] send packet"<<sendingQueue[i]<<endl;
			socket->sendMessage(sendingQueue[i]);
		}
		sendingQueue.clear();
		condition->unlock();
		pthread_testcancel();
	}
}

void SenderThread::send(string s) {
	condition->lock();
	sendingQueue.push_back(s);
	condition->unlock();
	condition->notify();
}

void SenderThread::cancel() {
	pthread_cancel(tid);
}


