//
//  Initializer.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Initializer.h"
#include "AccountBalanceOperation.h"

using namespace Operations;

namespace Initialize {
    Initializer::Initializer() {
        mOperations = new vector<IOperation*>;
        data = new FilesystemData();
        menu = new MainMenu();
        user = 0;
        context = 0;
    }
    
    Initializer::~Initializer() {
        delete data;
        delete user;
        delete context;
        delete menu;
        for (int i = 0; i < mOperations->size(); i++) {
            delete mOperations->at(i);
        }
        delete mOperations;
    }
    
    void Initializer::Intialize() {
        login();
        
        addMenuOptions();
        
        context = new OptionContext( *user, *data );
    }
    
    void Initializer::addMenuOptions() {
        // Account balance operation
        IOperation* operation1 = new AccountBalanceOperation();
        MenuOption option1 ( "Display account balance", operation1, Client );
        mOperations->push_back( operation1 );
        menu->AddMenuOption( option1 );
        
        // Trace operation
        IOperation* operation2 = new TraceOperation();
        MenuOption option2 ( "Enable/disable trace", operation2, Maintainer );
        mOperations->push_back( operation2 );
        menu->AddMenuOption( option2 );
    }
    
    void Initializer::login() {
        ENTER( "login" );
        
        string userName;
        while( user == 0 ) {
            cout << "Please enter your username: ";
            cin >> userName;
            
            if( data->DoesUserExist( userName ) ) {
                user = new User( userName );
                break;
            } else {
                cout << "User " << userName << " does not exist; would you like to create this user? [y/n] ";
                char createUser;
                cin >> createUser;
                if( createUser == 'y' ) {
                    data->CreateUser( userName );
                    user = new User( userName );
                }
            }
        }
        
        EXIT( "login" );
    }
}