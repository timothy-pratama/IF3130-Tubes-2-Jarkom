#ifndef LISTENERSOCKET_H
#define LISTENERSOCKET_H
#include "Socket/ActiveSocket.h"
#include "Socket/Socket.h"

class ListenerSocket : public Socket{
    public:
        ListenerSocket(int backlog);
        virtual ~ListenerSocket();
        void bindSocket(string port);
        void startListening();
        ActiveSocket acceptConnection();
    protected:

    private:
        const int BACKLOG;
};

#endif // LISTENERSOCKET_H

