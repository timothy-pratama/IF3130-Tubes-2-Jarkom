/*
 * Client.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: kevinyu
 */

#include "Client.h"

Client::Client() {
    user = new clientUser();
    user->SetLogin(false);
}

Client::~Client() {
    delete user;
}

void Client::start() {
	socket.setUpSocket();
	socket.connectTo("127.0.0.1",31000);
	ClientReceiverThread *receiverThread = new ClientReceiverThread(&socket,user);
        receiverThread->start();
	string command;
	while (true)
        {
            showNotification();
            cout<<"> ";
            cin>>command;
            if (command=="signup"){
                proccessCommandSignup();
            }
            else if (command=="login"){
                proccessCommandLogin();
            }
            else if (command=="message"){
                proccessCommandMessage();
            }
            else if (command=="show")
            {
                proccessCommandShow();
            }
            else if (command=="create")
            {
            	processCommandCreate();
            }
            else if (command=="join")
            {
            	processCommandJoin();
            }
            else if (command=="leave")
            {
            	processCommandLeave();
            }
            else if (command=="logout")
            {
                processCommandLogout();
            }
            else if (command=="sendFile")
            {
                processCommandSendFile();
            }
	}
	socket.closeSocket();
}

void Client::processCommandLogout() {
    if(user->IsLogin())
    {
        Packet * packet = new logoutPacket(user->GetCurrentUsername());
        string rawPacket = packetParser::encodePacket(packet);
        user->SetLogin(false);
        socket.sendMessage(rawPacket);
    }
    else
    {
        cout << "You are not logged in" << endl;
    }
}

void Client::proccessCommandLogin() 
{
    if(user->IsLogin() == false)
    {
        string username,password;
        cout<<"Username :";
        cin>>username;
        cout<<"Password :";
        cin>>password;
        Packet *packet = new loginPacket(username,password);
        string rawPacket = packetParser::encodePacket(packet);
        socket.sendMessage(rawPacket);
        user->SetCurrentUsername(username);
        delete packet;
    }
    else
    {
        cout << "You have already logged in" << endl;
    }
}

void Client::proccessCommandSignup() 
{
    string username,password;
    cout<<"Username :";
    cin>>username;
    cout<<"Password :";
    cin>>password;
    Packet * packet = new registerPacket(username,password);
    string rawPacket = packetParser::encodePacket(packet);
    socket.sendMessage(rawPacket);
    user->SetCurrentUsername(username);
    delete packet;
}

void Client::proccessCommandMessage() {
    if(user->IsLogin())
    {
        string username,message;
        string sender = "";
        Packet *packet;
        
        //Informasi timestamp kirim
        string timestamp;
        int year, month, day, hour, minute;
        time_t t = time(0); // ambil waktu sekarang
        struct tm* timenow = localtime(&t);
        year = timenow->tm_year + 1900;
        month = timenow->tm_mon + 1;
        day = timenow->tm_mday;
        hour = timenow->tm_hour;
        minute = timenow->tm_min;
        timestamp =  createTimestamp(year,month,day,hour,minute);
        sender = sender.append(timestamp);
        
        //Informasi sender
        string extra;
        sender = sender.append(user->GetCurrentUsername());
        sender = sender.append(" : ");
        
        cin >> username;
        cout << "Message : " << endl;
        extra = cin.get();
        getline(cin, message);
        message = message.insert(0,extra);
        if(message != "" && username != "")
        {
            message = message.substr(1,message.length());
            message = message.insert(0,sender);
            
            //periksa apakah username adalah sebuah group
            string currentGroupName;
            string listGroupPath = user->GetCurrentUsername().append("/listgroup");
            bool groupFound = false;
            ifstream listGroup(listGroupPath.c_str());
            if(listGroup.is_open())
            {
                while(getline(listGroup,currentGroupName))
                {
                    if(currentGroupName == username)
                    {
                        groupFound = true;
                        break;
                    }
                }
            }
            if(groupFound)
            {
                packet = new broadcastPacket(username,message);
                string rawPacket = packetParser::encodePacket(packet);
                socket.sendMessage(rawPacket);
                string groupChatPath = user->GetCurrentUsername().append("/").append(username);
                ofstream groupChatFile (groupChatPath.c_str(),ios::app);
                if(groupChatFile.is_open())
                {
                    groupChatFile << message << endl;
                }
                groupChatFile.close();
            }            
            else
            {
                //send sendPacket to server
                packet = new sendPacket(username,message);
                string rawPacket = packetParser::encodePacket(packet);
                socket.sendMessage(rawPacket);
                user->SetUsername(username);

                //update chat history
                string listclientpath;
                string currentUser; //tempat menampung user sementara pada saat baca file.
                bool found = false;

                //cari apakah sudah ada chat history dengan username.
                listclientpath = user->GetCurrentUsername().append("/listclient");
                ifstream listclientfile(listclientpath.c_str());
                if(listclientfile.is_open())
                {
                    while(getline(listclientfile,currentUser))
                    {
                        if(currentUser == username)
                        {
                            found = true;
                            break;
                        }
                    }
                    listclientfile.close();
                    if(found)
                    {
                        // update file yang bersangkutan
                        string chatpath;
                        chatpath = user->GetCurrentUsername().append("/").append(username);
                        ofstream filechat (chatpath.c_str(),ios::app|ios::out);
                        filechat << message << endl;
                        filechat.close();
                    }
                    else // not found
                    {
                        // update file chat history
                        string chatpath;
                        chatpath = user->GetCurrentUsername().append("/").append(username);
                        ofstream filechat (chatpath.c_str());
                        filechat << message << endl;
                        filechat.close();

                        // update file clientlist
                        ofstream clientfile;
                        clientfile.open(listclientpath.c_str(),ios::app|ios::out);
                        clientfile << username << endl;
                        clientfile.close();
                    }
                }
            }
            delete packet;
        }
        else
        {
            cout << "Invalid Message Syntax - target username or message is empty!" << endl;
        }
    }
    else
    {
        string dummy;
        cin >> dummy >> dummy;
        cout << "Login first" << endl;
    }
}

void Client::proccessCommandShow() {
    if(user->IsLogin())
    {
        string name; //baca input dari file
        string username; //nama user yang dicari
        cin >> username;

        //periksa apakah username adalah sebuah group.
        string listGroupPath = user->GetCurrentUsername().append("/listgroup");
        string currentGroupName;
        bool groupFound = false;
        ifstream listGroupFile (listGroupPath.c_str());
        if(listGroupFile.is_open())
        {
            while(getline(listGroupFile,currentGroupName))
            {
                if(currentGroupName == username)
                {
                    groupFound = true;
                    break;
                }
            }
            listGroupFile.close();
        }
        if(groupFound)
        {
            bool foundUnread = false;
            string inputfilename = user->GetCurrentUsername().append("/").append(username);
            string outputfilename = user->GetCurrentUsername().append("/temp");
            string chat;
            ifstream inputfile(inputfilename.c_str());
            ofstream outputfile(outputfilename.c_str());
            if(inputfile.is_open())
            {
                while(getline(inputfile,chat))
                {
                    if(chat == "=")
                    {
                        if(!foundUnread)
                        {
                            cout << "\nNew Message(s) :" << endl;
                            foundUnread = true;
                        }
                    }
                    else
                    {
                        cout << chat << endl;
                        outputfile << chat << endl;
                    }
                }
            }
            inputfile.close();
            outputfile.close();
            remove(inputfilename.c_str());
            rename(outputfilename.c_str(),inputfilename.c_str());
        }
        else
        {
            string chat;
            string filename = user->GetCurrentUsername().append("/listclient");
            ifstream file (filename.c_str());
            if(file.is_open())
            {
                bool found = false;
                while(getline(file,name))
                {
                    if(name == username)
                    {
                        found = true;
                    }
                }
                if(!found)
                {
                    cout << "you have no conversation with " << username << endl;
                }
                else
                {
                    bool foundUnread = false;
                    string inputfilename = user->GetCurrentUsername().append("/").append(username);
                    string outputfilename = user->GetCurrentUsername().append("/temp");
                    ifstream inputfile(inputfilename.c_str());
                    ofstream outputfile(outputfilename.c_str());
                    if(inputfile.is_open())
                    {
                        while(getline(inputfile,chat))
                        {
                            if(chat == "=")
                            {
                                if(!foundUnread)
                                {
                                    cout << "\nNew Message(s) :" << endl;
                                    foundUnread = true;
                                }
                            }
                            else
                            {
                                cout << chat << endl;
                                outputfile << chat << endl;
                            }
                        }
                    }
                    inputfile.close();
                    outputfile.close();
                    remove(inputfilename.c_str());
                    rename(outputfilename.c_str(),inputfilename.c_str());
                }
                file.close();
            }
        }
    }
    else
    {
        string dummy;
        cin >> dummy;
        cout <<"Login first"<< endl;
    }
}

void Client::processCommandCreate() {
	if (user->IsLogin()) {
		string groupname;
		cin>>groupname;
		Packet *packet = new groupPacket(user->GetCurrentUsername(),groupname);
		string rawPacket = packetParser::encodePacket(packet);
		socket.sendMessage(rawPacket);
                user->SetGroupname(groupname);
		delete packet;
	}
}

void Client::processCommandJoin() {
	if (user->IsLogin()) {
		string groupname;
		cin>>groupname;
		Packet *packet = new joinGroupPacket(user->GetCurrentUsername(),groupname);
		string rawPacket = packetParser::encodePacket(packet);
		socket.sendMessage(rawPacket);
                user->SetGroupname(groupname);
		delete packet;
	}
        else
        {
            cout << "You have to login first." << endl;
        }
}

void Client::processCommandLeave() {
	if (user->IsLogin()) {
		string groupname;
		cin>>groupname;
                if(groupname != "")
                {
                    Packet *packet = new leaveGroupPacket(user->GetCurrentUsername(),groupname);
                    string rawPacket = packetParser::encodePacket(packet);
                    socket.sendMessage(rawPacket);
                    user->SetGroupname(groupname);
                    delete packet;
                }
                else
                {
                    cout << "Leave command syntax error - groupname is empty" << endl;
                }
	}
        else
        {
            cout << "You have to login first." << endl;
        }
}

void Client::processCommandSendFile() {
	string filepath,filename,username;
	cout<<"Filepath :";
	cin>>filepath;
	cout<<"Destination Filename :";
	cin>>filename;
	cout<<"Username :";
	cin>>username;
	filePacket filePack;
	filePack.setSenderUsername(user->GetCurrentUsername());
	filePack.setDestinationUsername(username);
	filePack.setFilename(filename);
	Packet *packet = &filePack;
	string rawPacket = packetParser::encodePacket(packet);
	socket.sendMessage(rawPacket);
	int fd = open(filepath.c_str(),O_RDONLY|O_LARGEFILE);
	char buffer[200];
	int nread = 0;
	while((nread = read(fd,buffer,200))>0) {
		partFilePacket pf;
		string buff;
		buff.resize(nread);
		for (int i=0;i<nread;i++) {
			buff[i] = buffer[i];
		}
		pf.setMessage(buff);
		pf.setDestinationUsername(username);
		Packet *pack = &pf;
		string rawPacket = packetParser::encodePacket(pack);
		socket.sendMessage(rawPacket);
	}
	close(fd);
	finishFilePacket ff;
	ff.setUsername(username);
	socket.sendMessage(packetParser::encodePacket((Packet *)&ff));
}


void Client::showNotification() {
    while(SharedResource::getInstance()->isNotificationAvailable())
    {
        cout << SharedResource::getInstance()->getNotification() << endl;
    }
}

string Client::integerToString(int number)
{
    stringstream ss;
    ss << number;
    string temp = ss.str();
    return temp;
}

string Client::createTimestamp(int year, int month, int day, int hour, int minute)
{
    string hasil = "";
    string tahun, bulan, tanggal, jam, menit;
    tahun = integerToString(year);
    bulan = integerToString(month);
    tanggal = integerToString(day);
    jam = integerToString(hour);
    menit = integerToString(minute);
    hasil = hasil.append("[").append(tahun).append("-").append(bulan).append("-").append(tanggal).append(" ").append(jam).append(":").append(menit).append("] ");
    return hasil;
}
