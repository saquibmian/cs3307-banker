//
//  WithdrawOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "WithdrawOperation.h"
#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"

using namespace Accounts;
using namespace Data;


namespace Operations {
    
    void WithdrawOperation::Execute( OptionContext context ) {
        ENTER( "WithdrawOperation::Execute" );
        
        IData* data = &context.GetData();
        
        AccountType accountType; // Default value to get rid of warning symbol.
        bool validAccountType = false;
        User currentUser = context.GetSession().getUser();
        string type;
        
        if (data->DoesAccountExist(currentUser, Savings) == false && data->DoesAccountExist(currentUser, Checking) == false){
            cout << "No open account exists!" << endl;
        } else{
            
            while( !validAccountType ) {
                cout << "Any action causing a checking account to go, or on a checking account below $1000.00 has a $2.00 transaction fee" << endl;
                cout << "Withdraw from account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    accountType = Savings;
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    accountType = Checking;
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    cout << "Withdraw action cancelled" << endl;
                    validAccountType = true;
                }
                else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
            
            if ( accountType == Savings ){
                
                Account withdrawAccount = data->GetAccount(currentUser, Savings);
                double savingsWithdraw=0;
                double newBalance;
                
                cout << "Amount to withdraw from Savings Account [ $ ]: "; // could change it to round any requests of 0.002
                cin >> savingsWithdraw;
                
                newBalance = withdrawAccount.Withdraw(savingsWithdraw);
                data->UpdateAccount(currentUser, withdrawAccount);
                cout << "The remaining balance is $" << newBalance << endl; //can format to always show two decimals if needed.
                
                
                
            }
            
            if (accountType == Checking){
                
                Account withdrawAccount = data->GetAccount(currentUser, Checking);
                double checkingWithdraw=0;
                double newBalance;
                
                cout << "Amount to withdraw from Checking Account [ $ ]: "; // could change it to round any requests of 0.002
                cin >> checkingWithdraw;
                
                newBalance = withdrawAccount.Withdraw(checkingWithdraw);
                data->UpdateAccount(currentUser, withdrawAccount); // UpdateAccount is a less safe StoreAccount.
                //It doesn't check to see if the file exists, but in order to reach all uses of it that has to have been checked already.
                cout << "The remaining balance is $" << newBalance << endl; //can format to always show two decimals if needed.
                
            }
            
        }// end if statements
        
    } // end execute
    
}