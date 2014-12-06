/* 
 * File:   sendPacket.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 12:32 PM
 */

#include "Packet/sendPacket.h"

sendPacket::sendPacket() {
    code='S';
    message="";
    user="";
}

sendPacket::sendPacket(const sendPacket& orig) {
    code=orig.code;
    message=orig.message;
    user=orig.user;
}

sendPacket::sendPacket(string user, string message) {
	this->code = 'S';
    this->user = user;
    this-> message = message;
}


sendPacket::~sendPacket() {
}

void sendPacket::setUser(string user) {
    this->user = user;
}

void sendPacket::setMessage(string message) {
    this->message = message;
}

void sendPacket::setCode(char code) {
    this->code = code;
}

string sendPacket::getUser() const {
    return user;
}

string sendPacket::getMessage() const {
    return message;
}

char sendPacket::getCode() const {
    return code;
}

string sendPacket::getPacketType() {
    return "send";
}
