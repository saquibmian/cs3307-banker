//
//  Data.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Data__
#define __Banker__Data__

#include <iostream>
#include <vector>
#include "User.h"
#include "Account.h"

using namespace std;
using namespace Accounts;
using namespace Authentication;

namespace Data {
    class IData {
    public:
        virtual ~IData() {}
        
        virtual void initialize() = 0;
        
        virtual bool DoesUserExist( string name ) = 0;
        virtual User GetUser( string name ) = 0;
        virtual vector<User> getAllUsers() = 0;
        virtual void CreateUser( string name, UserRole role = Client ) = 0;
        virtual void CreateSavingsAccount ( User user, double inputBalance ) = 0;
        virtual void CreateCheckingAccount ( User user, double inputBalance ) = 0;
        virtual void CloseSavingsAccount(User user) = 0;
        virtual void CloseCheckingAccount (User user) = 0;
        virtual bool DoesAccountExist( User user, AccountType type ) = 0;
        virtual Account GetAccount( User user, AccountType type ) = 0;
        virtual void StoreAccount( User user, Account account ) = 0;
    };
}

#endif /* defined(__Banker__Data__) */
