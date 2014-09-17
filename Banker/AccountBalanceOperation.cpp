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
        
        User user = context.GetUser();
        
        if( context.GetUser().Role == Manager ) {
            string username;
            cout << "Please enter the username of the customer: ";
            cin >> username;

            if ( context.GetData().DoesUserExist(username) ) {
                user = context.GetData().GetUser( username );
            } else {
                Logger::Error() << "Client does not exist!" << endl;
                EXIT( "AccountBalanceOperation::Execute" );
                return;
            }
        }
        
        DisplayAccountDetails( context, user );
        
        EXIT( "AccountBalanceOperation::Execute" );
    }
}