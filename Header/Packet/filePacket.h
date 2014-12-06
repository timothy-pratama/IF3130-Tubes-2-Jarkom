/* 
 * File:   filePacket.h
 * Author: nim_13512080
 *
 * Created on December 2, 2014, 5:30 PM
 */

#ifndef FILEPACKET_H
#define	FILEPACKET_H
#include <string>
#include <iostream>
#include <stdio.h>

#include "Packet.h"
using namespace std;

class filePacket : public Packet {
public:
    //constructor
    filePacket();
    ~filePacket();
    filePacket(int num); //parameternya apa?

    //getter, setter
    char getCode() const;

    void setCode(char code);
    
    int getNumOfPacket() const;
    
    void setNumOfPacket(int num);
    
    string getPacketType();
	string getDestinationUsername() const;
	void setDestinationUsername(string destinationUsername);
	string getFilename() const;
	void setFilename(string filename);
	string getSenderUsername() const;
	void setSenderUsername(string senderUsername);

private:
    char code;
    string senderUsername;
    string destinationUsername;
    string filename;
};


#endif	/* FILEPACKET_H */

