//
//  Account.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Account.h"

namespace Accounts{
    Account::Account(AccountType inputType, double inputBalance){
        Balance = inputBalance;
        Type = inputType;
        exists = false;
    }
    Account::Account(){
        Balance = -400;
        Type = Savings;
        exists = false;
    }
    void Account::OpenAccount(){
        exists = true; // This should only be true if someone has manually created the account.
    }
    void Account::SetBalance(double inputBalance){
        Balance = inputBalance;
    }
    double Account::Withdraw (double withdrawAmount){
        Balance -= withdrawAmount;
        return Balance; // Returns new amount after withdraw has been completed.
    }
    double Account::Deposit(double depositAmount){
        Balance += depositAmount;
        return Balance; // Returns new amount after deposit is done.
    }
    
    bool Account::getExist(){
        
        return exists;
    }
}