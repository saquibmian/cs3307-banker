//
//  FilesystemData.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "FilesystemData.h"
#include "Definitions.h"
#include "Logger.h"

namespace Data {
    
    bool FilesystemData::DoesUserExist( string name ) {
        ENTER( "FilesystemData::DoesUserExist" );
        string dirPath = Configuration::DataDirectory + "/" + name;
        bool toReturn = dirExists( dirPath );
        
        EXIT( "FilesystemData::DoesUserExist" );
        return toReturn;
    }
    
    User FilesystemData::GetUser( string name ) {
        ENTER( "FilesystemData::GetUser" );
        
        if( !DoesUserExist(name) ) {
            Logger::Error() << "No such user";
            throw std::exception();
        }
        
        User toReturn( name );
        EXIT( "FilesystemData::GetUser" );
        return toReturn;
    }
    
    void FilesystemData::CreateUser( string name ) {
        ENTER( "FilesystemData::CreateUser" );
        
        if( DoesUserExist( name ) ) {
            Logger::Error() << "User already exists!" <<endl;
            throw std::exception();
        }
        createFile( getUserPath( name ), " ");
        
        EXIT( "FilesystemData::CreateUser" );
    }
    
    bool FilesystemData::DoesAccountExist( User user, AccountType type ) {
        ENTER( "FilesystemData::DoesAccountExist" );
        
        bool toReturn = fileExists(getAccountPath(user.GetName(), type));
        
        EXIT( "FilesystemData::DoesAccountExist" );
        return toReturn;
    }
    
    Account FilesystemData::GetAccount( User user, AccountType type ) {
        ENTER( "FilesystemData::GetAccount" );
        
        if( !DoesAccountExist(user, type) ) {
            Logger::Error() << "User account doesn't exist!" << endl;
            throw std::exception();
        }
        
        Account account;
        initFromFile(getAccountPath(user.GetName(), type), account.Balance);
        
        return account;
    }
    
    void FilesystemData::StoreAccount( User user, Account account ) {
        ENTER( "FilesystemData::StoreAccount" );
        
        if( DoesAccountExist(user, account.Type) ) {
            Logger::Error() << "User account already exists!" << endl;
            throw std::exception();
        }
        
        createFile(getAccountPath(user.GetName(), account.Type), account.Balance);
        
        EXIT( "FilesystemData::StoreAccount" );
    }
    
    string FilesystemData::getAccountPath( string username, AccountType type ) {
        ENTER( "FilesystemData::getAccountPath" );
        
        string toReturn;
        switch ( type ) {
            case Accounts::Savings:
                toReturn = getSavingsAccountPath(username);
                break;
            case Accounts::Checking:
                toReturn = getSavingsAccountPath(username);
                break;
        }
        
        EXIT( "FilesystemData::getAccountPath" );
        return toReturn;
    }
    
    inline string FilesystemData::getSavingsAccountPath( string userName ) {
        ENTER( "FilesystemData::getSavingsAccountPath" );
        
        string path = Configuration::DataDirectory + "/" + userName + ".savings.dat";
        
        EXIT( "FilesystemData::getSavingsAccountPath" );
        return path;
    }
    
    inline string FilesystemData::getCheckingAccountPath( string userName ) {
        ENTER( "FilesystemData::getSavingsAccountPath" );
        
        string path = Configuration::DataDirectory + "/" + userName + ".checking.dat";
        
        EXIT( "FilesystemData::getSavingsAccountPath" );
        return path;
    }
    
    inline string FilesystemData::getUserPath( string userName ) {
        ENTER( "FilesystemData::getSavingsAccountPath" );
        
        string path = Configuration::DataDirectory + "/" + userName + ".dat";
        
        EXIT( "FilesystemData::getSavingsAccountPath" );
        return path;
    }
    
    bool FilesystemData::dirExists( string path ) {
        ENTER( "FilesystemData::dirExists" );
        struct stat info;
        bool toReturn;
        
        if( stat( path.c_str(), &info ) != 0 )
            toReturn = false;
        else if( info.st_mode & S_IFDIR )
            toReturn = true;
        else
            toReturn = false;
        
        EXIT( "FilesystemData::dirExists" );
        return toReturn;
    }
    
    bool FilesystemData::fileExists( string path ) {
        ENTER( "FilesystemData::fileExists" );
        struct stat info;
        bool toReturn;
        
        if( stat( path.c_str(), &info ) != 0 )
            toReturn = false;
        else if( info.st_mode & S_IFDIR )
            toReturn = false;
        else
            toReturn = true;
        
        EXIT( "FilesystemData::fileExists" );
        return toReturn;
    }
    
    template< class T> void FilesystemData::createFile( string path, T& data ) {
        ENTER( "FilesystemData::createFile" );
        
        ofstream myfile;
        myfile.open( path.c_str(), ios::out | ios::binary );
        myfile << data;
        myfile.close();
        
        EXIT( "FilesystemData::createFile" );
    }
    
    template< class T> void FilesystemData::initFromFile( string path, T& data ) {
        ENTER( "FilesystemData::initFromFile" );
        
        ifstream myfile;
        myfile.open( path.c_str(), ios::in | ios::binary );
        myfile >> data;
        myfile.close();
        
        EXIT( "FilesystemData::initFromFile" );
    }
}