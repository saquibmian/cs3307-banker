//
//  Logger.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_Logger_h
#define Banker_Logger_h

#define ENTER(x) (Logger::Debug() << "Entering function: " << x << std::endl)
#define EXIT(x) (Logger::Debug() << "Exiting function: " << x << std::endl)

#include <iostream>
#include "Configuration.h"

using namespace std;

namespace Logger  {
    
    ostream& Debug();
    ostream& Info();
    ostream& Warn();
    ostream& Error();
    
}

#endif
