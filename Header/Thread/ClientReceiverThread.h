/*
 * ClientReceiverThread.h
 *
 *  Created on: Nov 29, 2014
 *      Author: kevinyu
 */

#ifndef CLIENTRECEIVERTHREAD_H_
#define CLIENTRECEIVERTHREAD_H_
#include "Thread/ReceiverThread.h"
#include "User/clientUser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include "SharedResource.h"
#include <iostream>
using namespace std;

class ClientReceiverThread : public ReceiverThread{
public:
	ClientReceiverThread(ActiveSocket *socket, clientUser *user);
	virtual ~ClientReceiverThread();
private:
	void processIncomingMessage(string message);
        packetReceiver packReceiver;
        clientUser *user;
        void processIncomingPacket(string);
        void processErrorPacket(string);
        void processSuccessPacket(string);
        void processIncomingGroupPacket(string);
        void processGroupSuccessPacket(string);
        void overcomeDisconnectedPeer();
        FileReceiver fileReceiver;
};

#endif /* CLIENTRECEIVERTHREAD_H_ */
