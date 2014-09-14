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
#include "MenuOption.h"

using namespace std;

namespace Menu {
    class MenuWindow {
    private:
        vector<MenuOption> options;
        void Display( const User& user );
    public:
        MenuWindow();
        void AddMenuOption( MenuOption& option );
        const MenuOption& GetNextOption( const User& user );
    };
}

#endif /* defined(__Banker__Menu__) */
