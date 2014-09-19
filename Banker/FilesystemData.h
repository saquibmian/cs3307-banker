//
//  FilesystemData.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__FilesystemData__
#define __Banker__FilesystemData__

#include <vector>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "Data.h"

namespace Data {
    class FilesystemData : public IData {
    private:
        inline string getUserPath( string userName );
        string getAccountPath( string username, AccountType type );
        inline string getAccountListPath();
    public:
        virtual void initialize();
        virtual bool DoesUserExist( string name );
        virtual vector<User> getAllUsers();
        virtual User GetUser( string name );
        virtual void CreateSavingsAccount (User user, double inputBalance);
        virtual void CreateCheckingAccount (User user,double inputBalance);
        virtual void CloseSavingsAccount(User user);
        virtual void CloseCheckingAccount (User user);
        virtual void CreateUser( string name, UserRole role = Client );
        virtual bool DoesAccountExist( User user, AccountType type );
        virtual Account GetAccount( User user, AccountType type );
        virtual void StoreAccount( User user, Account account );
        virtual void UpdateAccount ( User user, Account account );
    };
}

#endif /* defined(__Banker__FilesystemData__) */




