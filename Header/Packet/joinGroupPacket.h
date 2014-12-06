/*
 * joinGroupPacket.h
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#ifndef JOINGROUPPACKET_H_
#define JOINGROUPPACKET_H_

#include<string>
#include "Packet/Packet.h"

using namespace std;
class joinGroupPacket : public Packet{
public:
	joinGroupPacket();
	joinGroupPacket(string username,string groupname);
	virtual ~joinGroupPacket();
	string getGroupname() const;
	void setGroupname(string groupname);
	string getSenderUsername() const;
	void setSenderUsername(string senderUseraname);
	string getPacketType();
private:
	char code;
	string senderUseraname;
	string groupname;
};

#endif /* JOINGROUPPACKET_H_ */
