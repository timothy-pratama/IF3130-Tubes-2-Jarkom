/* 
 * File:   SharedResource.cpp
 * Author: timothy
 * 
 * Created on December 2, 2014, 9:43 PM
 */

#include "SharedResource.h"

SharedResource *SharedResource::instance = 0;

SharedResource::SharedResource() {
    
}

SharedResource::SharedResource(const SharedResource& orig) {
    
}

SharedResource::~SharedResource() {
    
}

SharedResource* SharedResource::getInstance() { 
    if (instance==0) {
        instance = new SharedResource();
    }
    return instance;
}

queue<string> SharedResource::getNotificationQueue() {
    return notification;
}

void SharedResource::addNotification(string notif) {
    notification.push(notif);
}

string SharedResource::getNotification() {
    string temp = notification.front();
    notification.pop();
    return temp;
}

bool SharedResource::isNotificationAvailable() {
    return (notification.empty() == false);
}

void SharedResource::addToGroupList(string groupname) {
	groupListLock.lock();
	groupList.push_back(groupname);
	groupListLock.unlock();
}

void SharedResource::deleteFromGroupList(string groupname) {
	groupListLock.lock();
	vector<string>::iterator groupListIterator;
	for (groupListIterator=groupList.begin();groupListIterator!=groupList.end();groupListIterator++) {
		if (*groupListIterator==groupname){
			groupList.erase(groupListIterator);
			break;
		}
	}
	groupListLock.unlock();
}

bool SharedResource::isGroupExist(string groupname) {
	vector<string>::iterator groupListIterator;
	for (groupListIterator=groupList.begin();groupListIterator!=groupList.end();groupListIterator++) {
		if (*groupListIterator==groupname){
			return true;
		}
	}
	return false;
}
