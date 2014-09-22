//
//  Logger.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_Logger_h
#define Banker_Logger_h

#define ENTER(x) (Logger::enter( x ))
#define EXIT(x) (Logger::exit( x ))

#include <iostream>
#include "Configuration.h"

using namespace std;

namespace Logger  {
    
    bool isTraceEnabled();
    void toggleTrace();
    ostream& debug();
    ostream& info();
    ostream& warn();
    ostream& error();
    
    void enter( string func );
    void exit( string func );
    void flushTrace( string username );
    
}

#endif
