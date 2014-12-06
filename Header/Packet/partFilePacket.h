/* 
 * File:   partFilePacket.h
 * Author: nim_13512080
 *
 * Created on December 3, 2014, 9:03 AM
 */

#ifndef PARTFILEPACKET_H
#define	PARTFILEPACKET_H
#include <string>
#include <iostream>
#include <stdio.h>

#include "Packet.h"
using namespace std;

class partFilePacket : public Packet {
public:
    //constructor
    partFilePacket();
    virtual ~partFilePacket();
    partFilePacket(string message);

    //getter, setter
    char getCode() const;

    void setCode(char code);
    
    string getMessage() const;
    
    void setMessage(string message);
    
    string getPacketType();
	string getDestinationUsername() const;
	void setDestinationUsername(string destinationUsername);

private:
    char code;
    string message;
    string destinationUsername;
};



#endif	/* PARTFILEPACKET_H */

