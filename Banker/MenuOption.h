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
        const string& display;
        int key;
        const IOperation& operation;
    public:
        MenuOption( int key, const string& display, const IOperation& op );
        const string& GetDisplay();
        const IOperation& GetOperation();
        bool IsQuit();
        bool IsLogout();
    };
    
}


#endif /* defined(__Banker__MenuOption__) */
