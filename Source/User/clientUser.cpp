/* 
 * File:   clientUser.cpp
 * Author: timothy
 * 
 * Created on December 2, 2014, 6:33 PM
 */

#include "User/clientUser.h"

clientUser::clientUser() {
}

clientUser::clientUser(const clientUser& orig) {
}

clientUser::~clientUser() {
}

void clientUser::SetLogin(bool login) {
    this->login = login;
}

bool clientUser::IsLogin() const {
    return login;
}

void clientUser::SetUsername(string username) {
    this->username = username;
}

string clientUser::GetUsername() const {
    return username;
}

void clientUser::SetDaftar(bool daftar) {
    this->daftar = daftar;
}

bool clientUser::IsDaftar() const {
    return daftar;
}

void clientUser::SetCurrentUsername(string currentUsername) {
    this->currentUsername = currentUsername;
}

string clientUser::GetCurrentUsername() const {
    return currentUsername;
}

void clientUser::SetGroupname(string groupname) {
    this->groupname = groupname;
}

string clientUser::GetGroupname() const {
    return groupname;
}
