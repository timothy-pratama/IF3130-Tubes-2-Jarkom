all: Server Client
PROG = Server
INCLUDE = -IHeader
LINKER = -LHeader
SOCKETSRC = Source/Socket
THREADSRC = Source/Thread
USERSRC = Source/User
PACKETSRC = Source/Packet
FILESRC = Source/File
SOCKETHDR = Header/Socket
THREADHDR = Header/Thread
USERHDR = Header/User
FILEHDR = Header/File
PACKETHDR = Header/Packet
OBJS = FileReceiver.o ServerLog.o Group.o GroupService.o Mutex.o ThreadFactory.o UserService.o Condition.o ListenerSocket.o ActiveSocket.o Socket.o ReceiverThread.o Thread.o User.o SenderThread.o packetReceiver.o packetParser.o Packet.o
SERVEROBJS = servers.o Server.o
CLIENTOBJS = clients.o Client.o ClientReceiverThread.o clientUser.o SharedResource.o
PACKETOBJS = finishFilePacket.o filePacket.o partFilePacket.o groupSuccessPacket.o incomingGroupPacket.o joinGroupPacket.o leaveGroupPacket.o broadcastPacket.o incomingPacket.o loginPacket.o registerPacket.o sendPacket.o groupPacket.o logoutPacket.o errorPacket.o successPacket.o

$(PROG) : servers.o Server.o 
	g++ -pthread -o $(PROG) $(LINKER) $(INCLUDE) $(OBJS) $(SERVEROBJS) $(PACKETOBJS)

Client : clients.o Client.o SharedResource.o
	g++ -pthread -o Client $(LINKER) $(INCLUDE) $(OBJS) $(CLIENTOBJS) $(PACKETOBJS)

clients.o : clients.cpp
	g++ -c $(INCLUDE) clients.cpp
	
Client.o : Client.cpp Client.h ActiveSocket.o packetParser.o ClientReceiverThread.o clientUser.o
	g++ -c $(INCLUDE) Client.cpp

ClientReceiverThread.o : FileReceiver.o $(THREADSRC)/ClientReceiverThread.cpp $(THREADHDR)/ClientReceiverThread.h ReceiverThread.o SharedResource.o	
	g++ -c $(INCLUDE) $(THREADSRC)/ClientReceiverThread.cpp
	
SharedResource.o : Source/SharedResource.cpp Header/SharedResource.h Mutex.o
	g++ -c $(INCLUDE) Source/SharedResource.cpp
	
servers.o : servers.cpp
	g++ -c $(INCLUDE) servers.cpp
	
Server.o : Server.cpp Server.h ListenerSocket.o Thread.o User.o
	g++ -c $(INCLUDE) $(LINKER) Server.cpp
	
ListenerSocket.o : $(SOCKETSRC)/ListenerSocket.cpp $(SOCKETHDR)/ListenerSocket.h ActiveSocket.o
	g++ -c $(INCLUDE) $(SOCKETSRC)/ListenerSocket.cpp
	
ActiveSocket.o : $(SOCKETHDR)/ActiveSocket.h $(SOCKETSRC)/ActiveSocket.cpp Socket.o
	g++ -c $(INCLUDE) $(SOCKETSRC)/ActiveSocket.cpp
	
Socket.o : $(SOCKETHDR)/Socket.h $(SOCKETSRC)/Socket.cpp ReceiverThread.o ListenerSocket.o Thread.o
	g++ -c $(INCLUDE) $(LINKER) $(SOCKETSRC)/Socket.cpp
	
ReceiverThread.o : $(THREADSRC)/ReceiverThread.cpp FileReceiver.o ReceiverThread.o Thread.o UserService.o packetReceiver.o packetParser.o $(PACKETOBJS) GroupService.o ServerLog.o
	g++ -c $(INCLUDE) $(THREADSRC)/ReceiverThread.cpp

SenderThread.o : $(THREADHDR)/SenderThread.h $(THREADSRC)/SenderThread.cpp Thread.o Mutex.o Condition.o ActiveSocket.o
	g++ -c $(INCLUDE) $(THREADSRC)/SenderThread.cpp
		
Thread.o : $(THREADHDR)/Thread.h $(THREADSRC)/Thread.cpp
	g++ -c $(INCLUDE) $(THREADSRC)/Thread.cpp

UserService.o : $(USERSRC)/UserService.cpp $(USERHDR)/UserService.h Mutex.o User.o ActiveSocket.o
	g++ -c $(INCLUDE) $(USERSRC)/UserService.cpp
	
User.o : $(USERHDR)/User.h $(USERSRC)/User.cpp SenderThread.o ActiveSocket.o ThreadFactory.o
	g++ -c $(INCLUDE) $(USERSRC)/User.cpp

Condition.o : $(THREADSRC)/Condition.cpp $(THREADHDR)/Condition.h Mutex.o
	g++ -c $(INCLUDE) $(THREADSRC)/Condition.cpp
		
Mutex.o : $(THREADSRC)/Mutex.cpp $(THREADHDR)/Mutex.h
	g++ -c $(INCLUDE) $(THREADSRC)/Mutex.cpp

packetReceiver.o : $(PACKETSRC)/packetReceiver.cpp $(PACKETHDR)/packetReceiver.h
	g++ -c $(INCLUDE)  $(PACKETSRC)/packetReceiver.cpp

packetParser.o : $(PACKETSRC)/packetParser.cpp $(PACKETHDR)/packetParser.h $(PACKETOBJS)
	g++ -c $(INCLUDE) $(PACKETSRC)/packetParser.cpp

broadcastPacket.o :$(PACKETSRC)/broadcastPacket.cpp $(PACKETHDR)/broadcastPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/broadcastPacket.cpp
	
incomingPacket.o : $(PACKETSRC)/incomingPacket.cpp $(PACKETHDR)/incomingPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/incomingPacket.cpp
	
loginPacket.o: $(PACKETSRC)/loginPacket.cpp $(PACKETHDR)/loginPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/loginPacket.cpp
	
registerPacket.o: $(PACKETSRC)/registerPacket.cpp $(PACKETHDR)/registerPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/registerPacket.cpp
	
sendPacket.o: $(PACKETSRC)/sendPacket.cpp $(PACKETHDR)/sendPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/sendPacket.cpp

ThreadFactory.o: $(THREADSRC)/ThreadFactory.cpp $(THREADHDR)/ThreadFactory.h ThreadFactory.o SenderThread.o
	g++ -c $(INCLUDE) $(THREADSRC)/ThreadFactory.cpp
	
Packet.o: $(PACKETSRC)/Packet.cpp
	g++ -c $(INCLUDE) $(PACKETSRC)/Packet.cpp
	
groupPacket.o: $(PACKETSRC)/groupPacket.cpp $(PACKETHDR)/groupPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/groupPacket.cpp

logoutPacket.o: $(PACKETSRC)/logoutPacket.cpp $(PACKETHDR)/logoutPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/logoutPacket.cpp
		
errorPacket.o: $(PACKETSRC)/errorPacket.cpp $(PACKETHDR)/errorPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/errorPacket.cpp

successPacket.o: $(PACKETSRC)/successPacket.cpp $(PACKETHDR)/successPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/successPacket.cpp

joinGroupPacket.o : $(PACKETSRC)/joinGroupPacket.cpp $(PACKETHDR)/joinGroupPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/joinGroupPacket.cpp
	
leaveGroupPacket.o : $(PACKETSRC)/leaveGroupPacket.cpp $(PACKETHDR)/leaveGroupPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/leaveGroupPacket.cpp
	
incomingGroupPacket.o : $(PACKETSRC)/incomingGroupPacket.cpp $(PACKETHDR)/incomingGroupPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/incomingGroupPacket.cpp

groupSuccessPacket.o : $(PACKETSRC)/groupSuccessPacket.cpp $(PACKETHDR)/groupSuccessPacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/groupSuccessPacket.cpp

filePacket.o : $(PACKETSRC)/filePacket.cpp $(PACKETHDR)/filePacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/filePacket.cpp
	
finishFilePacket.o : $(PACKETSRC)/finishFilePacket.cpp $(PACKETHDR)/finishFilePacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/finishFilePacket.cpp
	
partFilePacket.o : $(PACKETSRC)/partFilePacket.cpp $(PACKETHDR)/partFilePacket.h Packet.o
	g++ -c $(INCLUDE) $(PACKETSRC)/partFilePacket.cpp
			
Group.o: $(USERSRC)/Group.cpp $(USERHDR)/Group.h User.o
	g++ -c $(INCLUDE) $(USERSRC)/Group.cpp
	
GroupService.o : $(USERSRC)/GroupService.cpp $(USERHDR)/GroupService.h Group.o Mutex.o
	g++ -c $(INCLUDE) $(USERSRC)/GroupService.cpp
	
clientUser.o : $(USERSRC)/clientUser.cpp $(USERHDR)/clientUser.h
	g++ -c $(INCLUDE) $(USERSRC)/clientUser.cpp
	
ServerLog.o : $(FILESRC)/ServerLog.cpp $(FILEHDR)/ServerLog.h Mutex.o
	g++ -c $(INCLUDE) $(FILESRC)/ServerLog.cpp

FileReceiver.o : $(FILESRC)/FileReceiver.cpp $(FILEHDR)/FileReceiver.h filePacket.o partFilePacket.o finishFilePacket.o
	g++ -c $(INCLUDE) $(FILESRC)/FileReceiver.cpp
clean:
	rm -f *.o
	
