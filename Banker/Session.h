//
//  Session.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Session__
#define __Banker__Session__

#include <iostream>
#include "User.h"
#include "Data.h"

using namespace Data;

namespace Authentication {
    
    class Session {
    private:
        bool loggedIn;
        IData& data;
        User user;
    public:
        Session( IData& d ) : data( d ), user( "none" ) {
            loggedIn = false;
        }
        bool isActive();
        void login();
        void logout();
        User& getUser() { return user; };
    };
    
}

#endif /* defined(__Banker__Session__) */
