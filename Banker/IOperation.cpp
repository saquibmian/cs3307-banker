//
//  IOperation.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "IOperation.h"
#include "Logger.h"

namespace Operations {
    AccountType IOperation::getAccountType() {
        ENTER( "IOperation::getAccountType" );
        
        AccountType accountType;
        
        bool validAccountType = false;
        
        while( !validAccountType ) {
            cout << "Type of account [savings/checkings]: ";
            string type;
            cin >> type;
            if( type.compare("savings") == 0 ) {
                accountType = Savings;
                validAccountType = true;
            } else if ( type.compare( "checkings" ) == 0 ) {
                accountType = Checking;
                validAccountType = true;
            } else if (type.compare ( "credit" ) == 0){
                accountType = CreditCard;
                validAccountType = true;
            } else{
                Logger::error() << "Invalid account type!" << endl;
            }
        }
        
        EXIT( "IOperation::getAccountType" );
        return accountType;
    }
    
    void IOperation::displayAccountDetails( OptionContext& context, User& user ) {
        ENTER( "IOperation::DisplayAccountDetails" );

        IData& data = context.getData();
        bool hasAtLeastOneAccount = false;
        if( data.doesAccountExist(user, Checking) ) {
            hasAtLeastOneAccount = true;
            Account act = context.getData().getAccount( user, Checking );
            cout << "Checking balance: $" << act.Balance <<endl;
        }
        if( data.doesAccountExist(user, Savings) ) {
            hasAtLeastOneAccount = true;
            Account act = context.getData().getAccount( user, Savings );
            cout << "Savings balance: $" << act.Balance << endl;
        }
        if ( data.doesAccountExist(user, CreditCard) ){
            hasAtLeastOneAccount = true;
            Account act = context.getData().getAccount(user, CreditCard);
            cout << "Credit Card Balance: $" << act.Balance << endl;
            
        }
        //ADD CREDIT CARD EXCEPTIONS
        if( !hasAtLeastOneAccount) {
            Logger::warn() << "The specified user '" << user.Name << "' does not have any accounts." << endl;
        }
        
        EXIT( "IOperation::DisplayAccountDetails" );
    }
}
