/*
 * Mutex.h
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	void lock();
	void unlock();

protected:
	pthread_mutex_t mutex;
};

#endif /* MUTEX_H_ */
