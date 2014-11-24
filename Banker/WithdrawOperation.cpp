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
    
    void WithdrawOperation::execute( OptionContext context ) {
        ENTER( "WithdrawOperation::Execute" );
        
        IData* data = &context.getData();
        User currentUser = context.getSession().getUser();
        
        if (data->doesAccountExist(currentUser, Savings) == false && data->doesAccountExist(currentUser, Checking) == false){
            Logger::error() << "No open account exists!" << endl;
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
                    Logger::info() << "Withdraw action cancelled" << endl;
                    validAccountType = true;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
        }
     
        EXIT( "WithdrawOperation::Execute" );
    }
    
    
    void WithdrawOperation::vendorPurchase( OptionContext context, double purchasePrice ) {
        ENTER( "WithdrawOperation::vendorPurchase" );
       /*
        IData& data = context.getData();
        User currentUser = context.getSession().getUser();
        
        if (data.doesAccountExist(currentUser, CreditCard) == false){
            Logger::error() << "No account exists!" << endl;
        }
        else{
            
            Account creditAccount = data.getAccount ( currentUser, CreditCard );
            creditAccount.withdraw( purchasePrice );
            data.storeAccount( currentUser, creditAccount );
            
            
        }
        EXIT ( "WithdrawOperation::vendorPurchase" );
        */
        
    }
    
    void WithdrawOperation::withdrawFromAccount( OptionContext &context, AccountType type) {
        ENTER( "WithdrawOperation::withdrawFromAccount" );

        IData& data = context.getData();
        User& user = context.getSession().getUser();
        Account account = data.getAccount( user, type );
        
        double toWithdraw=0;
        cout << "Amount to withdraw from account [ $ ]: ";
        cin >> toWithdraw;
        
        if ( type == Checking && account.Balance - toWithdraw < 1000 ){
            Logger::warn() << "A $2.00 fee will be applied to this transaction. Continue? [y/n]: ";
            
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
            Logger::error() << "Invalid. The balance will be less than 0. Overdraft is not enabled" << endl;
        } else {
            account.withdraw( toWithdraw );
            data.storeAccount( user, account );
        }
        
        Logger::info() << "The remaining balance is $" << account.Balance << endl;
        
        EXIT( "WithdrawOperation::withdrawFromAccount" );
    }
    
}
