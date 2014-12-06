/* 
 * File:   partFilePacket.cpp
 * Author: nim_13512080
 *
 * Created on December 4, 2014, 2:05 PM
 */

#include "Packet/filePacket.h"
#include "Packet/partFilePacket.h"

partFilePacket::partFilePacket(){
    code = 'V';
    message = "";
}

partFilePacket::~partFilePacket(){
    
}

partFilePacket::partFilePacket(string message){
    code = 'V';
    this->message = message;
}

char partFilePacket::getCode() const{
    return this->code;
}

void partFilePacket::setCode(char code){
    this->code = code;
}

string partFilePacket::getMessage() const{
    return this->message;
}

void partFilePacket::setMessage(string message){
    this->message = message;
}

string partFilePacket::getPacketType(){
    return "part_file";
}

string partFilePacket::getDestinationUsername() const {
	return destinationUsername;
}

void partFilePacket::setDestinationUsername(string destinationUsername) {
	this->destinationUsername = destinationUsername;
}

