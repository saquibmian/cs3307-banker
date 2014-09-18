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
        bool dirExists( string path );
        bool fileExists( string path );
        void createDirectory( string path );
        void deleteFile( string path );
        template< class T> void createFile( string path, T& data );
        template< class T> void appendLineToFile( string path, T& data );
        template< class T> void initFromFile( string path, T& data );
        vector<string> readAllLinesFromFile( string path );
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




