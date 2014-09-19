//
//  User.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "User.h"
#include "Account.h"

using namespace Authentication;
using namespace Accounts;
namespace Authentication {
    
    User::User( string name, UserRole role ) {
        
        Name = name;
        Role = role;
        //savingsAccount.Type = Savings;
        //checkingAccount.Type = Checking;
        
        Account::Account savingsAccount(Savings,-400); // -400 causes a cannot exist flag later
        Account::Account checkingAccount(Checking,-400);
        
        
    }
    
    //User::User( string name, UserRole role ) : Name( name ), Role( role ), savingsAccount(Savings,0), checkingAccount(Checking,0) { }
    
    
    
   // Account User::getCheckingAccount(){
        
        
     //   return NULL;
   // }
    
    ostream& operator<<( ostream &strm, const User &user ) {
        return strm << user.Name;
    }
    
    
    
}
