/* 
 * File:   incomingPacket.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 12:55 PM
 */

#include "Packet/incomingPacket.h"

incomingPacket::incomingPacket() {
    code='I';
    sender = "";
    message = "";
}

incomingPacket::incomingPacket(const incomingPacket& orig) {
    code = orig.code;
    sender = orig.sender;
    message = orig.message;
}

incomingPacket::~incomingPacket() {
}

incomingPacket::incomingPacket(string sender, string message) {
    this->code = 'I';
    this->sender = sender;
    this->message = message;
}

void incomingPacket::setSender(string sender) {
    this->sender = sender;
}


void incomingPacket::setMessage(string message) {
    this->message = message;
}

void incomingPacket::setCode(char code) {
    this->code = code;
}

string incomingPacket::getSender() const {
    return sender;
}

string incomingPacket::getMessage() const {
    return message;
}

char incomingPacket::getCode() const {
    return code;
}

string incomingPacket::getPacketType() {
    return "incoming";
}
