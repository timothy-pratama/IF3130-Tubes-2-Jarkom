/*
 * groupSuccessPacket.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#include "Packet/groupSuccessPacket.h"

groupSuccessPacket::groupSuccessPacket() {
	// TODO Auto-generated constructor stub
}

groupSuccessPacket::groupSuccessPacket(string groupname) {
	this->groupname = groupname;
}

groupSuccessPacket::~groupSuccessPacket() {
	// TODO Auto-generated destructor stub
}

string groupSuccessPacket::getGroupname() const {
	return groupname;
}

void groupSuccessPacket::setGroupname(string groupname) {
	this->groupname = groupname;
}

string groupSuccessPacket::getPacketType() {
	return "groupSuccess";
}

