/* 
 * File:   packetParser.h
 * Author: timothy
 *
 * Created on November 26, 2014, 4:32 PM
 */

#ifndef PACKETPARSER_H
#define	PACKETPARSER_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "Packet/broadcastPacket.h"
#include "Packet/groupPacket.h"
#include "Packet/incomingPacket.h"
#include "Packet/loginPacket.h"
#include "Packet/registerPacket.h"
#include "Packet/sendPacket.h"
#include "Packet/logoutPacket.h"
#include "Packet/successPacket.h"
#include "Packet/errorPacket.h"
#include "Packet/joinGroupPacket.h"
#include "Packet/leaveGroupPacket.h"
#include "Packet/incomingGroupPacket.h"
#include "Packet/groupSuccessPacket.h"
#include "Packet/filePacket.h"
#include "Packet/partFilePacket.h"
#include "Packet/finishFilePacket.h"

using namespace std;

class packetParser {
public:
    //Constructor
    packetParser();
    packetParser(const packetParser& orig);
    ~packetParser();
    
    //Methods
    static string getPacketType(string);
    static broadcastPacket getBroadcastPacket(string);
    static groupPacket getGroupPacket(string);
    static incomingPacket getIncomingPacket(string);
    static loginPacket getLoginPacket(string);
    static registerPacket getRegisterPacket(string);
    static sendPacket getSendPacket(string);
    static logoutPacket getLogoutPacket(string);
    static successPacket getSuccessPacket(string);
    static errorPacket getErrorPacket(string);
    static joinGroupPacket getJoinGroupPacket(string);
    static leaveGroupPacket getLeaveGroupPacket(string);
    static incomingGroupPacket getIncomingGroupPacket(string);
    static groupSuccessPacket getGroupSuccessPacket(string);
    static filePacket getFilePacket(string);
    static finishFilePacket getFinishFilePacket(string);
    static partFilePacket getPartFilePacket(string);
    static string encodePacket(Packet *);
    static vector<string> parseMessage(string);
private:
};

#endif	/* PACKETPARSER_H */

