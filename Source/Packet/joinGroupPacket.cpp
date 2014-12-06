/*
 * joinGroupPacket.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: kevinyu
 */

#include "Packet/joinGroupPacket.h"

joinGroupPacket::joinGroupPacket() {
	code='J';
}

joinGroupPacket::joinGroupPacket(string username,string groupname) {
	code='J';
	this->senderUseraname = username;
	this->groupname = groupname;
}
joinGroupPacket::~joinGroupPacket() {

}

string joinGroupPacket::getGroupname() const {
	return groupname;
}

void joinGroupPacket::setGroupname(string groupname) {
	this->groupname = groupname;
}

string joinGroupPacket::getSenderUsername() const {
	return senderUseraname;
}

void joinGroupPacket::setSenderUsername(string senderUseraname) {
	this->senderUseraname = senderUseraname;
}

string joinGroupPacket::getPacketType() {
	return "joinGroup";
}


