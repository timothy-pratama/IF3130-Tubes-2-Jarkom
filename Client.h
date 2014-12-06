/*
 * Client.h
 *
 *  Created on: Nov 29, 2014
 *      Author: kevinyu
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
#include <fstream>
#include "Packet/packetParser.h"
#include "Socket/ActiveSocket.h"
#include "Thread/ClientReceiverThread.h"
#include "Header/User/clientUser.h"
#include "User/clientUser.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "SharedResource.h"
#include <stdio.h>
#include <ctime>

using namespace std;

class Client {
public:
	Client();
	virtual ~Client();
	void start();
private:
    clientUser* user;
    ActiveSocket socket;
    void proccessCommandLogin();
    void proccessCommandSignup();
    void proccessCommandMessage();
    void proccessCommandShow();
    void processCommandCreate();
    void processCommandJoin();
    void processCommandLeave();
    void processCommandLogout();
    void processCommandSendFile();
    void showNotification();
    string integerToString(int);
    string createTimestamp(int, int, int, int, int);
};

#endif /* CLIENT_H_ */
