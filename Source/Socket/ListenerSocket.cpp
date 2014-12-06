#include "Socket/ListenerSocket.h"

ListenerSocket::ListenerSocket(int backlog) : BACKLOG(backlog)
{

}

void ListenerSocket::bindSocket(string port)
{
    struct addrinfo * result;
    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE|AI_NUMERICSERV;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(NULL,port.c_str(),&hints,&result);
    struct addrinfo *currentResult;
    for (currentResult=result;currentResult!=NULL;currentResult = currentResult->ai_next) {
        socketFileDescriptor = socket(currentResult->ai_family,currentResult->ai_socktype,currentResult->ai_protocol);
        if (socketFileDescriptor==-1) {
            continue;
        }

        int option = 1;
        setsockopt(socketFileDescriptor,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(int));

        if (bind(socketFileDescriptor,currentResult->ai_addr,currentResult->ai_addrlen)==0){
            break;
        }
        close(socketFileDescriptor);
    }

    freeaddrinfo(currentResult);
}

void ListenerSocket::startListening() {
    listen(socketFileDescriptor,BACKLOG);
}

ActiveSocket ListenerSocket::acceptConnection(){
    sockaddr_in clientAddress;
    socklen_t addressSize = sizeof(struct sockaddr_storage);
    int clientFileDescriptor = accept(socketFileDescriptor,(struct sockaddr *)&clientAddress,&addressSize);
    ActiveSocket clientSocket(clientFileDescriptor);
    return clientSocket;
}


ListenerSocket::~ListenerSocket()
{

}

