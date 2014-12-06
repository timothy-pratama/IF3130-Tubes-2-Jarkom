/*
 * FileReceiver.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#include "File/FileReceiver.h"

FileReceiver::FileReceiver() {

}

FileReceiver::~FileReceiver() {

}

void FileReceiver::setDownloadLocation(string downloadLocation) {
	this->downloadLocation = downloadLocation;
}
void FileReceiver::receiveHeader(filePacket filePack) {
	filename = filePack.getFilename();
	string filePath = downloadLocation.append("/").append(filename);
	fileDescriptor = open(filePath.c_str(),O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
	totalByte = 0;
}

void FileReceiver::receivePartFile(partFilePacket filePack) {
	int nread = write(fileDescriptor,filePack.getMessage().c_str(),filePack.getMessage().length());
	totalByte += nread;
}

void FileReceiver::finish() {
	close(fileDescriptor);
}
