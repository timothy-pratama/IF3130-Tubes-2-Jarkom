/* 
 * File:   packetParser.cpp
 * Author: timothy
 * 
 * Created on November 26, 2014, 4:32 PM
 */

#include "Packet/packetParser.h"

//Format message : L7;timothy4;miku

packetParser::packetParser() {
}

packetParser::packetParser(const packetParser& orig) {
}

packetParser::~packetParser() {
}

string packetParser::getPacketType(string message) {    
    char code = message.at(0);
    if(code == 'L')
    {
        return "login";
    }
    else if(code == 'S')
    {
        return "send";
    }
    else if(code == 'R')
    {
        return "register";
    }
    else if(code == 'I')
    {
        return "incoming";
    }
    else if(code == 'G')
    {
        return "group";
    }
    else if(code == 'B')
    {
        return "broadcast";
    }
    else if(code == 'E')
    {
        return "logout";
    }
    else if(code == 'Z')
    {
        return "success";
    }
    else if(code =='X')
    {
        return "error";
    }
    else if (code =='J')
    {
    	return "joinGroup";
    }
    else if (code =='T')
    {
    	return "leaveGroup";
    }
    else if (code == 'A') {
    	return "incomingGroup";
    }
    else if (code == 'C') {
    	return "groupSuccess";
    }
    else if(code == 'F')
	{
		return "file";
	}
	else if(code == 'V')
	{
		return "part_file";
	}
	else if(code == 'W')
	{
		return "finishFile";
	}
    else
    {
        return "unknown";
    }
}

vector<string> packetParser::parseMessage(string message) {
    vector<string> parameter;
    int i = 1;                      // iterator.
    int length = message.length();  // panjang message.
    int counter;                    // panjang sebuah element dalam message.
    string temp;                    // string yang sedang dibaca.
    while(i < length)
    {
        temp = "";
        //baca jumlah karakter
        do
        {
            temp = temp + message.at(i);
            if(i < length - 1)
            {
                i++;
            }
        } while (message.at(i) != ';' && i < length);
        counter = atoi(temp.c_str());
        //ambil element nya.
        temp = "";
        for(int j=0; j<counter; j++)
        {
            i++;
            temp = temp + message.at(i);
        }
        i++;
        parameter.push_back(temp);
    }
    return parameter;
}


broadcastPacket packetParser::getBroadcastPacket(string message) {
    vector<string>parameter = parseMessage(message);  //menyimpan element2 yang ada di message.
    broadcastPacket result;                           //packet yang akan di return.
    result.setGroupName(parameter.at(0));
    result.setMessage(parameter.at(1));
    return result;
}

groupPacket packetParser::getGroupPacket(string message) {
    vector<string>parameter = parseMessage(message);  //menyimpan element2 yang ada di message.
    groupPacket result;                               //packet yang akan di return.
    result.setCreator(parameter.at(0));
    result.setName(parameter.at(1));
    return result;
}

incomingPacket packetParser::getIncomingPacket(string message) {
    vector<string>parameter = parseMessage(message);  //menyimpan element2 yang ada di message.
    incomingPacket result;                            //packet yang akan di return.
    result.setSender(parameter.at(0));
    result.setMessage(parameter.at(1));
    return result;
}

loginPacket packetParser::getLoginPacket(string message) {
    vector<string>parameter = parseMessage(message);
    loginPacket p;
    p.setUsername(parameter.at(0));
    p.setPassword(parameter.at(1));
    return p;
}

registerPacket packetParser::getRegisterPacket(string message) {
    vector<string>parameter = parseMessage(message);
    registerPacket r;
    r.setUsername(parameter.at(0));
    r.setPassword(parameter.at(1));
    return r;
}

sendPacket packetParser::getSendPacket(string message) {
    vector<string>parameter = parseMessage(message);
    sendPacket s;
    s.setUser(parameter.at(0));
    s.setMessage(parameter.at(1));
    return s;
}

logoutPacket packetParser::getLogoutPacket(string message) {
    vector<string>parameter = packetParser::parseMessage(message);
    logoutPacket e;
    e.SetUsername(parameter.at(0));
    return e;
}

errorPacket packetParser::getErrorPacket(string message) {
    vector<string>parameter = parseMessage(message);
    errorPacket x;
    x.SetMessage(parameter.at(0));
    return x;
}

successPacket packetParser::getSuccessPacket(string message) {
    vector<string>parameter = parseMessage(message);
    successPacket z;
    z.SetMessage(parameter.at(0));
    return z;
}

joinGroupPacket packetParser::getJoinGroupPacket(string message) {
	vector<string>parameter = parseMessage(message);
	joinGroupPacket j;
	j.setSenderUsername(parameter.at(0));
	j.setGroupname(parameter.at(1));
	return j;
}

leaveGroupPacket packetParser::getLeaveGroupPacket(string message) {
	vector<string>parameter = parseMessage(message);
	leaveGroupPacket t;
	t.setUsername(parameter.at(0));
	t.setGroupname(parameter.at(1));
	return t;
}

incomingGroupPacket packetParser::getIncomingGroupPacket(string message) {
	vector<string>parameter = parseMessage(message);
	incomingGroupPacket a;
	a.setUsername(parameter.at(0));
	a.setGroupname(parameter.at(1));
	a.setMessage(parameter.at(2));
	return a;
}

groupSuccessPacket packetParser::getGroupSuccessPacket(string message) {
	vector<string>parameter = parseMessage(message);
	groupSuccessPacket c;
	c.setGroupname(parameter.at(0));
	return c;
}

filePacket packetParser::getFilePacket(string message){
	vector<string>parameter = parseMessage(message);
	filePacket f;
	f.setSenderUsername(parameter.at(0));
	f.setDestinationUsername(parameter.at(1));
	f.setFilename(parameter.at(2));
	return f;
}

partFilePacket packetParser::getPartFilePacket(string message){
	vector<string>parameter = parseMessage(message);
	partFilePacket pf;
	pf.setMessage(parameter.at(1));
	pf.setDestinationUsername(parameter.at(0));
	return pf;
}

finishFilePacket packetParser::getFinishFilePacket(string message) {
	vector<string>parameter = parseMessage(message);
	finishFilePacket ff;
	ff.setUsername(parameter.at(0));
	return ff;
}
string packetParser::encodePacket(Packet* packet) {
    string type = packet->getPacketType();
    string result;
    stringstream ss;
    if(type == "broadcast")
    {
        broadcastPacket *b = (broadcastPacket *) packet;
        ss << b->getGroupName().length();
        string groupNameLength = ss.str();
        ss.str("");
        ss << b->getMessage().length();
        string messageLength = ss.str();
        result += "B"+groupNameLength+";"+b->getGroupName()+messageLength+";"+b->getMessage();
        ss.str("");
    }
    else if(type == "group")
    {
        groupPacket *g = (groupPacket*) packet;
        ss << g->getCreator().length();
        string creatorLength = ss.str();
        ss.str("");
        ss << g->getName().length();
        string nameLength = ss.str();
        result += "G"+creatorLength+";"+g->getCreator()+nameLength+";"+g->getName();
    }
    else if(type == "incoming")
    {
        incomingPacket *i = (incomingPacket*) packet;
        ss << i->getSender().length();
        string senderLength = ss.str();
        ss.str("");
        ss << i->getMessage().length();
        string messageLength = ss.str();
        result += "I"+senderLength+";"+i->getSender()+messageLength+";"+i->getMessage();        
    }
    else if(type == "login")
    {
        loginPacket *l = (loginPacket *) packet;
        string usernameLength;
        string passwordLength;
        ss << l->getUsername().length();
        usernameLength = ss.str();
        ss.str("");
        ss << l->getPassword().length();
        passwordLength = ss.str();
        result += "L"+usernameLength+";"+l->getUsername()+passwordLength+";"+l->getPassword();
    }
    else if(type == "register")
    {
        registerPacket *r = (registerPacket *) packet;
        string usernameLength;
        string passwordLength;
        ss << r->getUsername().length();
        usernameLength = ss.str();
        ss.str("");
        ss << r->getPassword().length();
        passwordLength = ss.str();
        result += "R"+usernameLength+";"+r->getUsername()+passwordLength+";"+r->getPassword();
    }
    else if(type == "send")
    {
        sendPacket *s = (sendPacket *) packet;
        string usernameLength;
        string messageLength;
        ss << s->getUser().length();
        usernameLength = ss.str();
        ss.str("");
        ss << s->getMessage().length();
        messageLength = ss.str();
        result += "S"+usernameLength+";"+s->getUser()+messageLength+";"+s->getMessage();
    }
    else if(type == "logout")
    {
        logoutPacket *e = (logoutPacket *) packet;
        string usernameLength;
        ss << e->GetUsername().length();
        usernameLength = ss.str();
        result = 'E'+usernameLength+';'+e->GetUsername();
    }
    else if(type == "error")
    {
        errorPacket *x = (errorPacket *) packet;
        string messageLength;
        ss << x->GetMessage().length();
        messageLength = ss.str();
        result = 'X'+messageLength+';'+x->GetMessage();
    }
    else if(type == "success")
    {
        successPacket *z = (successPacket *) packet;
        string messageLength;
        ss << z->GetMessage().length();
        messageLength = ss.str();
        result = 'Z'+messageLength+';'+z->GetMessage();
    }
    else if (type == "joinGroup")
    {
    	joinGroupPacket *j = (joinGroupPacket *) packet;
    	string usernameLength;
		ss << j->getSenderUsername().length();
		usernameLength = ss.str();
		ss.str("");
		string groupnameLength;
		ss << j->getGroupname().length();
		groupnameLength = ss.str();
		result = 'J'+usernameLength+';'+j->getSenderUsername()+groupnameLength+";"+j->getGroupname();
    }
    else if (type == "leaveGroup")
    {
    	leaveGroupPacket *t = (leaveGroupPacket *) packet;
    	string usernameLength;
    	ss <<t->getUsername().length();
    	usernameLength = ss.str();
    	ss.str("");
    	string groupnameLength;
		ss << t->getGroupname().length();
		groupnameLength = ss.str();
		result = 'T'+usernameLength+';'+t->getUsername()+groupnameLength+";"+t->getGroupname();
    }
    else if (type == "incomingGroup")
    {
    	incomingGroupPacket *t = (incomingGroupPacket *) packet;
    	string usernameLength;
    	ss << t->getUsername().length();
    	usernameLength = ss.str();
    	ss.str("");
    	string groupnameLength;
		ss << t->getGroupname().length();
		groupnameLength = ss.str();
		ss.str("");
		string messageLength;
		ss<< t->getMessage().length();
		messageLength = ss.str();
		result = 'A'+usernameLength+';'+t->getUsername()+groupnameLength+";"+t->getGroupname()+messageLength+";"+t->getMessage();
    }
    else if (type == "groupSuccess")
    {
    	groupSuccessPacket *t = (groupSuccessPacket *) packet;
    	string groupnameLength;
    	ss <<t->getGroupname().length();
    	groupnameLength = ss.str();
    	result = 'C'+groupnameLength+';'+t->getGroupname();
    }
    else if(type == "file")
	{
		filePacket *f = (filePacket *) packet;
		ss<<f->getSenderUsername().length();
		string senderLength = ss.str();
		ss.str("");
		ss<<f->getDestinationUsername().length();
		string destinationLength = ss.str();
		ss.str("");
		ss<<f->getFilename().length();
		string filenameLength = ss.str();
		result = 'F'+senderLength+';'+f->getSenderUsername()+destinationLength+';'+
				f->getDestinationUsername()+filenameLength+';'+f->getFilename();
	}
	else if(type == "part_file")
	{
		partFilePacket *v = (partFilePacket *) packet;
		ss<<v->getMessage().length();
		string messageLength = ss.str();
		ss.str("");
		ss<<v->getDestinationUsername().length();
		string destinationLength = ss.str();
		result = 'V'+destinationLength+';'+v->getDestinationUsername()+messageLength+';'+v->getMessage();
	}
	else if (type == "finishFile") {
		finishFilePacket *ff = (finishFilePacket *) packet;
		string usernameLength;
		ss <<ff->getUsername().length();
		usernameLength = ss.str();
		result = 'W'+usernameLength+';'+ff->getUsername();
	}
    ss.str("");
    ss << result.length();
    result = ss.str() + ';' + result;
    return result;
}
