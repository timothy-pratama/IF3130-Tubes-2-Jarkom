/* 
 * File:   errorPacket.h
 * Author: timothy
 *
 * Created on November 29, 2014, 4:46 PM
 */

#ifndef ERRORPACKET_H
#define	ERRORPACKET_H
#include <string>
using namespace std;
#include "Packet.h"

class errorPacket : public Packet {
public:
    errorPacket();
    errorPacket(const errorPacket& orig);
    errorPacket(string message);
    ~errorPacket();
    char GetCode() const;

    void SetCode(char code);

    string GetMessage() const;

    void SetMessage(string message);


    virtual string getPacketType();

private:
    char code;
    string message;

};

#endif	/* ERRORPACKET_H */

