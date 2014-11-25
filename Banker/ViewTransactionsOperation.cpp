//
//  ViewTransactionsOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-24.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "ViewTransactionsOperation.h"
#include "Logger.h"
#include "FileIo.h"
#include <vector>
#include <cctype>


namespace Operations {
    
    void ViewTransactionsOperation::execute(Options::OptionContext context){
        ENTER ("ViewTransactionsOperation::execute");
        
        IData& data = context.getData();
        
        if (data.doesAccountExist(context.getSession().getUser(),CreditCard)){
        User user = context.getSession().getUser();
        vector<string> transactionContents = Io::readAllLinesFromFile
        (Configuration::dataDirectory+"/"+user.Name+".creditcard.transactions.dat");
        
        for ( int i = 0; i <= transactionContents.size()-1; i++){
            
            cout << transactionContents[i] << endl;
            
        }
        
            Account act = context.getData().getAccount(user,CreditCard);
        
            double balance = act.Balance*-1;
            
            if (balance >= (context.getData().getAccount(user,Checking).Balance)){
                cout << "Warning: Balance on your credit card is more than 75% of your checking account" << endl;
            }
            cout << "Balance on credit card is $" << balance;
            
            
        }
        else{
            
        }
        
        
    }
    
    
}