//
//  CreditLimitOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "CreditLimitOperation.h"
#include "FileIo.h"

namespace Operations {
    void CreditLimitOperation::execute( OptionContext context ) {
        ENTER( "CreditLimitOperation::Execute" );
        
        User user = context.getSession().getUser();
        
        if( user.Role == Manager ) {
            string username;
            cout << "Please enter the username of the customer: ";
            cin >> username;
            
            if ( context.getData().doesUserExist(username) ) {
                user = context.getData().getUser( username );
                if (context.getData().doesAccountExist(user, CreditCard)){
                    
                    double creditLimit;
                    cout << "Set credit limit for " + user.Name + " [$]: ";
                    cin >> creditLimit;
                    
                    Io::createFile(Configuration::dataDirectory + "/" + username + ".creditcard.dat.creditlimit.dat",creditLimit);
                    
                    
                }
            } else {
                Logger::error() << "Client does not exist!" << endl;
                EXIT( "AccountBalanceOperation::Execute" );
                return;
            }
        }
        
        //displayAccountDetails( context, user );
        
        EXIT( "CreditLimitOperation::Execute" );
    }
}
