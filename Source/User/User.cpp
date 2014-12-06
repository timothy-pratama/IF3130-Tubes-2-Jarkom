/*
 * User.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#include "User/User.h"

User::User() {

}

User::~User() {

}

string User::getPassword() const {
	return password;
}

void User::setPassword(string password) {
	this->password = password;
}

int User::getUserId() const {
	return userId;
}

void User::setUserId(int userId) {
	this->userId = userId;
}

string User::getUsername() const {
	return username;
}

void User::setUsername(string username) {
	this->username = username;
}

void User::login(ActiveSocket *socket) {
	lock.lock();
	senderThread = ThreadFactory::getInstance()->getNewSenderThread(socket);
	senderThread->start();
	this->haveLogin = true;
	sendPendingMessage();
	lock.unlock();
}

void User::logout() {
	lock.lock();
	this->haveLogin = false;
	senderThread->cancel();
	ThreadFactory::getInstance()->deleteSenderThread(senderThread);
	string logMessage(username);
	logMessage.append(" logged out");
	cout<<username<<" logged out"<<endl;
	ServerLog::getInstance()->write(logMessage);
	lock.unlock();
}

bool User::isLogin() {
	return this->haveLogin;
}

void User::setHaveLogin(bool haveLogin) {
    this->haveLogin = haveLogin;
}

void User::sendMessage(string message){
	lock.lock();
	if (this->haveLogin){
		senderThread->send(message);
	}
	else {
		savePendingMessage(message);
	}
	lock.unlock();
}

void User::savePendingMessage(string message) {
	string fileLocation = "User/" + username;
	FILE * fp = fopen(fileLocation.c_str(),"ab+");
	message = message + "\n";
	fprintf(fp,"%s\n",message.c_str());
	fclose(fp);
}

void User::sendPendingMessage() {
	string fileLocation = "User/"+username;
	FILE *fp = fopen(fileLocation.c_str(),"ab+");
	char message[1024];
	while (fgets(message,1024,fp)!=0) {
		string sendedMessage(message);
		if (sendedMessage.at(0)=='\n') {
			//do nothing
		}
		else if (sendedMessage.at(sendedMessage.length()-1)=='\n') {
			sendedMessage = sendedMessage.substr(0,sendedMessage.length()-1);
			cout<<"[DEBUG INFO] send pending message ("<<sendedMessage<<")to "<<username<<endl;
			senderThread->send(sendedMessage);
		}


	}
	freopen(fileLocation.c_str(),"w",fp);
	fclose(fp);
}

