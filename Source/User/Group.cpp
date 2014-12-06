/*
 * Group.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#include "User/Group.h"

Group::Group() {

}

Group::~Group() {
	userList.clear();
}

void Group::addUser(string username) {
	lock.lock();
	cout<<"[DEBUG INFO] add user "<<username<<" to "<<groupName<<endl;
	userList.push_back(username);
	addUserToFileSystem(username);
	lock.unlock();
}

void Group::deleteUser(string username) {
	lock.lock();
	vector<string>::iterator userListIterator;
	for (userListIterator=userList.begin();userListIterator!=userList.end();userListIterator++) {
		if ((*userListIterator)==username) {
			break;
		}
	}
	if (userListIterator==userList.end()) {
		lock.unlock();
		throw "User not found";
	}
	else {
		cout<<"delete user "<<username<<" from "<<groupName<<endl;
		userList.erase(userListIterator);
	}
	lock.unlock();
}

void Group::send(string sender,string message) {
	lock.lock();
	for (int i=0;i<userList.size();i++) {
		if (userList[i]!=sender) {
			cout<<sender<<" send message to "<<userList[i]<<" "<<message<<endl;
			UserService::getInstance()->sendMessageToUser(userList[i],message);
		}
	}
	lock.unlock();
}

int Group::getGroupId() const {
	return groupId;
}

void Group::setGroupId(int groupId) {
	this->groupId = groupId;
}

string Group::getGroupName() const {
	return groupName;
}

void Group::setGroupName(string groupName) {
	this->groupName = groupName;
}

void Group::addUserToFileSystem(string username) {
	string fileLocation = "Group/"+groupName;
	FILE *fp = fopen(fileLocation.c_str(),"ab+");
	fprintf(fp,"%s\n",username.c_str());
	cout<<"[DEBUG INFO] "<<username<<" flush to filesystem"<<endl;
	fclose(fp);
}

void Group::loadUserFromFileSystem() {
	string fileLocation = "Group/"+groupName;
	char username[1024];
	FILE *fp = fopen(fileLocation.c_str(),"ab+");
	while (fscanf(fp,"%s\n",username)!=EOF) {
		cout<<"[DEBUG INFO] load "<<username<<" to "<<groupName<<endl;
		userList.push_back(string(username));
	}
	fclose(fp);
}

