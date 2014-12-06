/* 
 * File:   incomingPacket.h
 * Author: timothy
 *
 * Created on November 26, 2014, 12:55 PM
 */

#ifndef INCOMINGPACKET_H
#define	INCOMINGPACKET_H
#include <stdio.h>
#include <string>
#include <iostream>
#include "Packet.h"
using namespace std;

class incomingPacket : public Packet{
public:
    //constructor
    incomingPacket();
    incomingPacket(const incomingPacket& orig);
    incomingPacket(string sender, string message);
    ~incomingPacket();
    
    //setter, getter
    char getCode() const;

    void setCode(char code);

    string getMessage() const;

    void setMessage(string message);

    string getSender() const;

    void setSender(string sender);

    string getPacketType();
    
private:
    char code;
    string sender;
    string message;
};

#endif	/* INCOMINGPACKET_H */

