//
//  TraceDisplayOperation.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-24.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__TraceDisplayOperation__
#define __Banker__TraceDisplayOperation__

#include <stdio.h>
#include "IOperation.h"

namespace Operations {
    class TraceDisplayOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__TraceDisplayOperation__) */
