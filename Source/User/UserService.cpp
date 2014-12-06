/*
 * UserService.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#include "User/UserService.h"
UserService* UserService::instance = 0;
UserService::UserService() {
	loadUser();
	mutex = new Mutex();
}

UserService::~UserService() {
	delete mutex;
}

void UserService::sendMessageToUser(string username,string message) {
	mutex->lock();
	if (userPool.find(username)!=userPool.end()) {
		userPool[username].sendMessage(message);
		string logMessage(username);
	}
	else{
            mutex->unlock();
            throw "User does not exist";
	}
	mutex->unlock();
}

void UserService::createUser(string username,string password) {
	if (userPool.find(username)!=userPool.end()) {
		throw "User have been register before";
	}
	else {
		User user;
		user.setUsername(username);
		user.setPassword(password);
                user.setHaveLogin(false);
		userPool[username] =user;
		printf("User with username : %s with password %s have been registered\n",username.c_str(),password.c_str());
		saveNewUserToFileSystem(username,password);
	}
}

UserService* UserService::getInstance() {
	if (UserService::instance==NULL) {
		UserService::instance = new UserService();
	}
	return UserService::instance;
}

void UserService::login(string username,string password,ActiveSocket* socket) {
	if (userPool.find(username)!=userPool.end()) {
		User user = userPool[username];
		if (user.isLogin()){
			throw "User have login";
		}
		else {
			if (user.getPassword()==password){
				userPool[username].login(socket);
				cout<<username<<" have login"<<endl;
			}
			else {
				throw "Wrong password!";
			}
		}
	}
	else{
		throw "User not registered yet";
	}
}

void UserService::logout(string username) {
	userPool[username].logout();
}

void UserService::saveNewUserToFileSystem(string username,string password) {
	string fileLocation = "User/UserList";
	FILE * fp = fopen(fileLocation.c_str(),"ab+");
	fprintf(fp,"%s %s\n",username.c_str(),password.c_str());
	fclose(fp);
}

void UserService::loadUser() {
	string fileLocation = "User/UserList";
	FILE *fp = fopen(fileLocation.c_str(),"ab+");
	char username[1000],password[1000];
	while (fscanf(fp,"%s %s\n",username,password)!=EOF) {
		printf("[DEBUG INFO] %s loaded with password %s\n",username,password);
		User user;
		user.setUsername(string(username));
		user.setPassword(string(password));
		userPool[username] =user;
	}
	fclose(fp);
}
