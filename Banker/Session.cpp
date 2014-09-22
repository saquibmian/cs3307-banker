//
//  Session.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Session.h"
#include "Logger.h"
#include "Definitions.h"

namespace Authentication {
    
    bool Session::isActive() {
        return _loggedIn;
    };
    
    void Session::login() {
        ENTER( "login" );
        
        string userName;
        while( true ) {
            cout << "Please enter your username: ";
            cin >> userName;
            
            if( _data.doesUserExist( userName ) ) {
                _user = _data.getUser(userName);
                break;
            } else {
                cout << "User " << userName << " does not exist; would you like to create this user? [y/n] ";
                char createUser;
                cin >> createUser;
                if( createUser == 'y' ) {
                    _data.createUser( userName );
                    _user = _data.getUser(userName);
                    break;
                }
            }
        }
        _loggedIn = true;
        
        Logger::debug() << "User logged in '" << _user.Name << "'" << endl;
        EXIT( "login" );
    }
    
    void Session::logout() {
        if( !_loggedIn ) {
            Logger::error() << "Unable to log out; not logged in!";
            throw std::exception();
        }
        Logger::flushTrace( _user.Name );
        _loggedIn = false;
        Logger::debug() << "User logged out '" << _user.Name << "'" << endl;
    }
}
