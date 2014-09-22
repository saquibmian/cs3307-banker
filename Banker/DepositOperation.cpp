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
    
    void DepositOperation::Execute( OptionContext context ) {
        ENTER( "DepositOperation::Execute" );
        
        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        
        if (data.DoesAccountExist(user, Savings) == false && data.DoesAccountExist(user, Checking) == false){
            Logger::Error() << "No open account exists!" << endl;
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
                    Logger::Info() << "Deposit action cancelled" << endl;
                    break;
                } else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
        }
        
        EXIT( "DepositOperation::Execute" );
    }
    
    void DepositOperation::depositIntoAccount( AccountType type, OptionContext& context ) {
        ENTER( "DepositOperation::depositIntoAccount" );
        
        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        if( !data.DoesAccountExist( user, type ) ) {
            Logger::Error() << "Specified account does not exist. Please create it first." << endl;
        } else {
            Account account = data.GetAccount( user, type );
            
            double toDeposit=0;
            cout << "Amount to deposit into account [ $ ]: ";
            cin >> toDeposit;
            
            account.Deposit( toDeposit );
            data.StoreAccount( user, account );
            
            Logger::Info() << "The remaining balance is $" << account.Balance << endl;
        }
        
        EXIT( "DepositOperation::depositIntoAccount" );
    }
    
}