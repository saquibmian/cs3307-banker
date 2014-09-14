//
//  MenuOption.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "MenuOption.h"
#include "Definitions.h"

namespace Menu {

    MenuOption::MenuOption( int key, const string& display, const IOperation& op )
        : operation ( op ), key( key ), display( display ) { }
    
    const string& MenuOption::GetDisplay() {
        return display;
    }
    
    const IOperation& MenuOption::GetOperation() {
        return operation;
    }
    
    bool MenuOption::IsQuit() {
        TODO;
    }
    
    bool MenuOption::IsLogout() {
        TODO;
    }
    
}