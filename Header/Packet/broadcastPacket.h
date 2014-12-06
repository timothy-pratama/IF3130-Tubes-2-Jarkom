/* 
 * File:   packetFile.h
 * Author: timothy
 *
 * Created on November 26, 2014, 1:36 PM
 */

#ifndef PACKETBROADCAST_H
#define	PACKETBROADCAST_H
#include <string>
#include <iostream>
#include <stdio.h>

#include "Packet.h"
using namespace std;

class broadcastPacket : public Packet {
public:
    //constructor
    broadcastPacket();
    broadcastPacket(const broadcastPacket& orig);
    ~broadcastPacket();
    broadcastPacket(string groupName, string message);

    //getter, setter
    char getCode() const;

    void setCode(char code);

    string getGroupName() const;

    void setGroupName(string groupName);

    string getMessage() const;

    void setMessage(string message);
    
    string getPacketType();

private:
    char code;
    string groupName;
    string message;
};

#endif	/* PACKETBROADCAST_H */

