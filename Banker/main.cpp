//
//  main.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include <iostream>
#include "Definitions.h"
#include "User.h"
#include "Configuration.h"
#include "Logger.h"
#include "FilesystemData.h"
#include "MenuWindow.h"

using namespace std;
using namespace Authentication;
using namespace Data;
using namespace Menu;

User* login( IData& data );
void logout();

int main( int argc, const char * argv[] ) {
    ENTER( "main" );
    
    FilesystemData data;
    
    User* user = login( data );
    MenuWindow menu;
    
    while (true) {
        MenuOption option = menu.GetNextOption( *user );
        
        if( option.IsLogout() ) {
            logout();
            user = login( data );
            // NOTE: This makes it so that you can't quit until logged in ... we should fix this.
        } else if( option.IsQuit() ) {
            EXIT( "main" );
            return 0;
        }
    }

    cout << "Goodbye!" << endl;
    EXIT( "main" );
    return 0;
}

User* login( IData& data ) {
    string userName;
    User* user = 0;
    
    while( user == 0 ) {
        cout << "Please enter your username: ";
        cin >> userName;
        
        if( data.DoesUserExist( userName ) ) {
            user = new User( userName );
            break;
        } else {
            char createUser;
            cout << "User " << userName << " does not exist; would you like to create this user? [y/n]";
            createUser = getchar();
            if( createUser == 'y' ) {
                user = new User( userName );
                data.CreateUser( *user );
            }
        }
    }
    
    return user;
}

void logout() {
    return;
}
