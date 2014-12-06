/* 
 * File:   packetFile.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 1:36 PM
 */

#include "Packet/broadcastPacket.h"

broadcastPacket::broadcastPacket(const broadcastPacket& orig) {
    code = orig.code;
    groupName = orig.groupName;
    message = orig.message;
}

broadcastPacket::~broadcastPacket() {

}

broadcastPacket::broadcastPacket(string groupName, string message) :
code('B'), groupName(groupName), message(message) {
}

broadcastPacket::broadcastPacket() {
    code = 'B';
    groupName = "";
    message = "";
}

string broadcastPacket::getPacketType() {
    return "broadcast";
}

void broadcastPacket::setMessage(string message) {
    this->message = message;
}

void broadcastPacket::setGroupName(string groupName) {
    this->groupName = groupName;
}

void broadcastPacket::setCode(char code) {
    this->code = code;
}

string broadcastPacket::getMessage() const {
    return message;
}

string broadcastPacket::getGroupName() const {
    return groupName;
}

char broadcastPacket::getCode() const {
    return code;
}
