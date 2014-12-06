/* 
 * File:   receivePacket.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 12:46 PM
 */

#include "Packet/registerPacket.h"

registerPacket::registerPacket() {
    code='R';
    username="";
    password="";
}

registerPacket::registerPacket(const registerPacket& orig) {
    this->code = orig.code;
    this->password = orig.password;
    this->username = orig.username;
}

registerPacket::~registerPacket() {
}

registerPacket::registerPacket(string username, string password) {
	this->code = 'R';
    this->username = username;
    this->password = password;
}

void registerPacket::setUsername(string user) {
    this->username = user;
}

void registerPacket::setPassword(string message) {
    this->password = message;
}

void registerPacket::setCode(char code) {
    this->code = code;
}

string registerPacket::getUsername() const {
    return username;
}

string registerPacket::getPassword() const {
    return password;
}

char registerPacket::getCode() const {
    return code;
}

string registerPacket::getPacketType() {
    return "register";
}
