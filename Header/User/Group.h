/*
 * Group.h
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#ifndef GROUP_H_
#define GROUP_H_

#include <string>
#include "User/User.h"
#include <iostream>
using namespace std;

class Group {
public:
	Group();
	virtual ~Group();
	void addUser(string username);
	void deleteUser(string username);
	void send(string sender,string message);
	int getGroupId() const;
	void setGroupId(int groupId);
	string getGroupName() const;
	void setGroupName(string groupName);
	void loadUserFromFileSystem();

private:
	void addUserToFileSystem(string username);
	int groupId;
	string groupName;
	vector<string> userList;
	Mutex lock;

};

#endif /* GROUP_H_ */
