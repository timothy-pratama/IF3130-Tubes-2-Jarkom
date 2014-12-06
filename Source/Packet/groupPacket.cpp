/* 
 * File:   groupPacket.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 12:59 PM
 */

#include "Packet/groupPacket.h"

groupPacket::groupPacket() {
    code='G';
    name="";
    creator="";
}

groupPacket::groupPacket(const groupPacket& orig) {
    this->code = orig.code;
    creator = orig.creator;
    name = orig.name;
}

groupPacket::~groupPacket() {
}

groupPacket::groupPacket(string pengirim, string pesan) {
	this->code = 'G';
    this->creator = pengirim;
    this->name = pesan;
}

void groupPacket::setCreator(string creator) {
    this->creator = creator;
}

void groupPacket::setName(string name) {
    this->name = name;
}

void groupPacket::setCode(char code) {
    this->code = code;
}

string groupPacket::getCreator() const {
    return creator;
}

string groupPacket::getName() const {
    return name;
}

char groupPacket::getCode() const {
    return code;
}

string groupPacket::getPacketType() {
    return "group";
}
