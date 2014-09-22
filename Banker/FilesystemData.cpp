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
#include "FileIo.h"
#include <cstdio>
#include <stdio.h>

using namespace Io;

namespace Data {
    
    void FilesystemData::initialize() {
        if( !Io::fileExists( getAccountListPath() ) ) {
            Io::createFile(getAccountListPath(), "" );
        }
    }
    
    bool FilesystemData::DoesUserExist( string name ) {
        ENTER( "FilesystemData::DoesUserExist" );
        string path = getUserPath( name );
        bool toReturn = Io::fileExists( path );
        
        EXIT( "FilesystemData::DoesUserExist" );
        return toReturn;
    }
    
    User FilesystemData::GetUser( string name ) {
        ENTER( "FilesystemData::GetUser" );
        
        if( !DoesUserExist(name) ) {
            Logger::Error() << "No such user";
            throw std::exception();
        }
        
        string serRole;
        Io::initFromFile( getUserPath( name ), serRole );
        
        User toReturn( name, User::roleFromString(serRole) );
        
        EXIT( "FilesystemData::GetUser" );
        return toReturn;
    }
    
    vector<User> FilesystemData::getAllUsers() {
        vector<User> toReturn;
        
        vector<string> users = Io::readAllLinesFromFile( getAccountListPath() );
        for ( vector<string>::iterator iter = users.begin(); iter != users.end(); iter++ ) {
            if( !iter.base()->empty() ) {
                toReturn.push_back( GetUser( *iter.base() ) );
            }
        }
        
        return toReturn;
    }
    
    void FilesystemData::CreateUser( string name, UserRole role ) {
        ENTER( "FilesystemData::CreateUser" );
        
        if( DoesUserExist( name ) ) {
            Logger::Error() << "User already exists!" <<endl;
            throw std::exception();
        }
        string serRole = User::roleToString( role );
        Io::createFile( getUserPath( name ), serRole );
        Io::appendLineToFile(getAccountListPath(), name);
        
        EXIT( "FilesystemData::CreateUser" );
    }
        
    bool FilesystemData::DoesAccountExist( User user, AccountType type ) {
        ENTER( "FilesystemData::DoesAccountExist" );
        
        bool toReturn = Io::fileExists(getAccountPath(user.Name, type));
        
        EXIT( "FilesystemData::DoesAccountExist" );
        return toReturn;
    }
    
    Account FilesystemData::GetAccount( User user, AccountType type ) {
        ENTER( "FilesystemData::GetAccount" );
        
        if( !DoesAccountExist(user, type) ) {
            Logger::Error() << "User account doesn't exist!" << endl;
            throw std::exception();
        }
        
        Account account(type, 0);
        initFromFile(getAccountPath(user.Name, type), account.Balance);
        
        return account;
    }
    
    void FilesystemData::StoreAccount( User user, Account account ) {
        ENTER( "FilesystemData::StoreAccount" );
        
        Io::createFile(getAccountPath(user.Name, account.Type), account.Balance);
        
        EXIT( "FilesystemData::StoreAccount" );
    }
    
    void FilesystemData::closeAccountForUser( User user, AccountType type ) {
        ENTER( "FilesystemData::closeAccountForUser" );
        
        if( !DoesAccountExist(user, type) ) {
            Logger::Error() << "User account doesn't exist!" << endl;
            EXIT( "FilesystemData::closeAccountForUser" );
            throw std::exception();
        }
        
        deleteFile(getAccountPath( user.Name, type) );
        
        EXIT( "FilesystemData::closeAccountForUser" );
    };

    
    inline string FilesystemData::getAccountListPath() {
        return Configuration::DataDirectory + "/accounts.dat";
    }
    
    string FilesystemData::getAccountPath( string username, AccountType type ) {
        ENTER( "FilesystemData::getAccountPath" );
        
        string toReturn;
        switch ( type ) {
            case Accounts::Savings:
                toReturn = Configuration::DataDirectory + "/" + username + ".savings.dat";
                break;
            case Accounts::Checking:
                toReturn = Configuration::DataDirectory + "/" + username + ".checking.dat";
                break;
        }
        
        EXIT( "FilesystemData::getAccountPath" );
        return toReturn;
    }
    
    inline string FilesystemData::getUserPath( string userName ) {
        ENTER( "FilesystemData::getSavingsAccountPath" );
        
        string path = Configuration::DataDirectory + "/" + userName + ".dat";
        
        EXIT( "FilesystemData::getSavingsAccountPath" );
        return path;
    }
    
}