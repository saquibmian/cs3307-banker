//
//  Menu.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "MenuWindow.h"
#include "Definitions.h"
#include "Logger.h"

namespace Menu {
    
    MenuWindow::MenuWindow() {
        options = new map<int,MenuOption>;
    }
    
    MenuWindow::~MenuWindow() {
        delete options;
    }
    
    void MenuWindow::Display( User user ) {
        ENTER( "MenuWindow::Display" );
        
        for ( map<int,MenuOption>::iterator iter = options->begin(); iter != options->end(); iter++ ) {
            MenuOption op = iter->second;
            if( op.IsValidForUser( user ) ) {
                cout << "[" << iter->first << "] " << op.GetDisplay() <<endl;
            }
        }
        
        EXIT( "MenuWindow::Display" );
    }
    
    void MenuWindow::AddMenuOption( MenuOption option ) {
        ENTER( "MenuWindow::AddMenuOption" );
        
        options->insert( std::map< int, MenuOption >::value_type ( numOptions++, option ) );
        MenuOption op = options->at(numOptions -1);
        
        EXIT( "MenuWindow::AddMenuOption" );
    }
    
    MenuOption MenuWindow::GetNextOption( User user ) {
        ENTER( "MenuWindow::GetNextOption" );
        Display( user );
        
        int option;
        cout << "Please choose an option: ";
        cin >> option;
        
        cout << "numOptions is " << options->count(option) << endl;
        if( options->count(option) == 0 ) {
            Logger::Error() << "Invalid option!" << endl;
        }
        
        EXIT( "MenuWindow::GetNextOption" );
        return options->at( option );
    }

}