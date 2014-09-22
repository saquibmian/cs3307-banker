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
        virtual ~FilesystemData() { }
        
        virtual void initialize();
        
        virtual bool DoesUserExist( string name );
        virtual User GetUser( string name );
        virtual vector<User> getAllUsers();
        virtual void CreateUser( string name, UserRole role = Client );
        
        virtual bool DoesAccountExist( User user, AccountType type );
        virtual Account GetAccount( User user, AccountType type );
        virtual void StoreAccount( User user, Account account );
        virtual void closeAccountForUser( User user, AccountType type );
    };
}

#endif /* defined(__Banker__FilesystemData__) */




