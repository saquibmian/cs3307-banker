//
//  Account.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Account.h"

using namespace std;

namespace Accounts{
    Account::Account( AccountType inputType, double inputBalance ){
        Balance = inputBalance;
        Type = inputType;
    }
    void Account::Withdraw (double withdrawAmount){
        Balance -= withdrawAmount;
    }
    void Account::Deposit(double depositAmount){
        Balance += depositAmount;
    }
    
}