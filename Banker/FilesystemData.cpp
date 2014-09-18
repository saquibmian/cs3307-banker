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
#include <cstdio>
#include <stdio.h>

namespace Data {
    
    void FilesystemData::initialize() {
        if( !fileExists( getAccountListPath() ) ) {
            createFile(getAccountListPath(), "" );
        }
    }
    
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
    
    vector<User> FilesystemData::getAllUsers() {
        vector<User> toReturn;
        
        vector<string> users = readAllLinesFromFile( getAccountListPath() );
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
        createFile( getUserPath( name ), serRole );
        appendLineToFile(getAccountListPath(), name);
        
        EXIT( "FilesystemData::CreateUser" );
    }
    
    
    //Method to create an account for a pre-existing user.
    void FilesystemData::CreateSavingsAccount (User user, double startBalance){
        ENTER ("FilesystemData::CreateSavingsAccount");
        
        if ( DoesAccountExist( user.Name, Savings)){
            Logger::Error() << "Savings Account already exists!" <<endl;
            throw std::exception();
        }
        else{
        createFile( getAccountPath(user.Name, Savings), startBalance );
        }
        // Creates an account with the starting balance specified in the form of a username.checking.dat file
        EXIT("FilesystemData::CreateSavingsAccount");
    }
    
    
    void FilesystemData::CreateCheckingAccount (User user, double startBalance){
        ENTER("FilesystemData::CreateCheckingAccount");
        if ( DoesAccountExist( user.Name, Checking)){
            Logger::Error() << "Checking Account already exists!" <<endl;
            throw std::exception();
        }
        else{
            createFile(getAccountPath(user.Name, Checking), startBalance );
        }
    }
    
    void FilesystemData::CloseCheckingAccount (User user){
        ENTER("FilesystemData::CloseCheckingAccount");
        if ( !DoesAccountExist( user.Name, Checking)){
            Logger::Error() << "This account does not exist!" << endl;
            throw std::exception();
        }
        else{
            deleteFile(getAccountPath(user.Name,Checking));
        }
    }
    
    void FilesystemData::CloseSavingsAccount (User user){
        ENTER("FilesystemData::CloseSavingsAccount");
        if ( !DoesAccountExist( user.Name, Savings)){
            Logger::Error() << "This account does not exist!" << endl;
            throw std::exception();
        }
        else{
            deleteFile(getAccountPath(user.Name,Savings));
        }
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
        
        Account account(type, 0);
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
    
    void FilesystemData::UpdateAccount( User user, Account account ) {
        ENTER( "FilesysemData::UpdateAccount");
        createFile(getAccountPath(user.Name, account.Type),account.Balance);
    }
    
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
    
    void FilesystemData::deleteFile (string path){
        ENTER( "FilesystemData::deleteFile" );
        
        Logger::Debug() << "Deleting file at " << path << endl;
        
        int track = remove( path.c_str() );
        
        if (track == 0){
            cout << "File removed successfully" << endl;
        }
        else{
            cout << "An error occured deleting file at " << path << endl;
        }
        
    }
    
    template< class T> void FilesystemData::appendLineToFile( string path, T& data ) {
        ENTER( "FilesystemData::appendLineToFile" );
        
        Logger::Debug() << "Appending " << data << " to file " << path << endl;
        
        ofstream myfile;
        myfile.open( path.c_str(), ios::out | ios::app );
        myfile << endl << data;
        myfile.close();
        
        EXIT( "FilesystemData::appendLineToFile" );
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
    
    vector<string> FilesystemData::readAllLinesFromFile( string path ) {
        ENTER( "FilesystemData::readAllLinesFromFile" );

        ifstream myfile;
        myfile.open( path.c_str(), ios::in );
        
        vector<string> lines;
        string line;
        while ( myfile.good() ) {
            getline ( myfile, line, '\n' );
            lines.push_back( line );
        }
        
        myfile.close();
        
        EXIT( "FilesystemData::readAllLinesFromFile" );
        return lines;
    }
}