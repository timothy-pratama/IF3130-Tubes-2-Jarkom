/*
 * incomingGroupPacket.h
 *
 *  Created on: Dec 3, 2014
 *      Author: kevinyu
 */

#ifndef INCOMINGGROUPPACKET_H_
#define INCOMINGGROUPPACKET_H_

#include "Packet/Packet.h"
#include <string>
using namespace std;

class incomingGroupPacket:public Packet{
public:
	incomingGroupPacket();
	incomingGroupPacket(string username,string groupname,string message);
	virtual ~incomingGroupPacket();
	string getGroupname() const;
	void setGroupname(string groupname);
	string getMessage() const;
	void setMessage(string message);
	string getUsername() const;
	void setUsername(string username);
	string getPacketType();
private:
	char code;
	string groupname;
	string username;
	string message;
};

#endif /* INCOMINGGROUPPACKET_H_ */
