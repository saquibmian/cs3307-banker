//
//  Account.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Account__
#define __Banker__Account__

#include <iostream>
#include "Logger.h"

using namespace std;

namespace Accounts {
    enum AccountType {
        Savings, Checking
    };
    
    class Account {
    public:
        AccountType Type;
        double Balance;
        Account( AccountType actType, double balance);
        void deposit( double value );
        void withdraw( double value );
        
        static string typeToString( AccountType type ) {
            ENTER( "Account::typeToString" );
            
            string toReturn;
            switch ( type ) {
                case Savings:
                    toReturn = "Savings";
                    break;
                case Checking:
                    toReturn = "Checking";
                    break;
            }
            
            EXIT( "Account::typeToString" );
            return toReturn;
        }
        static AccountType typeFromString( string type ) {
            ENTER( "Account::typeFromString" );

            AccountType toReturn;
            if( type.compare("Checking") == 0 ) {
                toReturn = Checking;
            } else if( type.compare("Savings") == 0 ) {
                toReturn = Savings;
            }
            
            EXIT( "Account::typeFromString" );
            return toReturn;
        }
    };
}

#endif /* defined(__Banker__Account__) */
