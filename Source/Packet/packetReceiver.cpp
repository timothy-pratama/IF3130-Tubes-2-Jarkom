/* 
 * File:   packetReceiver.cpp
 * Author: timothy
 * 
 * Created on November 29, 2014, 11:48 AM
 */

#include "Packet/packetReceiver.h"

packetReceiver::packetReceiver() {
    /* 1 = getCurrentNumber
     * 2 = finish getCurrentNumber
     * 3 = getCurrentMessage
     * 4 = finish getCurrentMessage */
    state = 1;
    intermediateBuffer = "";
    currentNumber = 0;
}

packetReceiver::packetReceiver(const packetReceiver& orig) {
    intermediateBuffer = orig.intermediateBuffer;
    output = orig.output;
    state = orig.state;
}

packetReceiver::~packetReceiver() {
}

bool packetReceiver::isNextRawPacketAvailable() {
    return (output.size() > 0);
}

string packetReceiver::getRawPacket() {
    string result = output.front();
    output.pop();
    return result;
}

void packetReceiver::processRawMessage(string rawMessage) {
    int rawMessageLength = rawMessage.length();
    int i = 0;
    while(i < rawMessageLength)
    {
        if(state == 1) //getCurrentNumber
        {
            //Looking for ';'
            while (rawMessage.at(i) != ';' )
            {
                intermediateBuffer += rawMessage.at(i);
                if(i<rawMessageLength)
                i++;
                if(i == rawMessageLength)
                {
                    break;
                }
            }
            //Change to state 2 if find ';'.
            if(i < rawMessageLength)
            {
                if(rawMessage.at(i) == ';')
                {
                    state = 2;
                }
            }
        }
        if(state == 2) // finish reading current number 
        {
            currentNumber = atoi(intermediateBuffer.c_str());
            i++;
            intermediateBuffer = "";
            state = 3;
        }
        if(state == 3) // start reading current packet
        {
            while (i < rawMessageLength && currentNumber > 0)
            {
                intermediateBuffer += rawMessage.at(i);
                i++;
                currentNumber--;
            }
            if(currentNumber == 0)
            {
                state = 4;
            }
        }
        if(state == 4) // finish reading current packet
        {
            output.push(intermediateBuffer);
            state = 1;
            intermediateBuffer = "";
        }
    }
}

