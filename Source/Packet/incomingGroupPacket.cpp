/*
 * incomingGroupPacket.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: kevinyu
 */

#include "Packet/incomingGroupPacket.h"

incomingGroupPacket::incomingGroupPacket() {
	this->code = 'A';
}

incomingGroupPacket::incomingGroupPacket(string username,string groupname,string message) {
	this->code = 'A';
	this->username = username;
	this->groupname = groupname;
	this->message = message;
}

incomingGroupPacket::~incomingGroupPacket() {
	// TODO Auto-generated destructor stub
}

string incomingGroupPacket::getGroupname() const {
	return groupname;
}

void incomingGroupPacket::setGroupname(string groupname) {
	this->groupname = groupname;
}

string incomingGroupPacket::getMessage() const {
	return message;
}

void incomingGroupPacket::setMessage(string message) {
	this->message = message;
}

string incomingGroupPacket::getUsername() const {
	return username;
}

void incomingGroupPacket::setUsername(string username) {
	this->username = username;
}

string incomingGroupPacket::getPacketType() {
	return "incomingGroup";
}

