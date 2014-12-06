/*
 * GroupService.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: kevinyu
 */

#include <fstream>

#include "User/GroupService.h"

GroupService* GroupService::instance = 0;

void GroupService::sendMessage(string groupname,string sender,string message) {
	lock.lock();
	groupPool[groupname].send(sender,message);
	lock.unlock();
}

void GroupService::addUserToGroup(string username, string groupname) {
	lock.lock();
	if (groupPool.find(groupname)!=groupPool.end()){
		groupPool[groupname].addUser(username);
	}
	else {
		lock.unlock();
		throw "Group not created yet";
	}
	lock.unlock();
}

void GroupService::deleteUserFromGroup(string username, string groupname) {
	lock.lock();
	if (groupPool.find(groupname)!=groupPool.end()){
		groupPool[groupname].deleteUser(username);
        updateFileSystem(username,groupname);
	} else {
		lock.unlock();
		throw "Group not created yet";
	}
	lock.unlock();
}

GroupService* GroupService::getInstance() {
	if (instance==0) {
		instance = new GroupService();
	}
	return instance;
}

void GroupService::saveNewGroupToFileSystem(string groupname) {
	FILE *fp = fopen("Group/GroupList","ab+");
	fprintf(fp,"%s\n",groupname.c_str());
	fclose(fp);
}
void GroupService::createGroup(string groupname) {
	lock.lock();
	if (groupPool.find(groupname)==groupPool.end()) {
		Group newGroup;
		newGroup.setGroupId(nextGroupId);
		newGroup.setGroupName(groupname);
		nextGroupId++;
		groupPool[groupname] = newGroup;
		saveNewGroupToFileSystem(groupname);
	}
	else {
            lock.unlock();
		throw "Group have been created before";
	}
	lock.unlock();
}

GroupService::GroupService() {
	nextGroupId = 0;
	loadGroupFromFileSystem();
}

GroupService::~GroupService() {

}

void GroupService::loadGroupFromFileSystem() {
	string fileLocation = "Group/GroupList";
	FILE *fp = fopen(fileLocation.c_str(),"ab+");
	char groupname[1000];
	while (fscanf(fp,"%s\n",groupname)!=EOF) {
		printf("[DEBUG INFO] Group %s loaded\n",groupname);
		Group group;
		group.setGroupName(groupname);
		group.loadUserFromFileSystem();
		groupPool[groupname] = group;
	}
	fclose(fp);
}

void GroupService::updateFileSystem(string username, string groupname) {
    string filepath = "Group/";
    filepath = filepath.append(groupname);
    string filetemp = "Group/temp";
    string currentUserName;
    int numberUser = 0;
    ifstream inputfile (filepath.c_str());
    ofstream outputfile (filetemp.c_str());
    if(inputfile.is_open() && outputfile.is_open())
    {
        while (getline(inputfile,currentUserName))
        {
            if(currentUserName != username)
            {
                outputfile << currentUserName << endl;
                numberUser++;
            }
        }
    }
    inputfile.close();
    outputfile.close();
    remove(filepath.c_str());
    rename(filetemp.c_str(),filepath.c_str());          
    if(numberUser == 0)
    {
    	groupPool.erase(groupname);
        remove(filepath.c_str());
        filepath = "Group/GroupList";
        filetemp = "Group/temp";
        ifstream inputfile(filepath.c_str());
        ofstream outputfile(filetemp.c_str());
        string currentGroupName;
        if(inputfile.is_open()&&outputfile.is_open())
        {
            while(getline(inputfile,currentGroupName))
            {
                if(currentGroupName != groupname)
                {
                    outputfile << currentGroupName << endl;
                }
            }
        }
        inputfile.close();
        outputfile.close();
        remove(filepath.c_str());
        rename(filetemp.c_str(),filepath.c_str());
    }
}
