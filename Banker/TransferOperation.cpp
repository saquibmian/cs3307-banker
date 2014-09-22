//
//  TransferOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"
#include "TransferOperation.h"

using namespace Accounts;
using namespace Data;

namespace Operations{

    void TransferOperation::execute( OptionContext context ) {
        ENTER( "TransferOperation::Execute" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        if (data.doesAccountExist(user, Savings) == false || data.doesAccountExist(user, Checking) == false){
            cout << "Both accounts do not exist! Please open the missing account." << endl;
        } else{
            bool validAccountType = false;
            string type;
            while( !validAccountType ) {
                cout << "Transfer from account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    transfer( Savings, Checking, context );
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    transfer( Checking, Savings, context );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "Withdraw action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
            
        }
        
        EXIT( "TransferOperation::Execute" );
    }
    
    void TransferOperation::transfer( AccountType from, AccountType to, OptionContext& context ) {
        ENTER( "TransferOperation::transfer" );

        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        Account transferFrom = data.getAccount(user, from);
        Account transferTo = data.getAccount(user,to);
        
        double transferAmount = 0;
        cout << "Amount to transfer from " << Account::typeToString( from ) << " to " << Account::typeToString( to ) << " [ $ ]: ";
        cin >> transferAmount;
        
        transferFrom.withdraw( transferAmount );
        transferTo.deposit( transferAmount );
        
        data.storeAccount( user, transferFrom );
        data.storeAccount( user, transferTo );
        
        EXIT( "TransferOperation::transfer" );
    }

}

