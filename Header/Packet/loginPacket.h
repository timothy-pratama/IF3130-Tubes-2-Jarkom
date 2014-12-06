/* 
 * File:   loginPackett.h
 * Author: timothy
 *
 * Created on November 26, 2014, 12:26 PM
 */

#ifndef LOGINPACKETT_H
#define	LOGINPACKETT_H
#include <iostream>
#include <string>
#include <stdio.h>
#include "Packet.h"
using namespace std;

class loginPacket : public Packet{
public:
    //constructor, destructor
    loginPacket();
    loginPacket(const loginPacket& orig);
    loginPacket(string username, string password);
    ~loginPacket();
    
    //setter, getter
    char getCode() const;

    void setCode(char code);

    string getPassword() const;

    void setPassword(string password);

    string getUsername() const;

    void setUsername(string username);

    string getPacketType();
    
private:
    char code;
    string username;
    string password;
};

#endif	/* LOGINPACKETT_H */

