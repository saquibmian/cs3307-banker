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
        //User destinationUser = user;
        //string internalExternalChoice;
        
        /*cout << "Would you like to perform an internal transfer (Ex: Savings to Checkings) or an external transfer (Doe to Smith)? [internal/external/cancel]: ";
        cin >> internalExternalChoice;
        
        if (internalExternalChoice.compare("external")==0) {
            
            string destinationUsername;
            
            cout << "Please enter the name of the account to transfer to: " << endl;
            cin >> destinationUsername;
            
            if ( context.getData().doesUserExist(destinationUsername) ) {
                User destinationUser = context.getData().getUser( destinationUsername );
            } else {
                Logger::error() << "Client does not exist!" << endl;
                EXIT( "TransferOperation::Execute" );
                return;
            }
            
            cout << "Transfer from your Savings or Checking account? [checking/saving]: ";
            
            bool validAccountType;
            string destinationType;
            string type;
            
            while( !validAccountType ) {
                cout << "Transfer from account [savings/checkings/cancel]: ";
                
                cin >> type;
                if( type.compare("savings") == 0 ) {
                    
                    
                    ////////
                    
                    while( !validAccountType ) {

                        cout << "Transfer to " << destinationUsername << "'s Checking or Saving account? [checking/saving]: ";
                        cin >> type;
                        if( type.compare("savings") == 0 ) {
                            transferExternal(destinationUser, Savings, Savings, context );
                            validAccountType = true;
                        } else if ( type.compare( "checkings" ) == 0 ) {
                            transferExternal( destinationUser, Savings, Checking, context );
                            validAccountType = true;
                        } else if ( type.compare ("cancel" ) == 0){
                            Logger::info() << "Internal Transfer action cancelled" << endl;
                            break;
                        } else {
                            Logger::error() << "Invalid account type!" << endl;
                        }
                    }
                    
                    ///////
                    
                    validAccountType = true;
                    
                } else if ( type.compare( "checkings" ) == 0 ) {
                    
                    while( !validAccountType ) {
                        
                        cout << "Transfer to " << destinationUsername << "'s Checking or Saving account? [checking/saving]: ";
                        cin >> type;
                        if( type.compare("savings") == 0 ) {
                            transferExternal(destinationUser, Checking, Savings, context );
                            validAccountType = true;
                        } else if ( type.compare( "checkings" ) == 0 ) {
                            transferExternal( destinationUser, Checking, Checking, context );
                            validAccountType = true;
                        } else if ( type.compare ("cancel" ) == 0){
                            Logger::info() << "Internal Transfer action cancelled" << endl;
                            break;
                        } else {
                            Logger::error() << "Invalid account type!" << endl;
                        }
                    }
                    validAccountType = true;
                    
                } else if ( type.compare ("cancel" ) == 0){
                    Logger::info() << "Internal Transfer action cancelled" << endl;
                    break;
                } else {
                    Logger::error() << "Invalid account type!" << endl;
                }
            }
            
            validAccountType = false;
            type = "";
            
            
            //cout << "Transfer to " << destinationUsername << "'s Checking or Saving account? [checking/saving]: ";
            
            //Repeating myself here. Could maybe change this to a function?
            
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
        else if (internalExternalChoice.compare("internal")==0){ */
        
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
            
            
       // } // end internal external if statement.
        
       // else if (internalExternalChoice.compare ("cancel") == 0){
         //   Logger::info() << "Transfer action cancelled" << endl;
        //}
        
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
    
    /**
    void TransferOperation::transferExternal(User destinationUser, AccountType from, AccountType to, OptionContext& context ) {
        ENTER( "TransferOperation::transferExternal" );
        
        IData& data = context.getData();
        User& user = context.getSession().getUser();
        
        Account transferFrom = data.getAccount(user, from);
        Account transferTo = data.getAccount(destinationUser,to);
        
        double transferAmount = 0;
        cout << "Amount to transfer from " << Account::typeToString( from ) << " to " << Account::typeToString( to ) << " [ $ ]: ";
        cin >> transferAmount;
        
        transferFrom.withdraw( transferAmount );
        transferTo.deposit( transferAmount );
        
        data.storeAccount( user, transferFrom );
        data.storeAccount( destinationUser, transferTo );
        
        EXIT( "TransferOperation::transfer" );
    } **/

}

