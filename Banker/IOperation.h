//
//  IOperation.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_IOperation_h
#define Banker_IOperation_h

#include "OptionContext.h"

using namespace Options;

namespace Operations {
    
    class IOperation {
    public:
        virtual ~IOperation() {}
        virtual void Execute( OptionContext const &context ) = 0;
    };
    
}

#endif
