/*
 * Mutex.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#include "Thread/Mutex.h"

Mutex::Mutex() {
	pthread_mutex_init(&mutex,NULL);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex);
}

void Mutex::lock() {
	pthread_mutex_lock(&mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&mutex);
}
