//
//  ViewPaymentOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "ViewPaymentOperation.h"
#include "Logger.h"
#include "FileIo.h"
#include <vector>
#include <cctype>

namespace Operations {
    
    void ViewPaymentOperation::execute(OptionContext context){
        ENTER("ViewPaymentOperation::execute");
        
        IData& data = context.getData();
        User manager = context.getSession().getUser();
        
        if( manager.Role == Manager ) {
            string username;
            cout << "Please enter the username of the customer: ";
            cin >> username;
            
            if ( context.getData().doesUserExist(username) ) {
                User user = context.getData().getUser( username );
                
                /////////////
                
                if (data.doesAccountExist(user,CreditCard)){
                    //User user = context.getSession().getUser();
                    vector<string> transactionContents = Io::readAllLinesFromFile
                    (Configuration::dataDirectory+"/"+user.Name+".creditcard.dat.payments.dat");
                    
                    for ( int i = 0; i <= transactionContents.size()-1; i++){
                        
                        cout << transactionContents[i] << endl;
                        
                    }
                }
                
                /////////////
                
            } else {
                Logger::error() << "Client does not exist!" << endl;
                EXIT( "AccountBalanceOperation::Execute" );
                return;
            }
        }
        
    }
    
    
}