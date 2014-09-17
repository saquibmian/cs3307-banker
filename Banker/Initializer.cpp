//
//  Initializer.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Initializer.h"
#include "AccountBalanceOperation.h"
#include "AllClientsBalanceOperation.h"
#include "AggregateBalanceOperation.h"
#include "TraceOperation.h"

using namespace Operations;

namespace Initialize {
    Initializer::Initializer() : user( "none" ) {
        mOperations = new vector<IOperation*>;
        data = new FilesystemData();
        menu = new MainMenu();
        context = 0;
    }
    
    Initializer::~Initializer() {
        delete data;
        delete context;
        delete menu;
        for (int i = 0; i < mOperations->size(); i++) {
            delete mOperations->at(i);
        }
        delete mOperations;
    }
    
    void Initializer::Intialize() {
        data->initialize();
        
        createDefaultUsers();
        
        login();
        
        addMenuOptions();
        
        context = new OptionContext( user, *data );
    }
    
    void Initializer::createDefaultUsers() {
        if( !data->DoesUserExist( "maintainer" ) ) {
            data->CreateUser( "maintainer", Maintainer );
        }
        if( !data->DoesUserExist( "manager" ) ) {
            data->CreateUser( "manager", Manager );
        }
    }
    
    void Initializer::addMenuOptions() {
        // Account balance operation
        IOperation* accountBalanceOp = new AccountBalanceOperation();
        MenuOption accountBalanceMenuOp ( "Display account balance", accountBalanceOp, Client );
        mOperations->push_back( accountBalanceOp );
        menu->AddMenuOption( accountBalanceMenuOp );
        
        // All account balance operation
        IOperation* allAccountBalanceOp = new AllClientsBalanceOperation();
        MenuOption allAccountBalanceMenuOp ( "Display all account balances", allAccountBalanceOp, Manager );
        mOperations->push_back( allAccountBalanceOp );
        menu->AddMenuOption( allAccountBalanceMenuOp );

        // Total account balance operation
        IOperation* totalAccountBalanceOp = new AggregateBalanceOperation();
        MenuOption totalAccountBalanceMenuOp ( "Display total account balances", totalAccountBalanceOp, Manager );
        mOperations->push_back( totalAccountBalanceOp );
        menu->AddMenuOption( totalAccountBalanceMenuOp );

        // Trace operation
        IOperation* traceOp = new TraceOperation();
        MenuOption traceMenuOp ( "Enable/disable trace", traceOp, Maintainer );
        mOperations->push_back( traceOp );
        menu->AddMenuOption( traceMenuOp );
    }
    
    void Initializer::login() {
        ENTER( "login" );
        
        string userName;
        while( !loggedIn ) {
            cout << "Please enter your username: ";
            cin >> userName;
            
            if( data->DoesUserExist( userName ) ) {
                user = data->GetUser(userName);
                break;
            } else {
                cout << "User " << userName << " does not exist; would you like to create this user? [y/n] ";
                char createUser;
                cin >> createUser;
                if( createUser == 'y' ) {
                    data->CreateUser( userName );
                    user = data->GetUser(userName);
                }
            }
        }
        
        EXIT( "login" );
    }
}