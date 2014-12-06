/*
 * ListenerThread.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#include "Thread/ReceiverThread.h"

ReceiverThread::ReceiverThread(ActiveSocket *socket):receiverSocket(socket),Thread(true){
    username = "";
}

ReceiverThread::~ReceiverThread() {

}

void ReceiverThread::run() {
	while(true) {
		try{
              string incomingMessage = receiverSocket->receiveMessage();
              processIncomingMessage(incomingMessage);
		} catch (const char *message) {
              overcomeDisconnectedPeer();
              pthread_exit(0);
		}
	}
}

void ReceiverThread::processIncomingMessage(string incomingMessage) {
	packReceiver.processRawMessage(incomingMessage);
	while (packReceiver.isNextRawPacketAvailable()){
		string rawPacket = packReceiver.getRawPacket();
		string type = packetParser::getPacketType(rawPacket);
		if (type == "register"){
			processRegisterPacket(rawPacket);
		}
		else if (type== "login"){
			processLoginPacket(rawPacket);
		}
		else if (type== "logout"){
			processLogoutPacket(rawPacket);
		}
		else if (type== "send"){
			processSendPacket(rawPacket);
		}
		else if (type== "group"){
			processGroupPacket(rawPacket);
		}
		else if (type=="broadcast") {
			processBroadcastPacket(rawPacket);
		}
		else if (type=="joinGroup") {
			processJoinGroupPacket(rawPacket);
		}
		else if (type=="leaveGroup") {
			processLeaveGroupPacket(rawPacket);
		}
		else if (type=="file") {
			filePacket filePack = packetParser::getFilePacket(rawPacket);
			Packet *pack = &filePack;
			string raw = packetParser::encodePacket(pack);
			UserService::getInstance()->sendMessageToUser(filePack.getDestinationUsername(),raw);
		}
		else if (type=="part_file") {
			partFilePacket partFilePack = packetParser::getPartFilePacket(rawPacket);
			Packet *pack = &partFilePack;
			string raw = packetParser::encodePacket(pack);
			UserService::getInstance()->sendMessageToUser(partFilePack.getDestinationUsername(),raw);
		}
		else if (type=="finishFile") {
			finishFilePacket finishFilePack = packetParser::getFinishFilePacket(rawPacket);
			Packet *pack = &finishFilePack;
			string raw = packetParser::encodePacket(pack);
			UserService::getInstance()->sendMessageToUser(finishFilePack.getUsername(),raw);
		}
	}
}

void ReceiverThread::processRegisterPacket(string rawPacket){
	registerPacket registerPack = packetParser::getRegisterPacket(rawPacket);
	try{
		UserService::getInstance()->createUser(registerPack.getUsername(),registerPack.getPassword());
		sendSuccessPacket("Anda berhasil register");
	}
	catch(const char* errorMessage) {
		sendErrorPacket(errorMessage);
	}
}

void ReceiverThread::processLoginPacket(string rawPacket) {
	loginPacket loginPack = packetParser::getLoginPacket(rawPacket);
	try{
		UserService::getInstance()->login(loginPack.getUsername(),loginPack.getPassword(),receiverSocket);
		username = loginPack.getUsername();
		sendSuccessPacket("Anda berhasil login");
		string logMessage(username);
		logMessage.append(" logged in");
		ServerLog::getInstance()->write(logMessage);
	} catch(const char* errMessage){
		sendErrorPacket(errMessage);
	}
}

void ReceiverThread::processLogoutPacket(string rawPacket) {
	logoutPacket logoutPack = packetParser::getLogoutPacket(rawPacket);
	UserService::getInstance()->logout(logoutPack.GetUsername());
	string logMessage(username);
	logMessage.append(" logged out");
	ServerLog::getInstance()->write(logMessage);
}

void ReceiverThread::processGroupPacket(string rawPacket) {
	groupPacket groupPack = packetParser::getGroupPacket(rawPacket);
	try{
            GroupService::getInstance()->createGroup(groupPack.getName());
            GroupService::getInstance()->addUserToGroup(groupPack.getCreator(),groupPack.getName());
            string logMessage(username);
            logMessage.append(" create group ").append(groupPack.getName());
            ServerLog::getInstance()->write(logMessage);
            Packet *packet = new groupSuccessPacket(groupPack.getName());
            string rawPacket = packetParser::encodePacket(packet);
            receiverSocket->sendMessage(rawPacket);
            delete packet;
	} catch (const char *message) {
		sendErrorPacket(message);
	}
}

void ReceiverThread::processBroadcastPacket(string rawPacket) {
	broadcastPacket broadcastPack = packetParser::getBroadcastPacket(rawPacket);
	Packet *incomingGroupPack = new incomingGroupPacket(username,broadcastPack.getGroupName(),broadcastPack.getMessage());
	string rawPack = packetParser::encodePacket(incomingGroupPack);
	try{
		cout<<"sending to group "<<broadcastPack.getGroupName()<<endl;
		GroupService::getInstance()->sendMessage(broadcastPack.getGroupName(),username,rawPack);
		cout<<"sending finish"<<endl;
		string logMessage(username);
		logMessage.append(" messages ").append(broadcastPack.getGroupName());
		ServerLog::getInstance()->write(logMessage);
	} catch (const char * message) {
		sendErrorPacket(message);
	}
}

void ReceiverThread::processSendPacket(string rawPacket){
	sendPacket sendPack = packetParser::getSendPacket(rawPacket);
	incomingPacket *incomingPack = new incomingPacket(username,sendPack.getMessage());
	string rawPack = packetParser::encodePacket(incomingPack);
	cout << "rawPack = " << rawPack << endl;
	try{
		UserService::getInstance()->sendMessageToUser(sendPack.getUser(),rawPack);
		string logMessage(username);
		logMessage.append(" messages ").append(sendPack.getUser());
		ServerLog::getInstance()->write(logMessage);
	} catch (const char * errMessage) {
		sendErrorPacket(errMessage);
	}
}

void ReceiverThread::processJoinGroupPacket(string rawPacket) {
	joinGroupPacket joinGroupPack = packetParser::getJoinGroupPacket(rawPacket);
	try{
		GroupService::getInstance()->addUserToGroup(joinGroupPack.getSenderUsername(),joinGroupPack.getGroupname());
		string successMessage = "Anda berhasil masuk ke dalam group "+joinGroupPack.getGroupname();
		sendSuccessPacket(successMessage);
		string logMessage(username);
		logMessage.append(" join group ").append(joinGroupPack.getGroupname());
		ServerLog::getInstance()->write(logMessage);
		Packet *packet = new groupSuccessPacket(joinGroupPack.getGroupname());
		string rawPacket = packetParser::encodePacket(packet);
		receiverSocket->sendMessage(rawPacket);
		delete packet;
	} catch(const char * errmessage){
		sendErrorPacket(errmessage);
	}
}

void ReceiverThread::processLeaveGroupPacket(string rawPacket) {
	leaveGroupPacket leaveGroupPack = packetParser::getLeaveGroupPacket(rawPacket);
	try {
		GroupService::getInstance()->deleteUserFromGroup(leaveGroupPack.getUsername(),leaveGroupPack.getGroupname());
		string successMessage = "Anda berhasil meninggalkan group "+leaveGroupPack.getGroupname();
		sendSuccessPacket(successMessage);
		string logMessage(username);
		logMessage.append(" leave group ").append(leaveGroupPack.getGroupname());
		ServerLog::getInstance()->write(logMessage);
	} catch(const char * errmessage) {
		sendErrorPacket(errmessage);
	}
}

void ReceiverThread::sendErrorPacket(const char * errormessage) {
    string message = string (errormessage);
    errorPacket *errorPack = new errorPacket(message);
    string rawPack = packetParser::encodePacket(errorPack);
    receiverSocket->sendMessage(rawPack);
    delete errorPack;
}

void ReceiverThread::sendSuccessPacket(string message) {
    successPacket *successPack = new successPacket(message);
    string rawPack = packetParser::encodePacket(successPack);
    receiverSocket ->sendMessage(rawPack);
    delete successPack;
}

void ReceiverThread::overcomeDisconnectedPeer() {
    if (username!="") {
        UserService::getInstance()->logout(username);
    }
}
