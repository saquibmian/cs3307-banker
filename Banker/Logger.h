//
//  Logger.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_Logger_h
#define Banker_Logger_h

#define ENTER(x) (Logger::Enter( x ))
#define EXIT(x) (Logger::Exit( x ))

#include <iostream>
#include "Configuration.h"

using namespace std;

namespace Logger  {
    
    ostream& Debug();
    ostream& Info();
    ostream& Warn();
    ostream& Error();
    
    void Enter( string func );
    void Exit( string func );
    
}

#endif
