//
//  FilesystemData.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__FilesystemData__
#define __Banker__FilesystemData__

#include <iostream>
#include "Data.h"

namespace Data {
    class FilesystemData : public IData {
        virtual bool DoesUserExist( string& name );
        virtual User& GetUser( string& name );
        virtual void CreateUser( const User& user );
        
        virtual bool DoesAccountExist( const User& user, AccountType type );
        virtual Account& GetAccount( const User& user, AccountType type );
        virtual void StoreAccount( const User& user, const Account& account );
    };
}

#endif /* defined(__Banker__FilesystemData__) */
