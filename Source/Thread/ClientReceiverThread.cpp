/*
 * ClientReceiverThread.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: kevinyu
 */

#include "Thread/ClientReceiverThread.h"
#include "User/clientUser.h"

string MARKER ="=";

ClientReceiverThread::ClientReceiverThread(ActiveSocket *socket, clientUser *user):ReceiverThread(socket) {
    this->user = user;
}

ClientReceiverThread::~ClientReceiverThread() {

}

void ClientReceiverThread::processIncomingMessage(string message) {
    packReceiver.processRawMessage(message);
    while(packReceiver.isNextRawPacketAvailable())
    {
        string rawPacket = packReceiver.getRawPacket();
        string type = packetParser::getPacketType(rawPacket);
        if(type=="success")
        {
            processSuccessPacket(rawPacket);
        }
        if(type == "error")
        {
            processErrorPacket(rawPacket);
        }
        if(type =="incoming")
        {
            processIncomingPacket(rawPacket);
        }
        if (type=="incomingGroup")
        {
            processIncomingGroupPacket(rawPacket);
        }
        if (type=="groupSuccess")
        {
            processGroupSuccessPacket(rawPacket);
        }
        else if (type=="file") {
			fileReceiver.setDownloadLocation(user->GetCurrentUsername().append("/Downloads"));
			filePacket filePack = packetParser::getFilePacket(rawPacket);
			fileReceiver.receiveHeader(filePack);
		}
		else if (type=="part_file") {
			partFilePacket pfPack = packetParser::getPartFilePacket(rawPacket);
			fileReceiver.receivePartFile(pfPack);
		}
		else if (type=="finishFile") {
			finishFilePacket ffPack = packetParser::getFinishFilePacket(rawPacket);
			fileReceiver.finish();
		}

    }
}

void ClientReceiverThread::processIncomingGroupPacket(string rawPacket) {
    incomingGroupPacket i = packetParser::getIncomingGroupPacket(rawPacket);
    string pengirim = i.getGroupname();
    string message = i.getMessage();
    string groupChatPath = user->GetCurrentUsername().append("/").append(pengirim);
    ofstream groupChatFile(groupChatPath.c_str(),ios::app);
    string notification = "new message(s) from ";
    notification = notification.append(pengirim);
    SharedResource::getInstance()->addNotification(notification);
    if(groupChatFile.is_open())
    {
        groupChatFile << MARKER << endl << message << endl;
    }
    groupChatFile.close();
}

void ClientReceiverThread::processGroupSuccessPacket(string rawPacket) 
{
    groupSuccessPacket r = packetParser::getGroupSuccessPacket(rawPacket);
    SharedResource::getInstance()->addToGroupList(r.getGroupname());
    cout<<"Adding group "<<r.getGroupname()<<endl;
    string listGroupPath = user->GetCurrentUsername().append("/listgroup");
    string groupChatPath = user->GetCurrentUsername().append("/").append(user->GetGroupname());
    ofstream listGroupFile(listGroupPath.c_str(),ios::app);
    ofstream groupChatFile(groupChatPath.c_str(),ios::app);
    listGroupFile << user->GetGroupname() << endl;
    listGroupFile.close();
    groupChatFile.close();
}

void ClientReceiverThread::processIncomingPacket(string rawPacket) 
{
    //Masukkan notification ke dalam notification queue.
    incomingPacket i = packetParser::getIncomingPacket(rawPacket);
    string pengirim = i.getSender();
    string message = "new message(s) from ";
    message = message.append(pengirim);
    SharedResource::getInstance()->addNotification(message);

    //Tulis ke file eksternal
    //cari dari listclient
    bool found = false;
    string filepath;
    string currentUsername;
    filepath.append(user->GetCurrentUsername()).append("/listclient");
    fstream listclient(filepath.c_str());
    if(listclient.is_open())    
    {
        while(getline(listclient,currentUsername))
        {
            if(currentUsername == pengirim)
            {
                found = true;
                break;
            }
        }
        listclient.close();
        string filepath;
        filepath = filepath.append(user->GetCurrentUsername().append("/").append(pengirim));
        if(!found)
        {
            //buat file untuk pengirim tersebut.
            ofstream fileoutput (filepath.c_str());
            fileoutput << MARKER << "\n";
            fileoutput << i.getMessage() << endl;
            fileoutput.close();
            filepath = "";

            //update list client dengan pengirim
            filepath = filepath.append(user->GetCurrentUsername().append("/listclient"));
            fileoutput.open(filepath.c_str(),ios::app);
            fileoutput << pengirim << endl;
            fileoutput.close();
        }
        else //found == true
        {
            //update file pengirim.
            ofstream fileoutput (filepath.c_str(),ios::app);
            fileoutput << MARKER << endl;
            fileoutput << i.getMessage() << endl;
            fileoutput.close();
        }
    }
}

void ClientReceiverThread::processErrorPacket(string rawPacket) {
    errorPacket r = packetParser::getErrorPacket(rawPacket);
    cout << r.GetMessage() << endl;
    if(r.GetMessage() == "Wrong password!" || r.GetMessage() == "User not registered yet")
    {
        user->SetLogin(false);
        user->SetUsername("");
    }
    if(r.GetMessage() == "User have been register before")
    {
        user->SetDaftar(false);
        user->SetUsername("");
    }
    if(r.GetMessage() == "User does not exist")
    {
        //hapus file yang terlanjur dibuat.
        string filepath;
        filepath = user->GetCurrentUsername().append("/").append(user->GetUsername());
        remove(filepath.c_str());
        string pathinput;
        string pathoutput;
        string currentline;
        pathinput = user->GetCurrentUsername().append("/listclient");
        pathoutput = user->GetCurrentUsername().append("/temp");
        ifstream fileinput(pathinput.c_str());
        ofstream fileoutput(pathoutput.c_str());
        if(fileinput.is_open() && fileoutput.is_open())
        {
            while(getline(fileinput,currentline))
            {
                if(currentline != user->GetUsername())
                {
                    fileoutput << currentline << endl;
                }
            }
            fileinput.close();
            fileoutput.close();
            remove(pathinput.c_str());
            rename(pathoutput.c_str(),pathinput.c_str());
        }
        else
        {
            cout << "Error openning files" << endl;
            fileinput.close();
            fileoutput.close();
        }
    }
}

void ClientReceiverThread::processSuccessPacket(string rawPacket) {
    successPacket s = packetParser::getSuccessPacket(rawPacket);
    cout << s.getMessage() << endl;
    if(s.GetMessage() == "Anda berhasil login")
    {
        user->SetLogin(true);
    }
    else if(s.GetMessage() == "Anda berhasil register")
    {
        mkdir(user->GetCurrentUsername().c_str(),S_IRWXU);
        mkdir(user->GetCurrentUsername().append("/Downloads").c_str(),S_IRWXU);
        ofstream outputfile (user->GetCurrentUsername().append("/listclient").c_str());
        outputfile.close();
        outputfile.open(user->GetCurrentUsername().append("/listgroup").c_str());
        user->SetUsername("");
    }
    else if(s.GetMessage().substr(0,32) == "Anda berhasil meninggalkan group")
    {
        string listGroupPath = user->GetCurrentUsername().append("/listgroup");
        string groupChatHistory = user->GetCurrentUsername().append("/").append(user->GetGroupname());
        string tempFilePath = user->GetCurrentUsername().append("/temp");

        //Hapus file group chat.
        remove(groupChatHistory.c_str());
        
        //Hapus entry group dari listgroup
        string currentGroupName;
        ifstream listGroupFile (listGroupPath.c_str());
        ofstream outputFile (tempFilePath.c_str());
        if(listGroupFile.is_open())
        {
            while(getline(listGroupFile,currentGroupName))
            {
                if(currentGroupName != user->GetGroupname())
                {
                    outputFile << currentGroupName << endl;
                }
            }
        }
        listGroupFile.close();
        outputFile.close();
        remove(listGroupPath.c_str());
        rename(tempFilePath.c_str(),listGroupPath.c_str());
    }
}

void ClientReceiverThread::overcomeDisconnectedPeer() {
    cout << "Disconnected from server" << endl;
}
