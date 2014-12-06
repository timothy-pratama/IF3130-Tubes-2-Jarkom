/*
 * Server.h
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <vector>
#include "Thread/Thread.h"
#include "Socket/ListenerSocket.h"
#include "Thread/ReceiverThread.h"
#include "User/User.h"

using namespace std;

class Server {
public:
	Server(string port);
	virtual ~Server();
	void start();

protected:

private:
	vector<Thread*> threadList;
	vector<User> userList;
	ListenerSocket listenerSocket;
	static const int BACKLOG = 50;

};

#endif /* SERVER_H_ */
