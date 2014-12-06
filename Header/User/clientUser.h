/* 
 * File:   clientUser.h
 * Author: timothy
 *
 * Created on December 2, 2014, 6:33 PM
 */

#ifndef CLIENTUSER_H
#define	CLIENTUSER_H
#include <string>
using namespace std;

class clientUser {
public:
    clientUser();
    clientUser(const clientUser& orig);
    virtual ~clientUser();
    bool IsLogin() const;

    void SetLogin(bool login);

    string GetUsername() const;

    void SetUsername(string username);
    
    bool IsDaftar() const;

    void SetDaftar(bool daftar);

    string GetCurrentUsername() const;

    void SetCurrentUsername(string currentUsername);

    string GetGroupname() const;

    void SetGroupname(string groupname);


private:
    bool login;
    string username;
    string currentUsername;
    bool daftar;
    string groupname;
};

#endif	/* CLIENTUSER_H */

