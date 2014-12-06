/* 
 * File:   Packet.h
 * Author: timothy
 *
 * Created on November 26, 2014, 2:57 PM
 */

#ifndef PACKET_H
#define	PACKET_H
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Packet {
public:
    Packet();
    Packet(const Packet& orig);
    ~Packet();
    virtual string getPacketType() = 0;
private:
    string code;
};

#endif	/* PACKET_H */

