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
#include "User.h"
#include "Account.h"

using namespace std;
using namespace Accounts;
using namespace Authentication;

namespace Data {
    class IData {
    public:
        virtual ~IData() {}
        
        virtual bool DoesUserExist( string& name ) = 0;
        virtual User& GetUser( string& name ) = 0;
        virtual void CreateUser( const User& user ) = 0;
        
        virtual bool DoesAccountExist( const User& user, AccountType type ) = 0;
        virtual Account& GetAccount( const User& user, AccountType type ) = 0;
        virtual void StoreAccount( const User& user, const Account& account ) = 0;
    };
}

#endif /* defined(__Banker__Data__) */
