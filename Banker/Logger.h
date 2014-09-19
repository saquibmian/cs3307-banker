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
#include "User.h"

using namespace std;

namespace Logger  {
    
    bool isTraceEnabled();
    void toggleTrace();
    ostream& Debug();
    ostream& Info();
    ostream& Warn();
    ostream& Error();
    
    void enter( string func );
    void exit( string func );
    void flushTrace( Authentication::User& user );
    
}

#endif
