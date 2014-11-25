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
        
        virtual bool doesUserExist( string name );
        virtual User getUser( string name );
        virtual vector<User> getAllUsers();
        virtual void createUser( string name, UserRole role = Client );
        
        virtual bool doesAccountExist( User user, AccountType type );
        virtual Account getAccount( User user, AccountType type );
        virtual void storeAccount( User user, Account account );
        virtual void storePin ( User user, Account account, string pin );
        virtual bool checkPin ( User user, string inputPin );
        virtual void storeCreditLimit ( User user, Account account );
        virtual void closeAccountForUser( User user, AccountType type );
        virtual void storeTransaction ( string username, AccountType accountType, string transaction );
    };
}

#endif /* defined(__Banker__FilesystemData__) */




