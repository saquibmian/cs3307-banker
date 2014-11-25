//
//  main.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-11.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include <iostream>
#include "Logger.h"
#include "Program.h"
#include "Vendor.h"

using namespace Vendors;

int main( int argc, const char * argv[] ) {
    ENTER( "main" );
    
    Vendor vendor;
    
    cout << "Enter Vendor or Banking [vendor/banking]: ";
    string choice;
    cin >> choice;
    
    if (choice.compare("vendor")==0){
        Vendors::Vendor::purchaseSession();
    }
    else{
    
    Program init;
    init.intialize();
    init.run();
        
    }
    
    
    Logger::info() << "Goodbye!" << endl;

    EXIT( "main" );
    return 0;
}

