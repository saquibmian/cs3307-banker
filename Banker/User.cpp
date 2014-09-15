//
//  User.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "User.h"

namespace Authentication {
    
    User::User( string name ) : name( name ) { }
    
    const string User::GetName() const {
        return name;
    };

    UserRole User::GetRole() const {
        return role;
    }
    
    ostream& operator<<( ostream &strm, const User &user ) {
        return strm << user.GetName();
    }
    
}
