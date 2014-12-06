/*
 * Condition.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#include "Thread/Condition.h"

Condition::Condition() {
	pthread_cond_init(&cond,NULL);
}

Condition::~Condition() {
	pthread_cond_destroy(&cond);
}

void Condition::wait() {
	pthread_cond_wait(&cond,&mutex);
}

void Condition::notify() {
	pthread_cond_signal(&cond);
}



