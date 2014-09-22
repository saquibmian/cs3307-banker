//
//  DepositOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "DepositOperation.h"

#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"

using namespace Accounts;
using namespace Data;


namespace Operations {
    
    void DepositOperation::execute( OptionContext context ) {
        ENTER( "DepositOperation::Execute" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        
        if (data.doesAccountExist(user, Savings) == false && data.doesAccountExist(user, Checking) == false){
            Logger::error() << "No open account exists!" << endl;
        } else{
            bool validAccountType = false;
            string type;
            while( !validAccountType ) {
                cout << "Deposit into account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    depositIntoAccount( Savings, context );
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    depositIntoAccount( Checking, context );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "Deposit action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
        }
        
        EXIT( "DepositOperation::Execute" );
    }
    
    void DepositOperation::depositIntoAccount( AccountType type, OptionContext& context ) {
        ENTER( "DepositOperation::depositIntoAccount" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        if( !data.doesAccountExist( user, type ) ) {
            Logger::error() << "Specified account does not exist. Please create it first." << endl;
        } else {
            Account account = data.getAccount( user, type );
            
            double toDeposit=0;
            cout << "Amount to deposit into account [ $ ]: ";
            cin >> toDeposit;
            
            account.deposit( toDeposit );
            data.storeAccount( user, account );
            
            Logger::info() << "The remaining balance is $" << account.Balance << endl;
        }
        
        EXIT( "DepositOperation::depositIntoAccount" );
    }
    
}