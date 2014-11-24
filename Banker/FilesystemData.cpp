//
//  FilesystemData.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "FilesystemData.h"
#include "Logger.h"
#include "FileIo.h"
#include <cstdio>
#include <stdio.h>

using namespace Io;

namespace Data {
    
    void FilesystemData::initialize() {
        ENTER( "FilesystemData::initialize" );
        if( !Io::fileExists( getAccountListPath() ) ) {
            Io::createFile(getAccountListPath(), "" );
        }
        EXIT( "FilesystemData::initialize" );
    }
    
    bool FilesystemData::doesUserExist( string name ) {
        ENTER( "FilesystemData::doesUserExist" );
        string path = getUserPath( name );
        bool toReturn = Io::fileExists( path );
        
        EXIT( "FilesystemData::doesUserExist" );
        return toReturn;
    }
    
    User FilesystemData::getUser( string name ) {
        ENTER( "FilesystemData::getUser" );
        
        if( !doesUserExist(name) ) {
            Logger::error() << "No such user";
            throw std::exception();
        }
        
        string serRole;
        Io::initFromFile( getUserPath( name ), serRole );
        
        User toReturn( name, User::roleFromString(serRole) );
        
        EXIT( "FilesystemData::getUser" );
        return toReturn;
    }
    
    vector<User> FilesystemData::getAllUsers() {
        ENTER( "FilesystemData::getAllUsers" );
        vector<User> toReturn;
        
        vector<string> users = Io::readAllLinesFromFile( getAccountListPath() );
        for ( vector<string>::iterator iter = users.begin(); iter != users.end(); iter++ ) {
            if( !iter.base()->empty() ) {
                toReturn.push_back( getUser( *iter.base() ) );
            }
        }
        
        EXIT( "FilesystemData::getAllUsers" );
        return toReturn;
    }
    
    void FilesystemData::createUser( string name, UserRole role ) {
        ENTER( "FilesystemData::createUser" );
        
        if( doesUserExist( name ) ) {
            Logger::error() << "User already exists!" <<endl;
            throw std::exception();
        }
        string serRole = User::roleToString( role );
        Io::createFile( getUserPath( name ), serRole );
        Io::appendLineToFile(getAccountListPath(), name);
        
        EXIT( "FilesystemData::createUser" );
    }
        
    bool FilesystemData::doesAccountExist( User user, AccountType type ) {
        ENTER( "FilesystemData::doesAccountExist" );
        
        bool toReturn = Io::fileExists(getAccountPath(user.Name, type));
        
        EXIT( "FilesystemData::doesAccountExist" );
        return toReturn;
    }
    
    Account FilesystemData::getAccount( User user, AccountType type ) {
        ENTER( "FilesystemData::getAccount" );
        
        if( !doesAccountExist(user, type) ) {
            Logger::error() << "User account doesn't exist!" << endl;
            throw std::exception();
        }
        
        Account account(type, 0);
        initFromFile(getAccountPath(user.Name, type), account.Balance);
        
        EXIT( "FilesystemData::getAccount" );
        return account;
    }
    
    void FilesystemData::storeAccount( User user, Account account ) {
        ENTER( "FilesystemData::storeAccount" );
        
        Io::createFile(getAccountPath(user.Name, account.Type), account.Balance);
        
        EXIT( "FilesystemData::storeAccount" );
    }
    
    void FilesystemData::closeAccountForUser( User user, AccountType type ) {
        ENTER( "FilesystemData::closeAccountForUser" );
        
        if( !doesAccountExist(user, type) ) {
            Logger::error() << "User account doesn't exist!" << endl;
            EXIT( "FilesystemData::closeAccountForUser" );
            throw std::exception();
        }
        
        deleteFile(getAccountPath( user.Name, type) );
        
        EXIT( "FilesystemData::closeAccountForUser" );
    };

    
    inline string FilesystemData::getAccountListPath() {
        return Configuration::dataDirectory + "/accounts.dat";
    }
    
    string FilesystemData::getAccountPath( string username, AccountType type ) {
        ENTER( "FilesystemData::getAccountPath" );
        
        string toReturn;
        switch ( type ) {
            case Accounts::Savings:
                toReturn = Configuration::dataDirectory + "/" + username + ".savings.dat";
                break;
            case Accounts::Checking:
                toReturn = Configuration::dataDirectory + "/" + username + ".checking.dat";
                break;
            case Accounts::CreditCard:
                toReturn = Configuration::dataDirectory + "/" + username + ".creditcard.dat";
        }
        
        EXIT( "FilesystemData::getAccountPath" );
        return toReturn;
    }
    
    inline string FilesystemData::getUserPath( string userName ) {
        ENTER( "FilesystemData::getSavingsAccountPath" );
        
        string path = Configuration::dataDirectory + "/" + userName + ".dat";
        
        EXIT( "FilesystemData::getSavingsAccountPath" );
        return path;
    }
    
    void FilesystemData::storeTransaction(string username, AccountType type, string transaction ){
        ENTER ("FilesystemData::storeTransaction" );
        
        string path;
        switch ( type ){
            case Accounts::CreditCard:
                //cout << "Entered CreditCard";
                path = Configuration::dataDirectory + "/" + username + ".creditcard.transactions.dat";
                break;
            case Accounts::Savings:
                path = Configuration::dataDirectory + "/" + username + ".savings.transactions.dat";
                break;
            case Accounts::Checking:
                //cout << "Entered Checking";
                path = Configuration::dataDirectory + "/" + username + ".checking.transactions.dat";
                break;
        }
        
        Io::appendLineToFile(path, transaction );
        
    }
    
}
