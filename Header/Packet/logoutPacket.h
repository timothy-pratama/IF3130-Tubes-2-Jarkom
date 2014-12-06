/* 
 * File:   logoutPacket.h
 * Author: timothy
 *
 * Created on November 29, 2014, 10:25 AM
 */

#ifndef LOGOUTPACKET_H
#define	LOGOUTPACKET_H
#include <string>
#include <iostream>
#include <stdio.h>

#include "Packet.h"
using namespace std;

class logoutPacket : public Packet {
public:
    //constructor
    logoutPacket();
    logoutPacket(const logoutPacket& orig);
    logoutPacket(string username);
    ~logoutPacket();
    
    //Setter, Getter
    char GetCode() const;
    void SetCode(char code);
    string GetUsername() const;
    void SetUsername(string username);

    virtual string getPacketType();
    
private:
    char code;
    string username;
};

#endif	/* LOGOUTPACKET_H */

