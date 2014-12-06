/*
 * Socket.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: kevinyu
 */

#include "Socket/Socket.h"

Socket::Socket() {

}

Socket::~Socket() {

}

void Socket::closeSocket() {
	close(socketFileDescriptor);
}

