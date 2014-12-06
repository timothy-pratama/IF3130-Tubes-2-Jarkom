#include "Socket/ActiveSocket.h"

ActiveSocket::ActiveSocket()
{

}

void ActiveSocket::setUpSocket() {

    socketFileDescriptor = socket(AF_INET,SOCK_STREAM,0);
}

ActiveSocket::ActiveSocket(int fileDescriptor){
	socketFileDescriptor = fileDescriptor;
}

void ActiveSocket::connectTo(string ipAddress,int portNumber) {
	struct sockaddr_in destinationAddress;

	memset(&destinationAddress,0,sizeof(struct sockaddr_in));
	inet_pton(AF_INET,ipAddress.c_str(),&(destinationAddress.sin_addr.s_addr));
	destinationAddress.sin_family = AF_INET;
	destinationAddress.sin_port = htons(portNumber);

	connect(socketFileDescriptor,(struct sockaddr *)&destinationAddress,sizeof(struct sockaddr_in));
}

void ActiveSocket::sendMessage(string s) {
	if (s.size()<BUFFER_SIZE) {
		int n = s.size();
		for (int i=0;i<n;i++) {
			outputBuffer[i]=s.c_str()[i];
		}
		for (int totalByteSend = 0 ;totalByteSend <n;) {
			int numberByteSend = send(socketFileDescriptor,outputBuffer+
					totalByteSend,n-totalByteSend,0);
			if (numberByteSend <= 0){
				throw "Error";
			}
			totalByteSend += numberByteSend;
		}
	}
}

string ActiveSocket::receiveMessage(){
    int byteRead = read(socketFileDescriptor,inputBuffer,BUFFER_SIZE-1);
    if ((byteRead==0) || (byteRead==-1)) {
    	throw "Error";
    }
    string input;
    input.resize(byteRead);
    for (int i=0;i<byteRead;i++) {
    	input[i] = inputBuffer[i];
    }
    return input;
}


ActiveSocket::~ActiveSocket()
{

}
