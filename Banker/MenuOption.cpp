//
//  MenuOption.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "MenuOption.h"
#include "Definitions.h"
#include "Logger.h"

namespace Menu {

    MenuOption::MenuOption( string display, IOperation* op, UserRole role )
        : _display( display ), _validRole( role ) {
            _operation = op;
        }
    
    string MenuOption::getDisplay() {
        return _display;
    }
    
    IOperation& MenuOption::getOperation() {
        return *_operation;
    }
    
    bool MenuOption::isValidForUser( Authentication::User user ) {
        ENTER( "MenuOption::IsValidForUser" );
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
        
        EXIT( "MenuOption::IsValidForUser" );
        return toReturn;
    }
    
}