/*
 * UserService.h
 *
 *  Created on: Nov 27, 2014
 *      Author: kevinyu
 */

#ifndef USERSERVICE_H_
#define USERSERVICE_H_
#include <vector>
#include <cstdio>
#include <map>
#include "User/User.h"
#include "Thread/Mutex.h"
#include "Socket/ActiveSocket.h"

class User;
class UserService {
public:
	virtual ~UserService();
	void sendMessageToUser(string username,string message);
	void createUser(string username,string password);
	void savePendingMessage(string username,string message);
	void login(string username,string password,ActiveSocket *socket);
	void logout(string username);
	static UserService* getInstance();
private:
	map<string,User> userPool;
	Mutex *mutex;
	UserService();
	static UserService *instance;
	void saveNewUserToFileSystem(string username,string password);
	void loadUser();
};

#endif /* USERSERVICE_H_ */
