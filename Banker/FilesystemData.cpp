//
//  FilesystemData.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "FilesystemData.h"
#include "Definitions.h"

namespace Data {
    
    bool FilesystemData::DoesUserExist( string& name ) {
        TODO;
    }
    
    User& FilesystemData::GetUser( string& name ) {
    User& FilesystemData::CreateUser( string& name ) {
        TODO;
    }
    
        TODO;
    }
    
    bool FilesystemData::DoesAccountExist( const Authentication::User &user, Accounts::AccountType type ) {
        TODO;
    }
    
    Account& FilesystemData::GetAccount( const Authentication::User &user, Accounts::AccountType type ) {
        TODO;
    }
    
    void FilesystemData::StoreAccount( const Authentication::User &user, const Accounts::Account &account ) {
        TODO;
    }
}