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
        string internalExternalChoice;
        
        cout << "Would you like to perform an internal transfer (Ex: Savings to Checkings) or an external transfer (Doe to Smith)? [internal/external/cancel]: ";
        cin >> internalExternalChoice;
        
        if (internalExternalChoice.compare("external")==0) {
            
            
            
            _transferData = new FilesystemData();
            _transferSession = new Session( *_transferData );
            _transferContext = 0;
            
            _transferData->initialize();
            
            
            _transferSession->externalTransferHelper();
            
            
            
            _transferContext = new OptionContext( *_transferData, *_transferSession );
            
            OptionContext transferContext = *_transferContext;
            
            string destinationUsername;
            
            cout << "Please re-enter the name of the account to transfer to: ";
            cin >> destinationUsername;
            
            if ( transferContext.getData().doesUserExist(destinationUsername) ) {
                User destinationUser = transferContext.getData().getUser( destinationUsername );
            } else {
                Logger::error() << "Client does not exist!" << endl;
                EXIT( "TransferOperation::Execute" );
                return;
            }
            
            
            bool validAccountType;
            string destinationType;
            string type;
            
            while( !validAccountType ) {
                cout << "Transfer from account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    
                    
                    ////////
                    
                    while( !validAccountType ) {

                        cout << "Transfer to " << destinationUsername << "'s Checking or Saving account? [checkings/savings]: ";
                        cin >> type;
                        if( type.compare("savings") == 0 ) {
                            transferExternal(transferContext, Savings, Savings, context );
                            validAccountType = true;
                        } else if ( type.compare( "checkings" ) == 0 ) {
                            transferExternal( transferContext, Savings, Checking, context );
                            validAccountType = true;
                        } else if ( type.compare ("cancel" ) == 0){
                            Logger::info() << "External Transfer action cancelled" << endl;
                            break;
                        } else {
                            Logger::error() << "Invalid account type!" << endl;
                        }
                    }
                    
                    ///////
                    
                    validAccountType = true;
                    
                } else if ( type.compare( "checkings" ) == 0 ) {
                    
                    while( !validAccountType ) {
                        
                        cout << "Transfer to " << destinationUsername << "'s Checking or Saving account? [checkings/savings]: ";
                        cin >> type;
                        if( type.compare("savings") == 0 ) {
                            transferExternal( transferContext, Checking, Savings, context );
                            validAccountType = true;
                        } else if ( type.compare( "checkings" ) == 0 ) {
                            transferExternal( transferContext, Checking, Checking, context );
                            validAccountType = true;
                        } else if ( type.compare ("cancel" ) == 0){
                            Logger::info() << "External Transfer action cancelled" << endl;
                            break;
                        } else {
                            Logger::error() << "Invalid account type!" << endl;
                        }
                    }
                    validAccountType = true;
                    
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "External Transfer action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
            
            //Repeating myself here. Could maybe change this to a function?
            /*
            while( !validAccountType ) {
                cout << "Transfer from account [savings/checkings/cancel]: ";
                cout << "Is this ever entered?";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    transfer( Savings, Checking, context );
                    validAccountType = true;
                } else if ( type.compare( "checkings" ) == 0 ) {
                    transfer( Checking, Savings, context );
                    validAccountType = true;
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "Internal Transfer action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            } */

        
        }
        else if (internalExternalChoice.compare("internal")==0){
        
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
                        Logger::info() << "Internal Transfer action cancelled" << endl;
                        break;
                    } else {
                        Logger::error() << "Invalid account type!" << endl;
                    }
                }
            
        }
            
            
        } // end internal external if statement.
        
        else if (internalExternalChoice.compare ("cancel") == 0){
           Logger::info() << "Transfer action cancelled" << endl;
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
    
    
    void TransferOperation::transferExternal(OptionContext destinationContext, AccountType from, AccountType to, OptionContext& context ) {
        ENTER( "TransferOperation::transferExternal" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        IData& destinationData = destinationContext.getData();
        User& destinationUser = destinationContext.getSession().getUser();
        
        Account transferFrom = data.getAccount(user, from);
        Account transferTo = destinationData.getAccount(destinationUser,to);
        
        double transferAmount = 0;
        cout << "Amount to transfer from " << Account::typeToString( from ) << " to " << Account::typeToString( to ) << " [ $ ]: ";
        cin >> transferAmount;
        
        transferFrom.withdraw( transferAmount );
        transferTo.deposit( transferAmount );
        
        data.storeAccount( user, transferFrom );
        data.storeAccount( destinationUser, transferTo );
        
        EXIT( "TransferOperation::transfer" );
    }

}

