/*
 * finishFilePacket.h
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#ifndef FINISHFILEPACKET_H_
#define FINISHFILEPACKET_H_
#include "Packet/Packet.h"
class finishFilePacket:public Packet {
public:
	finishFilePacket();
	virtual ~finishFilePacket();
	string getPacketType();
	string getUsername() const;
	void setUsername(string username);
private:
	char code;
	string username;
};

#endif /* FINISHFILEPACKET_H_ */
