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
        string path = getUserPath( name );
        bool toReturn = fileExists( path );
        
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
        initFromFile( getUserPath( name ), serRole );
        
        User toReturn( name, User::roleFromString(serRole) );
        
        EXIT( "FilesystemData::GetUser" );
        return toReturn;
    }
    
    void FilesystemData::CreateUser( string name, UserRole role ) {
        ENTER( "FilesystemData::CreateUser" );
        
        if( DoesUserExist( name ) ) {
            Logger::Error() << "User already exists!" <<endl;
            throw std::exception();
        }
        string serRole = User::roleToString( role );
        createFile( getUserPath( name ), serRole );
        
        EXIT( "FilesystemData::CreateUser" );
    }
    
    bool FilesystemData::DoesAccountExist( User user, AccountType type ) {
        ENTER( "FilesystemData::DoesAccountExist" );
        
        bool toReturn = fileExists(getAccountPath(user.Name, type));
        
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
        initFromFile(getAccountPath(user.Name, type), account.Balance);
        
        return account;
    }
    
    void FilesystemData::StoreAccount( User user, Account account ) {
        ENTER( "FilesystemData::StoreAccount" );
        
        if( DoesAccountExist(user, account.Type) ) {
            Logger::Error() << "User account already exists!" << endl;
            throw std::exception();
        }
        
        createFile(getAccountPath(user.Name, account.Type), account.Balance);
        
        EXIT( "FilesystemData::StoreAccount" );
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
        
        Logger::Debug() << "Writing " << data << " to file " << path << endl;
        
        ofstream myfile;
        myfile.open( path.c_str(), ios::out );
        myfile << data;
        myfile.close();
        
        EXIT( "FilesystemData::createFile" );
    }
    
    template< class T> void FilesystemData::initFromFile( string path, T& data ) {
        ENTER( "FilesystemData::initFromFile" );

        ifstream myfile;
        myfile.open( path.c_str(), ios::in );
        myfile >> data;
        myfile.close();
        
        Logger::Debug() << "Read " << data << " from file " << path << endl;
        
        EXIT( "FilesystemData::initFromFile" );
    }
}