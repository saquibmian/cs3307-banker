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
    _operations = new vector<IOperation*>;
    _data = new FilesystemData();
    _menu = new MainMenu();
    _session = new Session( *_data );
    _context = 0;
}

Program::~Program() {
    delete _data;
    delete _context;
    delete _menu;
    for (int i = 0; i < _operations->size(); i++) {
        IOperation* toFree = _operations->at(i);
        delete toFree;
    }
    delete _operations;
}

void Program::intialize() {
    _data->initialize();
    
    createDefaultUsers();
    
    _session->login();
    
    addMenuOptions();
    
    _context = new OptionContext( *_data, *_session );
}

void Program::run() {
    while( _session->isActive() ) {
        try {
            MenuOption option = _menu->getNextOption( _session->getUser() );
            option.getOperation().execute( *_context );
        } catch ( std::exception e ) {
            Logger::error() << "An error occured: " << e.what() << endl;;
        }
    }
}

void Program::createDefaultUsers() {
    if( !_data->doesUserExist( "maintainer" ) ) {
        _data->createUser( "maintainer", Maintainer );
    }
    if( !_data->doesUserExist( "manager" ) ) {
        _data->createUser( "manager", Manager );
    }
}

void Program::addMenuOptions() {
    // Account balance operation
    IOperation* accountBalanceOp = new AccountBalanceOperation();
    MenuOption accountBalanceMenuOp ( "Display account balance", accountBalanceOp, Client );
    _operations->push_back( accountBalanceOp );
    _menu->addMenuOption( accountBalanceMenuOp );
    
    // All account balance operation
    IOperation* allAccountBalanceOp = new AllClientsBalanceOperation();
    MenuOption allAccountBalanceMenuOp ( "Display all account balances", allAccountBalanceOp, Manager );
    _operations->push_back( allAccountBalanceOp );
    _menu->addMenuOption( allAccountBalanceMenuOp );

    // Total account balance operation
    IOperation* totalAccountBalanceOp = new AggregateBalanceOperation();
    MenuOption totalAccountBalanceMenuOp ( "Display total account balances", totalAccountBalanceOp, Manager );
    _operations->push_back( totalAccountBalanceOp );
    _menu->addMenuOption( totalAccountBalanceMenuOp );

    // Trace operation
    IOperation* traceOp = new TraceOperation();
    MenuOption traceMenuOp ( "Enable/disable trace", traceOp, Maintainer );
    _operations->push_back( traceOp );
    _menu->addMenuOption( traceMenuOp );
    
    // Account creation options
    IOperation* accountCreationOp = new AccountCreationOperation();
    MenuOption accountCreationMenuOp ("Open an account", accountCreationOp, Client);
    _operations->push_back( accountCreationOp );
    _menu->addMenuOption( accountCreationMenuOp );
    
    // Account deletion options
    IOperation* accountDeletionOp = new AccountDeletionOperation();
    MenuOption accountDeletionMenuOp ("Close an account", accountDeletionOp, Client);
    _operations->push_back( accountDeletionOp );
    _menu->addMenuOption( accountDeletionMenuOp );
    
    // Withdraw
    IOperation* withdrawOp = new WithdrawOperation();
    MenuOption withdrawMenuOp ("Withdraw funds", withdrawOp, Client);
    _operations ->push_back (withdrawOp);
    _menu->addMenuOption (withdrawMenuOp);
    
    // Deposit
    IOperation* depositOp = new DepositOperation();
    MenuOption depositMenuOp ("Deposit funds", depositOp, Client);
    _operations ->push_back (depositOp);
    _menu->addMenuOption(depositMenuOp);
    
    //Transfer
    IOperation* transferOp = new TransferOperation();
    MenuOption transferMenuOp ("Transfer funds", transferOp, Client);
    _operations ->push_back(transferOp);
    _menu->addMenuOption(transferMenuOp);
    
    // Quit operation
    IOperation* quitOp = new QuitOperation();
    MenuOption quitMenuOp ( "Quit", quitOp, All );
    _operations->push_back( quitOp );
    _menu->addMenuOption( quitMenuOp );
}
