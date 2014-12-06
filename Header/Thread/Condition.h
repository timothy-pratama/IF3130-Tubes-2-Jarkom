/*
 * Condition.h
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "Thread/Mutex.h"
#include <cstddef>

class Condition : public Mutex{
public:
	Condition();
	virtual ~Condition();
	void wait();
	void notify();
protected:
	pthread_cond_t cond;
};

#endif /* CONDITION_H_ */
