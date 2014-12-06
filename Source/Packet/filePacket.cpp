/* 
 * File:   filePacket.cpp
 * Author: nim_13512080
 *
 * Created on December 2, 2014, 5:30 PM
 */

#include "Packet/filePacket.h"

filePacket::filePacket(){
    code = 'F';
}

filePacket::~filePacket(){
    
}

filePacket::filePacket(int num){
    code = 'F';
}

char filePacket::getCode() const{
    return this->code;
}

void filePacket::setCode(char code){
    this->code = code;
}

string filePacket::getPacketType(){
    return "file";
}

string filePacket::getDestinationUsername() const {
	return destinationUsername;
}

void filePacket::setDestinationUsername(string destinationUsername) {
	this->destinationUsername = destinationUsername;
}

string filePacket::getFilename() const {
	return filename;
}

void filePacket::setFilename(string filename) {
	this->filename = filename;
}

string filePacket::getSenderUsername() const {
	return senderUsername;
}

void filePacket::setSenderUsername(string senderUsername) {
	this->senderUsername = senderUsername;
}


