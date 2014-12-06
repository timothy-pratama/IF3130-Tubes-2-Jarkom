/*
 * ListenerThread.h
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#ifndef RECEIVERTHREAD_H_
#define RECEIVERTHREAD_H_

#include "Socket/ActiveSocket.h"
#include "Thread/SenderThread.h"
#include "User/UserService.h"
#include "User/User.h"
#include "Thread/Thread.h"
#include "Packet/packetReceiver.h"
#include "Packet/packetParser.h"
#include <string>
#include "Packet/successPacket.h"
#include "User/GroupService.h"
#include "Packet/incomingGroupPacket.h"
#include "File/ServerLog.h"
#include "File/FileReceiver.h"
#include "Packet/filePacket.h"
#include "Packet/partFilePacket.h"
#include "Packet/finishFilePacket.h"

class ReceiverThread: public Thread{
public:
	ReceiverThread(ActiveSocket *socket);
	virtual void run();
	virtual ~ReceiverThread();

protected:
	virtual void processIncomingMessage(string incomingMessage);

private:
	ActiveSocket *receiverSocket;
	void sendErrorPacket(const char * message);
	void sendSuccessPacket(string message);
	void processLoginPacket(string rawPacket);
	void processLogoutPacket(string rawPacket);
	void processBroadcastPacket(string rawPacket);
	void processGroupPacket(string rawPacket);
	void processRegisterPacket(string rawPacket);
	void processSendPacket(string rawPacket);
	void processJoinGroupPacket(string rawPacket);
	void processLeaveGroupPacket(string rawPacket);
    virtual void overcomeDisconnectedPeer();
	packetReceiver packReceiver;
	string username;
	FileReceiver fileReceiver;
};

#endif /* RECEIVERTHREAD_H_ */
