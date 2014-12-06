#ifndef ACTIVESOCKET_H
#define ACTIVESOCKET_H
#include "Socket/Socket.h"
#define BUFFER_SIZE 1024


class ActiveSocket : public Socket{
    public:
        ActiveSocket();
        ActiveSocket(int fileDescriptor);
        void connectTo(string ipAddress,int portNumber);
        void sendMessage(string s);
        string receiveMessage();
        virtual ~ActiveSocket();
        void setUpSocket();
    protected:
    private:
        char inputBuffer[BUFFER_SIZE];
        char outputBuffer[BUFFER_SIZE];
};

#endif // ACTIVESOCKET_H
