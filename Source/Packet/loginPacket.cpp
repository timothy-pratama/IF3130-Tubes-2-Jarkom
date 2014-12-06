/* 
 * File:   loginPackett.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 12:26 PM
 */

#include "Packet/loginPacket.h"

loginPacket::~loginPacket() {

}


loginPacket::loginPacket() {
    code='L';
    username="";
    password="";
}

loginPacket::loginPacket(const loginPacket& orig) {
    this->code = orig.code;
    this->password = orig.password;
    this->username = orig.username;
}

loginPacket::loginPacket(string username, string password) {
	this->code = 'L';
    this->username = username;
    this->password = password;
}

void loginPacket::setUsername(string username) {
    this->username = username;
}

void loginPacket::setPassword(string password) {
    this->password = password;
}

void loginPacket::setCode(char code) {
    this->code = code;
}

string loginPacket::getUsername() const {
    return username;
}

string loginPacket::getPassword() const {
    return password;
}

char loginPacket::getCode() const {
    return code;
}

string loginPacket::getPacketType() {
    return "login";
}
