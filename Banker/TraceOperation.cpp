//
//  TraceOperation.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "TraceOperation.h"

namespace Operations {
    void TraceOperation::Execute( OptionContext context ) {
        ENTER( "TraceOperation::Execute" );
        
        Logger::toggleTrace();
        
        Logger::Info() << "Trace is now: " << ( Logger::isTraceEnabled() ? "ON" : "OFF") << endl;
        
        EXIT( "TraceOperation::Execute" );
    }
}