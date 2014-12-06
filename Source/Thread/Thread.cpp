/*
 * Thread.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#include "Thread/Thread.h"

Thread::Thread():started(false),isDetach(false) {

}

Thread::Thread(bool detached):started(false),isDetach(detached){

}

Thread::~Thread(){

}

void Thread::start() {
	if (!started){
		started = true;

		int isError = pthread_create(&tid,NULL,&(Thread::exec),this);
		if (isError==-1) {
			cout<<"Error happen on creating Thread"<<endl;
		}

		if (isDetach){
			pthread_detach(pthread_self());
		}
	}
}

void *Thread::exec(void *arg) {
	reinterpret_cast<Thread*>(arg)->run();
}

void Thread::join() {
	pthread_join(tid,NULL);
}

pthread_t Thread::getThreadId() {
	return tid;
}

