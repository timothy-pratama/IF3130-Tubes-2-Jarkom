/*
 * Thread.h
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
using namespace std;

class Thread {
	public:
		Thread();
		Thread(bool isDetach);
		virtual ~Thread();

		void start();
		void join();
		pthread_t getThreadId();
		virtual void run() =0;

	protected:
		pthread_t tid;

	private:
		bool started;
		bool isDetach;
		static void* exec(void *arg);
};

#endif /* THREAD_H_ */
