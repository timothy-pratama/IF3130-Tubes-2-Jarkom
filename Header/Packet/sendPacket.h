/* 
 * File:   sendPacket.h
 * Author: timothy
 *
 * Created on November 26, 2014, 12:32 PM
 */

#ifndef SENDPACKET_H
#define	SENDPACKET_H
#include <stdio.h>
#include <string>
#include <iostream>
#include "Packet.h"
using namespace std;

class sendPacket : public Packet{
public:
    //constructor
    sendPacket();
    sendPacket(const sendPacket& orig);
    ~sendPacket();
    sendPacket(string user, string message);
    
    //setter, getter
    char getCode() const;
    void setCode(char code);
    string getMessage() const;
    void setMessage(string message);
    string getUser() const;
    void setUser(string user);
    string getPacketType();

private:
    char code;
    string user;
    string message;
    
};

#endif	/* SENDPACKET_H */

