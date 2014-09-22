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

    void TransferOperation::Execute( OptionContext context ) {
        ENTER( "TransferOperation::Execute" );
        
        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        if (data.DoesAccountExist(user, Savings) == false || data.DoesAccountExist(user, Checking) == false){
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
                    transfer( Savings, Checking, context );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::Info() << "Withdraw action cancelled" << endl;
                    break;
                } else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
            
        }
        
        EXIT( "TransferOperation::Execute" );
    }
    
    void TransferOperation::transfer( AccountType from, AccountType to, OptionContext& context ) {
        ENTER( "TransferOperation::transfer" );

        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        
        Account transferFrom = data.GetAccount(user, from);
        Account transferTo = data.GetAccount(user,to);
        
        double transferAmount = 0;
        cout << "Amount to transfer from " << Account::typeToString( from ) << " to " << Account::typeToString( to ) << " [ $ ]: ";
        cin >> transferAmount;
        
        transferFrom.Withdraw( transferAmount );
        transferTo.Deposit( transferAmount );
        
        data.StoreAccount( user, transferFrom );
        data.StoreAccount( user, transferTo );
        
        EXIT( "TransferOperation::transfer" );
    }

}
