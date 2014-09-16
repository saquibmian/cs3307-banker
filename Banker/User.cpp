//
//  User.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "User.h"

namespace Authentication {
    
    User::User( string name, UserRole role ) : Name( name ), Role( role ) { }
    
    ostream& operator<<( ostream &strm, const User &user ) {
        return strm << user.Name;
    }
    
    
    
}
