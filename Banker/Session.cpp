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
        return loggedIn;
    };
    
    void Session::login() {
        ENTER( "login" );
        
        string userName;
        while( true ) {
            cout << "Please enter your username: ";
            cin >> userName;
            
            if( data.DoesUserExist( userName ) ) {
                user = data.GetUser(userName);
                break;
            } else {
                cout << "User " << userName << " does not exist; would you like to create this user? [y/n] ";
                char createUser;
                cin >> createUser;
                if( createUser == 'y' ) {
                    data.CreateUser( userName );
                    user = data.GetUser(userName);
                    break;
                }
            }
        }
        loggedIn = true;
        
        Logger::Debug() << "User logged in '" << user.Name << "'" << endl;
        EXIT( "login" );
    }
    
    void Session::logout() {
        if( !loggedIn ) {
            Logger::Error() << "Unable to log out; not logged in!";
            throw std::exception();
        }
        Logger::flushTrace( user );
        loggedIn = false;
        Logger::Debug() << "User logged out '" << user.Name << "'" << endl;
    }
}
