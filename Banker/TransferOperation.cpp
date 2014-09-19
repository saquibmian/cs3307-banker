//
//  TransferOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"
#include "TransferOperation.h"

using namespace Accounts;
using namespace Data;

namespace Operations{

void TransferOperation::Execute( OptionContext context ) {
    ENTER( "Transfer::Execute" );
    
    data = new FilesystemData();
    
    AccountType accountTypeRoot; // Default value to get rid of warning symbol.
    AccountType accountTypeDestination;
    bool validAccountType = false;
    User currentUser = context.GetUser();
    string type;
    
    if (data->DoesAccountExist(currentUser, Savings) == false || data->DoesAccountExist(currentUser, Checking) == false){
        cout << "Both accounts do not exist! Please open the missing account." << endl;
    } else{
        
        while( !validAccountType ) {
            cout << "Transfer from account [savings/checkings/cancel]: ";
            
            cin >> type;
            if( type.compare("savings") == 0 ) {
                accountTypeRoot = Savings;
                validAccountType = true;
            } else if ( type.compare( "checkings" ) == 0 ) {
                accountTypeRoot = Checking;
                validAccountType = true;
            } else if ( type.compare ("cancel" ) == 0){
                cout << "Withdraw action cancelled" << endl;
                validAccountType = true;
            }
            else {
                Logger::Error() << "Invalid account type!" << endl;
            }
        }
        
        if ( accountTypeRoot == Savings ){
            
            Account transferAccountRoot = data->GetAccount(currentUser, Savings);
            Account transferAccountDestination = data->GetAccount(currentUser,Checking);
            double savingsWithdraw=0;
            //double checkingsDeposit=0;
            double newBalance;
            
            cout << "Amount to transfer from Savings Account to Checkings Account [ $ ]: "; // could change it to round any requests of 0.002
            cin >> savingsWithdraw;
            
            newBalance = transferAccountRoot.Withdraw(savingsWithdraw);
            cout << "The remaining balance in the Savings Account is $" << newBalance << endl; //can format to always show two decimals if needed.
            
            newBalance = transferAccountDestination.Deposit(savingsWithdraw);
            cout << "The new balance in the Checking Account is $" << newBalance << endl << endl;
            
            data->UpdateAccount(currentUser, transferAccountRoot);
            data->UpdateAccount(currentUser, transferAccountDestination);
            
            
            
            
        }
        
        if (accountTypeRoot == Checking){
            
            Account transferAccountRoot = data->GetAccount(currentUser, Checking);
            Account transferAccountDestination = data->GetAccount(currentUser,Savings);
            double savingsWithdraw=0;
            //double checkingsDeposit=0;
            double newBalance;
            
            cout << "Amount to transfer from Checking Account to Savings Account [ $ ]: "; // could change it to round any requests of 0.002
            cin >> savingsWithdraw;
            
            newBalance = transferAccountRoot.Withdraw(savingsWithdraw);
            cout << "The remaining balance in the Checking Account is $" << newBalance << endl; //can format to always show two decimals if needed.
            
            newBalance = transferAccountDestination.Deposit(savingsWithdraw);
            cout << "The new balance in the Savings Account is $" << newBalance << endl << endl;
            
            data->UpdateAccount(currentUser, transferAccountRoot);
            data->UpdateAccount(currentUser, transferAccountDestination);
            
        }
        
    }// end if statements
    
} // end execute

}