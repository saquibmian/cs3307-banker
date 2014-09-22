//
//  MenuOption.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "MenuOption.h"
#include "Logger.h"

namespace Menu {

    MenuOption::MenuOption( string display, IOperation* op, UserRole role )
        : _display( display ), _validRole( role ) {
            _operation = op;
        }
    
    string MenuOption::getDisplay() {
        ENTER( "MenuOption::getDisplay" );
        EXIT( "MenuOption::getDisplay" );
        return _display;
    }
    
    IOperation& MenuOption::getOperation() {
        ENTER( "MenuOption::getDisplay" );
        EXIT( "MenuOption::getDisplay" );
        return *_operation;
    }
    
    bool MenuOption::isValidForUser( Authentication::User user ) {
        ENTER( "MenuOption::isValidForUser" );
        bool toReturn;
        
        if( _validRole == All ) {
            toReturn = true;
        } else if( user.Role == Manager ) {
            if( _validRole == Maintainer ) {
                toReturn = false;
            } else {
                toReturn = true;
            }
        } else {
            toReturn = user.Role == _validRole;
        }
        
        EXIT( "MenuOption::isValidForUser" );
        return toReturn;
    }
    
}
