//
//  Menu.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "MainMenu.h"
#include "Logger.h"

namespace Menu {
    
    MainMenu::MainMenu() {
        _options = new map<int,MenuOption>;
        _numOptions = 0;
    }
    
    MainMenu::~MainMenu() {
        delete _options;
    }
    
    void MainMenu::display( User user ) {
        ENTER( "MenuWindow::display" );
        
        for ( map<int,MenuOption>::iterator iter = _options->begin(
             ); iter != _options->end(); iter++ ) {
            MenuOption op = iter->second;
            if( op.isValidForUser( user ) ) {
                cout << "[" << iter->first << "] " << op.getDisplay() <<endl;
            }
        }
        
        EXIT( "MenuWindow::display" );
    }
    
    void MainMenu::addMenuOption( MenuOption option ) {
        ENTER( "MenuWindow::addMenuOption" );
        
        _options->insert( std::map< int, MenuOption >::value_type ( _numOptions++, option ) );
        MenuOption op = _options->at( _numOptions - 1 );
        
        EXIT( "MenuWindow::addMenuOption" );
    }
    
    MenuOption MainMenu::getNextOption( User user ) {
        ENTER( "MenuWindow::getNextOption" );
        display( user );
        
        int option;
        cout << "Please choose an option: ";
        // TODO: entering a string here causes a stack overflow; is there a way to empty cin?
        cin >> option;
        
        if( _options->count(option) == 0 ) {
            Logger::error() << "Invalid option!" << endl;
            throw std::exception();
        }
        
        EXIT( "MenuWindow::getNextOption" );
        return _options->at( option );
    }

}
