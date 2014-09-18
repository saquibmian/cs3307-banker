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
        
        if ((Balance-withdrawAmount)<0){
            cout << "Invalid. The balance will be less than 0. Overdraft is not enabled" << endl;
        }
        else if (Type == Checking && (Balance - withdrawAmount) < 1000 ){ // It seemed silly not to do this as I was working on the withdraw.
            
            char yesno;
            
            cout << "A $2.00 fee will be applied to this transaction. Continue? [y/n]: ";
            cin >> yesno;
            
            if (yesno == 'y'){
                Balance = Balance - withdrawAmount - 2; // $2.00 fee as stated above.
            }
            
        }
        else{
        
        Balance -= withdrawAmount;
            
        }
        return Balance; // Returns new amount after withdraw has been completed.
    }
    double Account::Deposit(double depositAmount){
        Balance += depositAmount;
        return Balance; // Returns new amount after deposit is done.
    }
    
}