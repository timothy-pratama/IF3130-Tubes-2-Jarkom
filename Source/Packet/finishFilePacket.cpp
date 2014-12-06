/*
 * finishFilePacket.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#include "Packet/finishFilePacket.h"

finishFilePacket::finishFilePacket() {
	code = 'W';
}

finishFilePacket::~finishFilePacket() {
	// TODO Auto-generated destructor stub
}

string finishFilePacket::getPacketType() {
	return "finishFile";
}

string finishFilePacket::getUsername() const {
	return username;
}

void finishFilePacket::setUsername(string username) {
	this->username = username;
}

