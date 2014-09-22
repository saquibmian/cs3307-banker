//
//  TraceOperation.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__TraceOperation__
#define __Banker__TraceOperation__

#include <iostream>
#include "IOperation.h"
#include "Configuration.h"
#include "Logger.h"

namespace Operations {
    class TraceOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__TraceOperation__) */
