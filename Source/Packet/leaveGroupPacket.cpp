/*
 * leaveGroupPacket.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#include "Packet/leaveGroupPacket.h"

leaveGroupPacket::leaveGroupPacket() {
	code = 'T';
}

leaveGroupPacket::leaveGroupPacket(string username,string groupname) {
	code = 'T';
	this->username = username;
	this->groupname = groupname;
}
leaveGroupPacket::~leaveGroupPacket() {

}

string leaveGroupPacket::getGroupname() const {
	return groupname;
}

void leaveGroupPacket::setGroupname(string groupname) {
	this->groupname = groupname;
}

string leaveGroupPacket::getUsername() const {
	return username;
}

void leaveGroupPacket::setUsername(string username) {
	this->username = username;
}

string leaveGroupPacket::getPacketType() {
    return "leaveGroup";
}
