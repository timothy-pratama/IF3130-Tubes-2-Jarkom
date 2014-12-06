/*
 * leaveGroupPacket.h
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#ifndef LEAVEGROUPPACKET_H_
#define LEAVEGROUPPACKET_H_

#include <string>
#include "Packet/Packet.h"
using namespace std;

class leaveGroupPacket : public Packet{
public:
	leaveGroupPacket();
	leaveGroupPacket(string username,string groupname);
	virtual ~leaveGroupPacket();
	string getGroupname() const;
	void setGroupname(string groupname);
	string getUsername() const;
	void setUsername(string username);
	string getPacketType();
private:
	char code;
	string groupname;
	string username;
};

#endif /* LEAVEGROUPPACKET_H_ */
