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
    void AccountBalanceOperation::execute( OptionContext context ) {
        ENTER( "AccountBalanceOperation::Execute" );
        
        User user = context.getSession().getUser();
        
        if( user.Role == Manager ) {
            string username;
            cout << "Please enter the username of the customer: ";
            cin >> username;

            if ( context.getData().doesUserExist(username) ) {
                user = context.getData().getUser( username );
            } else {
                Logger::error() << "Client does not exist!" << endl;
                EXIT( "AccountBalanceOperation::Execute" );
                return;
            }
        }
        
        displayAccountDetails( context, user );
        
        EXIT( "AccountBalanceOperation::Execute" );
    }
}