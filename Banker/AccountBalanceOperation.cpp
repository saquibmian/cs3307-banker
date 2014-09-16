//
//  AccountBalanceOperation.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "AccountBalanceOperation.h"
#include "Account.h"
#include "Logger.h"

using namespace Accounts;

namespace Operations {
    void AccountBalanceOperation::Execute( OptionContext context ) {
        ENTER( "AccountBalanceOperation::Execute" );

        AccountType accountType = getAccountType();

        if( !context.GetData().DoesAccountExist(context.GetUser(), accountType) ) {
            Logger::Error() << "The specified account does not exist!" << endl;
        } else {
            Account act = context.GetData().GetAccount( context.GetUser(), accountType );
            cout << "Balance: " << act.Balance;
        }
        
        EXIT( "AccountBalanceOperation::Execute" );
    }
}