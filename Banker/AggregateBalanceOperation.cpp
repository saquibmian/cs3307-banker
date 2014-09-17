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
    void AggregateBalanceOperation::Execute( OptionContext context ) {
        ENTER( "AggregateBalanceOperation.h::Execute" );
        
        int totalCheckingBalance = 0;
        int totalSavingsBalance = 0;
        vector<User> users = context.GetData().getAllUsers();
        for ( vector<User>::iterator iter = users.begin(); iter != users.end(); iter++ ) {
            User* user = iter.base();
            if( user->Role == Client ) {
                
                if( context.GetData().DoesAccountExist(*user, Checking) ) {
                    Account checking = context.GetData().GetAccount(*user, Checking);
                    totalCheckingBalance += checking.Balance;
                }
                
                if( context.GetData().DoesAccountExist(*user, Savings) ) {
                    Account checking = context.GetData().GetAccount(*user, Savings);
                    totalSavingsBalance += checking.Balance;
                }
            }
        }
        
        cout << "Total checking balance: $" << totalCheckingBalance << endl;
        cout << "Total savings balance: $" << totalSavingsBalance << endl;
        
        EXIT( "AggregateBalanceOperation.h::Execute" );
    }
}