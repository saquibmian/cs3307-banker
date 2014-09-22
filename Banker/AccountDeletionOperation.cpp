//
//  AccountDeletionOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-17.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "AccountDeletionOperation.h"
#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"
using namespace Accounts;
using namespace Data;


namespace Operations {

    void AccountDeletionOperation::Execute( OptionContext context ) {
        ENTER( "AccountBalanceOperation::Execute" );
        
        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        
        if (data.DoesAccountExist(user, Savings) == false && data.DoesAccountExist(user, Checking) == false){
            Logger::Error() << "Neither account exists!" << endl;
        } else{

            bool validAccountType = false;
            string type;
            while( !validAccountType ) {
                Logger::Info() << "To close an account, it must have a 0 (zero) balance." << endl;
                Logger::Info() << "Closing account of type [savings/checkings/both/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    deleteAccount( Savings, context);
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    deleteAccount( Checking, context);
                    validAccountType = true;
                } else if ( type.compare( "both" ) == 0){
                    deleteAccount( Checking, context);
                    deleteAccount( Savings, context);
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::Info() << "Close acount action cancelled" << endl;
                    break;
                } else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
        }
        
        EXIT( "AccountBalanceOperation::Execute" );
    }
    
    void AccountDeletionOperation::deleteAccount( AccountType type, OptionContext& context ) {
        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        if( !data.DoesAccountExist( user, type ) ) {
            Logger::Error() << "Account '" << Account::typeToString( type ) <<"' doesn't exist!" << endl;
        }
        
        Account account = data.GetAccount(user, type);
        if ( account.Balance != 0 ){
            Logger::Error() << "Account '" << Account::typeToString( type ) <<"' is not empty" << endl;
        } else{
            data.closeAccountForUser( user, account.Type );
            Logger::Info() << "Account '" << Account::typeToString( type ) <<"' closed" << endl;
        }
    }

}