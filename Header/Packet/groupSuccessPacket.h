/*
 * groupSuccessPacket.h
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#ifndef GROUPSUCCESSPACKET_H_
#define GROUPSUCCESSPACKET_H_
#include <string>
#include "Packet/Packet.h"
using namespace std;
class groupSuccessPacket : public Packet{
public:
	groupSuccessPacket();
	groupSuccessPacket(string groupname);
	virtual ~groupSuccessPacket();
	string getGroupname() const;
	void setGroupname(string groupname);
	string getPacketType();
private:
	char code;
	string groupname;
};

#endif /* GROUPSUCCESSPACKET_H_ */
