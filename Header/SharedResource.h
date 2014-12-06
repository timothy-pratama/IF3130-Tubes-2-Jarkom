/* 
 * File:   SharedResource.h
 * Author: timothy
 *
 * Created on December 2, 2014, 9:43 PM
 */

#ifndef SHAREDRESOURCE_H
#define	SHAREDRESOURCE_H
#include <queue>
#include <vector>
#include <string>
#include "Thread/Mutex.h"
#include <iostream>

using namespace std;

class SharedResource {
public:
    SharedResource();
    SharedResource(const SharedResource& orig);
    virtual ~SharedResource();
    static SharedResource *getInstance();
    queue<string> getNotificationQueue();
    void addNotification (string notif);
    string getNotification ();
    bool isNotificationAvailable();
    void addToGroupList(string groupname);
    void deleteFromGroupList(string groupname);
    bool isGroupExist(string groupname);
    void printNotification();
private:
    Mutex groupListLock;
    Mutex notificationLock;
    queue<string> notification;
    vector<string> groupList;
    static SharedResource * instance;
};

#endif	/* SHAREDRESOURCE_H */

