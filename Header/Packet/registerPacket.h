/* 
 * File:   receivePacket.h
 * Author: timothy
 *
 * Created on November 26, 2014, 12:46 PM
 */

#ifndef RECEIVEPACKET_H
#define	RECEIVEPACKET_H
#include <stdio.h>
#include <string>
#include <iostream>
#include "Packet.h"
using namespace std;

class registerPacket : public Packet{
public:
    //constructor
    registerPacket();
    registerPacket(const registerPacket& orig);
    registerPacket(string message, string user);
    ~registerPacket();
    
    //setter, getter
    char getCode() const;

    void setCode(char code);

    string getPassword() const;

    void setPassword(string message);

    string getUsername() const;

    void setUsername(string user);

    string getPacketType();
    
private:
    char code;
    string username;
    string password;
};

#endif	/* RECEIVEPACKET_H */

