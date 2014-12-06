/* 
 * File:   groupPacket.h
 * Author: timothy
 *
 * Created on November 26, 2014, 12:59 PM
 */

#ifndef GROUPPACKET_H
#define	GROUPPACKET_H
#include <stdio.h>
#include <string>
#include <iostream>
#include "Packet.h"
using namespace std;

class groupPacket : public Packet {
public:
    //constructor
    groupPacket();
    groupPacket(const groupPacket& orig);
    groupPacket(string pengirim, string pesan);
    ~groupPacket();
    
    //setter, getter
    char getCode() const;

    void setCode(char code);

    string getName() const;

    void setName(string name);

    string getCreator() const;

    void setCreator(string creator);

    string getPacketType();

private:
    char code;
    string creator;
    string name;
    
};

#endif	/* GROUPPACKET_H */

