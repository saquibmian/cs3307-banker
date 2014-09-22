//
//  User.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_User_h
#define Banker_User_h

#import <iostream>
#include "Logger.h"
#include "Account.h"

using namespace std;

namespace Authentication {
    
    enum UserRole {
        All, Client, Manager, Maintainer
    };
    
    class User {
    public:
        string Name;
        UserRole Role;
        User( string name, UserRole role = Client );
        friend ostream& operator<<( ostream& os, const User& user );
        
        static string roleToString( UserRole role ) {
            ENTER( "User::roleToString" );
            
            string toReturn;
            switch ( role ) {
                case All:
                    toReturn = "All";
                    break;
                case Client:
                    toReturn = "Client";
                    break;
                case Manager:
                    toReturn = "Manager";
                    break;
                case Maintainer:
                    toReturn = "Maintainer";
                    break;
            }
            
            EXIT( "User::roleToString" );
            return toReturn;
        }
        static UserRole roleFromString( string role ) {
            ENTER( "User::roleFromString" );
            
            UserRole toReturn;
            if( role.compare("All") == 0 ) {
                toReturn = All;
            } else if( role.compare("Client") == 0 ) {
                toReturn = Client;
            } else if( role.compare("Manager") == 0 ) {
                toReturn = Manager;
            } else if( role.compare("Maintainer" ) == 0 ) {
                toReturn = Maintainer;
            }
            
            EXIT( "User::roleFromString" );
            return toReturn;
        }
    };
    
}

#endif
