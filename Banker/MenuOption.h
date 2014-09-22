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
        string _display;
        IOperation* _operation;
        UserRole _validRole;
    public:
        MenuOption( string display, IOperation* op, UserRole role );
        string getDisplay();
        IOperation& getOperation();
        bool isValidForUser( User user );
    };
    
}


#endif /* defined(__Banker__MenuOption__) */
