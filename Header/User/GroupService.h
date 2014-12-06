/*
 * GroupService.h
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#ifndef GROUPSERVICE_H_
#define GROUPSERVICE_H_

#include <map>
#include <utility>
#include "Thread/Mutex.h"
#include "User/Group.h"
using namespace std;

class Group;
class GroupService {
public:
	virtual ~GroupService();
	void sendMessage(string groupname,string sender,string message);
	void addUserToGroup(string username,string groupname);
	void deleteUserFromGroup(string username,string groupname);
	void createGroup(string groupname);
	static GroupService* getInstance();

private:
	static GroupService *instance;
	GroupService();
	GroupService(const GroupService&);
	const GroupService& operator=(const GroupService&);
    map<string,Group> groupPool;
	Mutex lock;
	void saveNewGroupToFileSystem(string groupname);
	void loadGroupFromFileSystem();
	int nextGroupId;
        void updateFileSystem(string,string);
};

#endif /* GROUPSERVICE_H_ */
