/* 
 * File:   successPacket.cpp
 * Author: timothy
 * 
 * Created on November 29, 2014, 4:39 PM
 */

#include "Packet/successPacket.h"

successPacket::successPacket() {
    code = 'Z';
    message = "";
}

successPacket::successPacket(string message) {
	code = 'Z';
	this->message = message;
}

successPacket::successPacket(const successPacket& orig) {
    code = 'Z';
    message = orig.message;
}

successPacket::~successPacket() {
}

void successPacket::SetMessage(string message) {
    this->message = message;
}

void successPacket::SetCode(char code) {
    this->code = code;
}

string successPacket::GetMessage() const {
    return message;
}

char successPacket::GetCode() const {
    return code;
}

string successPacket::getPacketType() {
    return "success";
}

string successPacket::getMessage() const {
	return message;
}

void successPacket::setMessage(string message) {
	this->message = message;
}


