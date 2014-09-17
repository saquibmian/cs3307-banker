//
//  AllClientsBalanceOpertion.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "AllClientsBalanceOperation.h"
#include "Account.h"
#include "Logger.h"

using namespace Accounts;

namespace Operations {
    void AllClientsBalanceOperation::Execute( OptionContext context ) {
        ENTER( "AllClientsBalanceOperation::Execute" );
        
        vector<User> users = context.GetData().getAllUsers();
        for ( vector<User>::iterator iter = users.begin(); iter != users.end(); iter++ ) {
            User* user = iter.base();
            if( user->Role == Client ) {
                cout << "Client " << user->Name << endl;
                DisplayAccountDetails( context, *user );
                cout << endl;
            }
        }
        
        EXIT( "AllClientsBalanceOperation::Execute" );
    }
}