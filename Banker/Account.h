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
        Savings, Checking, CreditCard
    };
    
    class Account {
    public:
        AccountType Type;
        double Balance;
        
        
        Account( AccountType actType, double balance);
        void deposit( double value );
        void withdraw( double value );
        bool pinCheck ( int input );
        
        
        
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
                case CreditCard:
                    toReturn = "Credit";
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
            } else if (type.compare("Credit") == 0) {
                toReturn = CreditCard;
            }
            
            EXIT( "Account::typeFromString" );
            return toReturn;
        }
        
        
        
        private: int pinNumber;
        
    };
}

#endif /* defined(__Banker__Account__) */
