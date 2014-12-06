/* 
 * File:   logoutPacket.cpp
 * Author: timothy
 * 
 * Created on November 29, 2014, 10:25 AM
 */

#include "Packet/logoutPacket.h"

logoutPacket::logoutPacket() {
    code = 'E';
    username = "";
}

logoutPacket::logoutPacket(const logoutPacket& orig) {
    this->code = orig.code;
    this->username = orig.username;
}

logoutPacket::logoutPacket(string username) {
    this->code = 'E';
    this->username = username;
}

void logoutPacket::SetUsername(string username) {
    this->username = username;
}

void logoutPacket::SetCode(char code) {
    this->code = code;
}

string logoutPacket::GetUsername() const {
    return username;
}

char logoutPacket::GetCode() const {
    return code;
}


logoutPacket::~logoutPacket() {
}

string logoutPacket::getPacketType() {
    return "logout";
}
