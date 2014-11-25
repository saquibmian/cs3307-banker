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
        
        virtual bool doesUserExist( string name ) = 0;
        virtual User getUser( string name ) = 0;
        virtual vector<User> getAllUsers() = 0;
        virtual void createUser( string name, UserRole role = Client ) = 0;

        virtual bool doesAccountExist( User user, AccountType type ) = 0;
        virtual Account getAccount( User user, AccountType type ) = 0;
        virtual void storeAccount( User user, Account account ) = 0;
        virtual void storePin (User user, Account account, string pin) = 0;
        virtual void storeCreditLimit (User user, Account account) = 0;
        virtual void closeAccountForUser( User user, AccountType type ) = 0;
        virtual void storeTransaction ( string username, AccountType accountType, string transaction ) = 0;
    };
}

#endif /* defined(__Banker__Data__) */
