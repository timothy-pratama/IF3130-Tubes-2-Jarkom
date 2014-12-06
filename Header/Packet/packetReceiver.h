/* 
 * File:   packetReceiver.h
 * Author: timothy
 *
 * Created on November 29, 2014, 11:48 AM
 */

#ifndef PACKETRECEIVER_H
#define	PACKETRECEIVER_H
#include <queue>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


class packetReceiver {
public:
    packetReceiver();
    packetReceiver(const packetReceiver& orig);
    virtual ~packetReceiver();
    void processRawMessage(string rawMessage); //process the raw message, if the packet is complete, send it to output queue.
    string getRawPacket(); //retrieve the message from output queue.
    bool isNextRawPacketAvailable(); //return if there is at least 1 packet in the output queue.
        
private:
    int state; /* 1 = getCurrentNumber
                * 2 = finish getCurrentNumber
                * 3 = getCurrentMessage
                * 4 = finish getCurrentMessage */
    string intermediateBuffer;
    queue<string> output;
    int currentNumber;
};

#endif	/* PACKETRECEIVER_H */

