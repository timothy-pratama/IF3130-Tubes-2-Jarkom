/*
 * Socket.h
 *
 *  Created on: Nov 26, 2014
 *      Author: kevinyu
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;
class Socket {
public:
	Socket();
	virtual ~Socket();
	void closeSocket();

	int getSocketFileDescriptor() const {
		return socketFileDescriptor;
	}

	void setSocketFileDescriptor(int socketFileDescriptor) {
		this->socketFileDescriptor = socketFileDescriptor;
	}

protected:
	int socketFileDescriptor;
private:

};

#endif /* SOCKET_H_ */
