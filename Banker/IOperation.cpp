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
            } else {
                Logger::Error() << "Invalid account type!" << endl;
            }
        }
        
        EXIT( "IOperation::getAccountType" );
        return accountType;
    }
    
    void IOperation::DisplayAccountDetails( OptionContext& context, User& user ) {
        ENTER( "IOperation::DisplayAccountDetails" );

        IData& data = context.GetData();
        bool hasAtLeastOneAccount = false;
        if( data.DoesAccountExist(user, Checking) ) {
            hasAtLeastOneAccount = true;
            Account act = context.GetData().GetAccount( user, Checking );
            cout << "Checking balance: $" << act.Balance <<endl;
        }
        if( data.DoesAccountExist(user, Savings) ) {
            hasAtLeastOneAccount = true;
            Account act = context.GetData().GetAccount( user, Savings );
            cout << "Savings balance: $" << act.Balance << endl;
        }
        
        if( !hasAtLeastOneAccount) {
            Logger::Error() << "The specified client does not have any accounts; please create one." << endl;
        }
        
        EXIT( "IOperation::DisplayAccountDetails" );
    }
}