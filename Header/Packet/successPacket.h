/* 
 * File:   successPacket.h
 * Author: timothy
 *
 * Created on November 29, 2014, 4:39 PM
 */

#ifndef SUCCESSPACKET_H
#define	SUCCESSPACKET_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "Packet.h"
using namespace std;

class successPacket : public Packet {
public:
    successPacket();
    successPacket(string message);
    successPacket(const successPacket& orig);
    ~successPacket();
    char GetCode() const;

    void SetCode(char code);

    string GetMessage() const;

    void SetMessage(string message);

    string getPacketType();
	string getMessage() const;
	void setMessage(string message);
    
private:
    char code;
    int successType; //0=generic;1=createGroup;2=joinGroup
    string message;
    string parameter1;
};

#endif	/* SUCCESSPACKET_H */

