//
//  main.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include <iostream>
#include "Definitions.h"
#include "User.h"
#include "Configuration.h"
#include "Logger.h"
#include "FilesystemData.h"
#include "MainMenu.h"
#include "AccountBalanceOperation.h"
#include "Initializer.h"

using namespace std;
using namespace Authentication;
using namespace Data;
using namespace Menu;
using namespace Initialize;

int main( int argc, const char * argv[] ) {
    ENTER( "main" );
        
    Initializer init;
    
    init.Intialize();
    
    while (true) {
        try {
            MenuOption option = init.getMenu().GetNextOption( init.getUser() );
            option.GetOperation().Execute( init.getContext() );
        } catch ( std::exception e ) {
            Logger::Error() << "An error occured: " << e.what() << endl;;
        }
    }

    cout << "Goodbye!" << endl;
    EXIT( "main" );
    return 0;
}

