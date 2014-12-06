/*
 * FileReceiver.h
 *
 *  Created on: Dec 4, 2014
 *      Author: kevinyu
 */

#ifndef FILERECEIVER_H_
#define FILERECEIVER_H_
#include "Packet/filePacket.h"
#include "Packet/partFilePacket.h"
#include "Packet/finishFilePacket.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

using namespace std;

class FileReceiver {
public:
	FileReceiver();
	virtual ~FileReceiver();
	void receiveHeader(filePacket filePack);
	void receivePartFile(partFilePacket partPack);
	void setDownloadLocation(string downloadLocation);
	void finish();
private:
	int numberPacketOfCurrentReceivedFile;
	string filename;
	string downloadLocation;
	int fileDescriptor;
	int totalByte;
};

#endif /* FILERECEIVER_H_ */
