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
        User fromUser = context.getSession().getUser();
        User toUser = context.getSession().getUser();
        AccountType from, to;
        
        string internalExternalChoice;
        cout << "Would you like to transfer between accounts, (Ex: Savings to Checkings) or transfer to another user (Doe to Smith)? [account/customer/cancel]: ";
        cin >> internalExternalChoice;
        bool isBetweenCustomers = internalExternalChoice.compare( "customer" )==0;
        bool cancel = internalExternalChoice.compare ( "cancel" ) == 0;
    
        // get destination username if transfering between customers
        if ( !cancel && isBetweenCustomers ) {
            string destinationUsername;
            while( true ) {
                Logger::info() << "Please enter destination username (type cancel to cancel): ";
                cin >> destinationUsername;
                if( destinationUsername.compare("cancel") == 0 ) {
                    cancel = true;
                    break;
                } else if( data.doesUserExist( destinationUsername ) ) {
                    toUser = data.getUser( destinationUsername );
                    break;
                } else {
                    Logger::error() << "User " << destinationUsername << " does not exist" << endl;
                }
            }
        }

        // get account to transfer from
        while( !cancel && true ) {
            string type;
            cout << "Transfer from account [savings/checkings/cancel]: ";
            cin >> type;
            
            if ( type.compare ("cancel" ) == 0){
                cancel = true;
                break;
            } else if( type.compare("savings") == 0 ) {
                from = Savings;
                break;
            } else if ( type.compare( "checkings" ) == 0 ) {
                from = Checking;
                break;
            } else {
                Logger::error() << "Invalid account type!" << endl;
            }
        }
        
        // get destination account
        if( !cancel && isBetweenCustomers ) {
            while( true ) {
                string type;
                cout << "Transfer to account [savings/checkings/cancel]: ";
                cin >> type;
                
                if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "Transfer action cancelled" << endl;
                    break;
                } else if( type.compare("savings") == 0 ) {
                    to = Savings;
                    break;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    to = Checking;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
        } else if( !cancel && !isBetweenCustomers ) {
            if( from == Savings ) {
                to = Checking;
            } else {
                to = Savings;
            }
        }
        
        // check if accounts exist; if all good, do transfer
        if( !cancel ) {
            if ( data.doesAccountExist( fromUser, from ) == false ) {
                Logger::error() << "Source account does not exist! Please open the missing account." << endl;
            } else if( data.doesAccountExist( fromUser, to ) == false ){
                Logger::error() << "Destination account does not exist! Please open the missing account." << endl;
            } else {
                transfer(fromUser, toUser, from, to, data );
            }
        }

        if( cancel ) {
            Logger::info() << "Transfer action cancelled" << endl;
        }
        
        EXIT( "TransferOperation::Execute" );
    }
    
    
    void TransferOperation::transfer( User& fromUser, User& toUser, AccountType fromAccount, AccountType toAccount, IData& data ) {
        ENTER( "TransferOperation::transferExternal" );
        
        Account transferFrom = data.getAccount( fromUser, fromAccount );
        Account transferTo = data.getAccount( toUser,toAccount );
        
        double transferAmount = 0;
        cout << "Amount to transfer from " << Account::typeToString( fromAccount ) << " to " << Account::typeToString( toAccount ) << " [ $ ]: ";
        cin >> transferAmount;
        
        transferFrom.withdraw( transferAmount );
        transferTo.deposit( transferAmount );
        
        data.storeAccount( fromUser, transferFrom );
        data.storeAccount( toUser, transferTo );
        
        EXIT( "TransferOperation::transfer" );
    }

}

