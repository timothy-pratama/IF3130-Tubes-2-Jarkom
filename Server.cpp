/*
 * Server.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#include "Server.h"

Server::Server(string port):listenerSocket(BACKLOG){
	listenerSocket.bindSocket(port);
}

Server::~Server() {

}

void Server::start() {
    ServerLog::getInstance()->write("Server start");
	listenerSocket.startListening();
	bool pertamaKali = true;
	int numberOfSocket = 0;
	ActiveSocket socket[2000];
	UserService::getInstance();
	GroupService::getInstance();
	while (true) {
		socket[numberOfSocket] = listenerSocket.acceptConnection();
		ReceiverThread *thread = new ReceiverThread(&(socket[numberOfSocket]));
		numberOfSocket++;
		thread->start();
		threadList.push_back(thread);
	}
}

