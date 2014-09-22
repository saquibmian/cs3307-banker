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
    class MainMenu {
    private:
        int _numOptions;
        map<int,MenuOption>* _options;
        void display( User user );
    public:
        MainMenu();
        ~MainMenu();
        void addMenuOption( MenuOption option );
        MenuOption getNextOption( User user );
    };
}

#endif /* defined(__Banker__Menu__) */
