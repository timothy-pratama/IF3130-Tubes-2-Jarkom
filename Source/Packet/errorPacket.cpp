/* 
 * File:   errorPacket.cpp
 * Author: timothy
 * 
 * Created on November 29, 2014, 4:46 PM
 */

#include "Packet/errorPacket.h"

errorPacket::errorPacket() {
    code = 'X';
    message = "";
}

errorPacket::errorPacket(string message) {
	code = 'X';
	this->message = message;
}
errorPacket::errorPacket(const errorPacket& orig) {
    code = 'X';
    message = orig.message;
}

errorPacket::~errorPacket() {
}

char errorPacket::GetCode() const {
    return this->code;
}

string errorPacket::getPacketType() {
    return "error";
}

void errorPacket::SetMessage(string message) {
    this->message = message;
}

void errorPacket::SetCode(char code) {
    this->code = code;
}

string errorPacket::GetMessage() const {
    return message;
}
