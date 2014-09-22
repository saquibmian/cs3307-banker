//
//  WithdrawOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "WithdrawOperation.h"
#include "Account.h"
#include "Logger.h"
#include "FilesystemData.h"

using namespace Accounts;
using namespace Data;


namespace Operations {
    
    void WithdrawOperation::Execute( OptionContext context ) {
        ENTER( "WithdrawOperation::Execute" );
        
        IData* data = &context.GetData();
        User currentUser = context.GetSession().getUser();
        
        if (data->DoesAccountExist(currentUser, Savings) == false && data->DoesAccountExist(currentUser, Checking) == false){
            Logger::Error() << "No open account exists!" << endl;
        } else{
            string type;
            bool validAccountType = false;
            while( !validAccountType ) {
                cout << "Any action causing a checking account to go, or on a checking account below $1000.00 has a $2.00 transaction fee" << endl;
                cout << "Withdraw from account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    withdrawFromAccount( context, Savings );
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    withdrawFromAccount( context, Checking );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::Info() << "Withdraw action cancelled" << endl;
                    validAccountType = true;
                } else {
                    Logger::Error() << "Invalid account type!" << endl;
                }
            }
        }
     
        EXIT( "WithdrawOperation::Execute" );
    }
    
    void WithdrawOperation::withdrawFromAccount( OptionContext &context, AccountType type) {
        ENTER( "WithdrawOperation::withdrawFromAccount" );

        IData& data = context.GetData();
        User& user = context.GetSession().getUser();
        Account account = data.GetAccount( user, type );
        
        double toWithdraw=0;
        cout << "Amount to withdraw from account [ $ ]: ";
        cin >> toWithdraw;
        
        if ( type == Checking && account.Balance - toWithdraw < 1000 ){
            Logger::Warn() << "A $2.00 fee will be applied to this transaction. Continue? [y/n]: ";
            
            char yesno;
            cin >> yesno;
            if ( yesno == 'y' ){
                toWithdraw += 2;
            } else {
                EXIT( "WithdrawOperation::withdrawFromAccount" );
                return;
            }
        }

        if ( account.Balance - toWithdraw < 0 ){
            Logger::Error() << "Invalid. The balance will be less than 0. Overdraft is not enabled" << endl;
        } else {
            account.Withdraw( toWithdraw );
            data.StoreAccount( user, account );
        }
        
        Logger::Info() << "The remaining balance is $" << account.Balance << endl;
        
        EXIT( "WithdrawOperation::withdrawFromAccount" );
    }
    
}