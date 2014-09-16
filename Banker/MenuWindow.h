//
//  Menu.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Menu__
#define __Banker__Menu__

#include <iostream>
#include <vector>
#include <map>
#include "MenuOption.h"

using namespace std;

namespace Menu {
    class MenuWindow {
    private:
        int numOptions = 0;
        map<int,MenuOption>* options;
        void Display( User user );
    public:
        MenuWindow();
        ~MenuWindow();
        void AddMenuOption( MenuOption option );
        MenuOption GetNextOption( User user );
    };
}

#endif /* defined(__Banker__Menu__) */
