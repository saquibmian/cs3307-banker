//
//  Initializer.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Program.h"
#include "AccountBalanceOperation.h"
#include "AllClientsBalanceOperation.h"
#include "AggregateBalanceOperation.h"
#include "AccountCreationOperation.h"
#include "AccountDeletionOperation.h"
#include "DepositOperation.h"
#include "WithdrawOperation.h"
#include "TransferOperation.h"
#include "TraceOperation.h"
#include "QuitOperation.h"
#include "Logger.h"
#include "Definitions.h"


using namespace Operations;

Program::Program() {
    mOperations = new vector<IOperation*>;
    data = new FilesystemData();
    menu = new MainMenu();
    session = new Session( *data );
    context = 0;
}

Program::~Program() {
    delete data;
    delete context;
    delete menu;
    for (int i = 0; i < mOperations->size(); i++) {
        delete mOperations->at(i);
    }
    delete mOperations;
}

void Program::Intialize() {
    data->initialize();
    
    createDefaultUsers();
    
    session->login();
    
    addMenuOptions();
    
    context = new OptionContext( *data, *session );
}

void Program::Run() {
    while( session->isActive() ) {
        try {
            MenuOption option = menu->GetNextOption( session->getUser() );
            option.GetOperation().Execute( *context );
        } catch ( std::exception e ) {
            Logger::Error() << "An error occured: " << e.what() << endl;;
        }
    }
}

void Program::createDefaultUsers() {
    if( !data->DoesUserExist( "maintainer" ) ) {
        data->CreateUser( "maintainer", Maintainer );
    }
    if( !data->DoesUserExist( "manager" ) ) {
        data->CreateUser( "manager", Manager );
    }
}

void Program::addMenuOptions() {
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
<<<<<<< HEAD
=======
    
    // Account creation options
    IOperation* accountCreationOp = new AccountCreationOperation();
    MenuOption accountCreationMenuOp ("Open an account", accountCreationOp, Client);
    mOperations->push_back( accountCreationOp );
    menu->AddMenuOption( accountCreationMenuOp );
    
    // Account deletion options
    IOperation* accountDeletionOp = new AccountDeletionOperation();
    MenuOption accountDeletionMenuOp ("Close an account", accountDeletionOp, Client);
    mOperations->push_back( accountDeletionOp );
    menu->AddMenuOption( accountDeletionMenuOp );
    
    // Withdraw
    IOperation* withdrawOp = new WithdrawOperation();
    MenuOption withdrawMenuOp ("Withdraw funds", withdrawOp, Client);
    mOperations ->push_back (withdrawOp);
    menu->AddMenuOption (withdrawMenuOp);
    
    // Deposit
    IOperation* depositOp = new DepositOperation();
    MenuOption depositMenuOp ("Deposit funds", depositOp, Client);
    mOperations ->push_back (withdrawOp);
    menu->AddMenuOption(depositMenuOp);
    
    //Transfer
    IOperation* transferOp = new TransferOperation();
    MenuOption transferMenuOp ("Transfer funds", transferOp, Client);
    mOperations ->push_back(transferOp);
    menu->AddMenuOption(transferMenuOp);
    
    
    
}
>>>>>>> Brent-New

    // Quit operation
    IOperation* quitOp = new QuitOperation();
    MenuOption quitMenuOp ( "Quit", quitOp, All );
    mOperations->push_back( quitOp );
    menu->AddMenuOption( quitMenuOp );
}
