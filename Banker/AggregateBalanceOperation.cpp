//
//  AggregateBalanceOperation.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "AggregateBalanceOperation.h"
#include "Account.h"
#include "Logger.h"

using namespace Accounts;

namespace Operations {
    void AggregateBalanceOperation::execute( OptionContext context ) {
        ENTER( "AggregateBalanceOperation.h::Execute" );
        
        double totalCheckingBalance = 0;
        double totalSavingsBalance = 0;
        vector<User> users = context.getData().getAllUsers();
        for ( vector<User>::iterator iter = users.begin(); iter != users.end(); iter++ ) {
            User* user = iter.base();
            if( user->Role == Client ) {
                
                if( context.getData().doesAccountExist(*user, Checking) ) {
                    Account checking = context.getData().getAccount(*user, Checking);
                    totalCheckingBalance += checking.Balance;
                }
                
                if( context.getData().doesAccountExist(*user, Savings) ) {
                    Account checking = context.getData().getAccount(*user, Savings);
                    totalSavingsBalance += checking.Balance;
                }
            }
        }
        
        cout << "Total checking balance: $" << totalCheckingBalance << endl;
        cout << "Total savings balance: $" << totalSavingsBalance << endl;
        
        EXIT( "AggregateBalanceOperation.h::Execute" );
    }
}