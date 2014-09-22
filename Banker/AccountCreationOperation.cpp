


//
//  AccountCreationOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-17.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "AccountCreationOperation.h"
#include "AccountCreationOperation.h"
#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"
using namespace Accounts;
using namespace Data;


namespace Operations {
    
    void AccountCreationOperation::execute( OptionContext context ) {
        ENTER( "AccountBalanceOperation::Execute" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        if (data.doesAccountExist(user, Savings) && data.doesAccountExist(user, Checking)){
            Logger::error() << "Both accounts already exist!" << endl;
        } else{
            bool validAccountType = false;
            string type;
            while( !validAccountType ) {
                cout << "Open account of type [savings/checkings/both/cancel]: ";
                cin >> type;
                
                if( type.compare("savings") == 0 ) {
                    createAccount( Savings, context );
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    createAccount( Checking, context );
                    validAccountType = true;
                } else if ( type.compare( "both" ) == 0){
                    createAccount( Checking, context );
                    createAccount( Savings, context );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    cout << "Open acount action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
        }
        
        EXIT( "AccountBalanceOperation::Execute" );
    }
    
    void AccountCreationOperation::createAccount( AccountType type, OptionContext& context) {
        ENTER( "AccountBalanceOperation::createAccount" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();

        if ( data.doesAccountExist(user, type) ){
            Logger::error() << Account::typeToString( type ) << "account already exists!" << endl;
        } else {
            bool validBalance = false;
            double inputBalance = -1;
            while (!validBalance){
                cout << "Starting balance of " << Account::typeToString( type ) << " account [ $ ]: ";
                cin >> inputBalance;
                if (inputBalance >= 0){
                    validBalance = true;
                }
            }
            Account account = Account( type, inputBalance );
            data.storeAccount( user, account );
            Logger::info() << "Account '" << Account::typeToString( type ) <<"' created!" << endl;
        }

        EXIT( "AccountBalanceOperation::createAccount" );
    }

}