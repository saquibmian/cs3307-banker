//
//  MenuOption.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__MenuOption__
#define __Banker__MenuOption__

#include <iostream>
#include "IOperation.h"

using namespace std;
using namespace Operations;

namespace Menu {
    
    class MenuOption {
    private:
        string display;
        IOperation* operation;
        UserRole validRole;
    public:
        MenuOption( string display, IOperation* op, UserRole role );
        string GetDisplay();
        IOperation& GetOperation();
        bool IsValidForUser( User user );
        bool IsQuit();
    };
    
}


#endif /* defined(__Banker__MenuOption__) */
