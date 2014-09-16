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
        : display( display ), validRole( role ) {
            operation = op;
        }
    
    string MenuOption::GetDisplay() {
        return display;
    }
    
    IOperation& MenuOption::GetOperation() {
        return *operation;
    }
    
    bool MenuOption::IsValidForUser( Authentication::User user ) {
        ENTER( "MenuOption::IsValidForUser" );
        bool toReturn = user.GetRole() == validRole;
        
        EXIT( "MenuOption::IsValidForUser" );
        return toReturn;
    }
    
    bool MenuOption::IsQuit() {
        TODO;
    }
    
}