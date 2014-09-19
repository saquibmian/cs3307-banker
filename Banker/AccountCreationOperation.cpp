


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
    
    
    void AccountCreationOperation::Execute( OptionContext context ) {
        ENTER( "AccountBalanceOperation::Execute" );
        
        data = new FilesystemData();
        
        AccountType accountType = Savings; // Default value to get rid of warning symbol.
        bool validAccountType = false;
        User currentUser = context.GetUser();
        string type;
        
        if (data->DoesAccountExist(currentUser, Savings) && data->DoesAccountExist(currentUser, Checking)){
            cout << "Both accounts already exist!" << endl;
        } else{
            
        
        
        while( !validAccountType ) {
            cout << "Opening account of type [savings/checkings/both/cancel]: ";
            
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
                cout << "Open acount action cancelled" << endl;
                validAccountType = true;
            }
            else {
                Logger::Error() << "Invalid account type!" << endl;
            }
        }
        
        
        if (accountType == Savings || type.compare("both") == 0 ){
            if( currentUser.savingsAccount.exists || data->DoesAccountExist(currentUser, Savings) ) {
                Logger::Error() << "This Savings account already exists!" << endl;
            } else {
                bool validBalance = false;
                double inputBalance = -1;
                while (!validBalance){
                cout << "Starting balance of savings account [ $ ]: ";
                cin >> inputBalance;
                    if (inputBalance >= 0){
                        validBalance = true;
                    }
                }
                currentUser.savingsAccount.SetBalance(inputBalance); // sets the value in the class
                currentUser.savingsAccount.exists = true; // Boolean flag in account class
                data->CreateSavingsAccount(currentUser,inputBalance); // Creates the file with contents identical to class.
                
            }
        }
         
        if (accountType == Checking || type.compare("both") == 0){
            
            if (currentUser.checkingAccount.exists || data->DoesAccountExist(currentUser, Checking) ){
                Logger::Error() << "This Checking account already exists!" << endl;
            } else {
                bool validBalance = false;
                double inputBalance = -1;
                while (!validBalance){
                    cout << "Starting balance of checking account [ $ ]: ";
                    cin >> inputBalance;
                    if (inputBalance >= 0){
                        validBalance = true;
                    }
                }
                currentUser.checkingAccount.SetBalance(inputBalance); // sets the value in the class
                currentUser.checkingAccount.exists = true; // Boolean flag in account class
                data->CreateCheckingAccount(currentUser,inputBalance); // Creates the file with contents identical to class.
                
            }
            
        }
        } // Exit of else/if of checking if both accounts already exist.
        EXIT( "AccountBalanceOperation::Execute" );
    }
}