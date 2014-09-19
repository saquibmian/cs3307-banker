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
        
        data = new FilesystemData();
        
        AccountType accountType; // Default value to get rid of warning symbol.
        bool validAccountType = false;
        User currentUser = context.GetUser();
        string type;
        
        if (data->DoesAccountExist(currentUser, Savings) == false && data->DoesAccountExist(currentUser, Checking) == false){
            cout << "Neither account exists!" << endl;
        } else{
    
            while( !validAccountType ) {
                cout << "To close an account, it must have a 0 (zero) balance." << endl;
                cout << "Closing account of type [savings/checkings/both/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    accountType = Savings;
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    accountType = Checking;
                    validAccountType = true;
                } else if ( type.compare( "both" ) == 0){
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    cout << "Close acount action cancelled" << endl;
                    validAccountType = true;
                }
                else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
            
            if (accountType == Savings || type.compare("both") == 0){
             
                Account deletionAccount = data->GetAccount(currentUser, Savings);
                
                if (deletionAccount.Balance != 0){
                    cout << "Savings account is not empty" << endl;
                }
                else{
                    data->CloseSavingsAccount(currentUser);
                    cout << "Savings account closed" << endl;
                }
                
                
            }
            
            if (accountType == Checking || type.compare("both") == 0){
                
                Account deletionAccount = data->GetAccount(currentUser, Checking);
                
                if (deletionAccount.Balance != 0){
                    cout << "Checking account is not empty" << endl;
                }
                else {
                    data ->CloseCheckingAccount(currentUser);
                    cout << "Checking account closed" << endl;
                }
                
            }
            
        }// end else where accounts can be closed.
        
    } // end execute

}