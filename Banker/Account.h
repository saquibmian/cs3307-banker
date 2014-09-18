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

namespace Accounts {
    enum AccountType {
        Savings, Checking
    };
    class Account {
    public:
        AccountType Type;
        double Balance;
        Account(AccountType actType, double balance);
        Account();
        bool exists = false;
        void OpenAccount();
        void SetBalance(double);
        double Deposit(double);
        double Withdraw(double);
        //double Transfer( ); May come back to. May have the transfer be done as a combination of Deposit and Withdraw.
    };
}

#endif /* defined(__Banker__Account__) */
