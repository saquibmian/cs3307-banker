//
//  Initializer.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Initializer__
#define __Banker__Initializer__

#include <iostream>
#include "FilesystemData.h"
#include "MenuOption.h"
#include "MainMenu.h"
#include "OptionContext.h"
#include "Logger.h"

using namespace Menu;

class Program {
private:
    bool loggedIn = false;
    IData* data;
    User user;
    OptionContext* context;
    MainMenu* menu;
    vector<IOperation*>* mOperations;
    void login();
    void addMenuOptions();
    void createDefaultUsers();
public:
    Program();
    ~Program();
    void Intialize();
    inline User& getUser() { return user; }
    inline OptionContext& getContext() { return *context; }
    inline MainMenu& getMenu() { return *menu; }
};

#endif /* defined(__Banker__Initializer__) */
