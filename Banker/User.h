//
//  User.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_User_h
#define Banker_User_h

#import <iostream>

using namespace std;

namespace Authentication {
    
    enum UserRole {
        Client, Manager, Maintainer
    };
    
    class User {
    private:
        string& name;
        UserRole role;
        
    public:
        User( string& name );
        const string& GetName() const;
        UserRole GetRole() const;
        friend ostream& operator<<( ostream& os, const User& user );
    };
    
}

#endif
