//
//  Session.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Session.h"
#include "Logger.h"

namespace Authentication {
    
    bool Session::isActive() {
        return _loggedIn;
    };
    
    void Session::login() {
        ENTER( "Session::login" );
        
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
        EXIT( "Session::login" );
    }
    
    void Session::logout() {
        ENTER( "Session::logout" );
        
        if( !_loggedIn ) {
            Logger::error() << "Unable to log out; not logged in!";
            throw std::exception();
        }
        
        _loggedIn = false;
        Logger::debug() << "User logged out '" << _user.Name << "'" << endl;

        // flushTrace writes the trace to the disk; trace events after this point will not be flushed out before the program exits.
        Logger::flushTrace( _user.Name );

        EXIT( "Session::logout" );
    }
    
    void Session::externalTransferHelper() {
        ENTER( "Session:externalTransferHelper" );
        
        string transferUsername;
        while( true ) {
            cout << "Please enter destination username: ";
            cin >> transferUsername;
            
            if( _data.doesUserExist( transferUsername ) ) {
                _user = _data.getUser(transferUsername);
                break;
            } else {
                cout << "User " << transferUsername << " does not exist" << endl;
                
                }
            }
    
        _loggedIn = true;
        
    }
    
        
        
    }

