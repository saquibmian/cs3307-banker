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
        
        IData* data = &context.GetData();
        
        AccountType accountType; // Default value to get rid of warning symbol.
        bool validAccountType = false;
        User currentUser = context.GetSession().getUser();
        string type;
        
        if (data->DoesAccountExist(currentUser, Savings) == false && data->DoesAccountExist(currentUser, Checking) == false){
            cout << "No open account exists!" << endl;
        } else{
            
            while( !validAccountType ) {
                cout << "Deposit into account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    accountType = Savings;
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    accountType = Checking;
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    cout << "Deposit action cancelled" << endl;
                    validAccountType = true;
                }
                else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
            
            if ( accountType == Savings ){
                
                Account withdrawAccount = data->GetAccount(currentUser, Savings);
                double savingsDeposit=0;
                double newBalance;
                
                cout << "Amount to deposit into Savings Account [ $ ]: "; // could change it to round any requests of 0.002
                cin >> savingsDeposit;
                
                newBalance = withdrawAccount.Deposit(savingsDeposit);
                data->UpdateAccount(currentUser, withdrawAccount);
                cout << "The new balance is $" << newBalance << endl; //can format to always show two decimals if needed.
                
                
                
            }
            
            if (accountType == Checking){
                
                Account withdrawAccount = data->GetAccount(currentUser, Checking);
                double checkingDeposit=0;
                double newBalance;
                
                cout << "Amount to deposit from Checking Account [ $ ]: "; // could change it to round any requests of 0.002
                cin >> checkingDeposit;
                
                newBalance = withdrawAccount.Deposit(checkingDeposit);
                data->UpdateAccount(currentUser, withdrawAccount); // UpdateAccount is a less safe StoreAccount.
                //It doesn't check to see if the file exists, but in order to reach all uses of it that has to have been checked already.
                cout << "The new balance is $" << newBalance << endl; //can format to always show two decimals if needed.
                
            }
            
        }// end if statements
        
    } // end execute
    
}