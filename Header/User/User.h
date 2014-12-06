/*
 * User.h
 *
 *  Created on: Nov 25, 2014
 *      Author: kevinyu
 */

#ifndef USER_H_
#define USER_H_

#include "Thread/SenderThread.h"
#include "Thread/ReceiverThread.h"
#include "Thread/ThreadFactory.h"
#include <string>
using namespace std;

class User {
public:
    User();
    virtual ~User();

    //getter and setter
    string getPassword() const;
    void setPassword(string password);
    int getUserId() const;
    void setUserId(int userId);
    string getUsername() const;
    void setUsername(string username);
    void login(ActiveSocket *socket);
    void logout();
    bool isLogin();
    void sendMessage(string s);
    void setSenderThread(SenderThread *senderThread);
    SenderThread* getSenderThread() const;
    void setHaveLogin(bool haveLogin);

private:
	int userId;
	string username;
	string password;
	bool haveLogin;
	SenderThread* senderThread;
	void savePendingMessage(string message);
	void sendPendingMessage();
	Condition lock;
};

#endif /* USER_H_ */
