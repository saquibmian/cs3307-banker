//
//  AggregateBalanceOperation.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-16.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__AggregateBalanceOperation__
#define __Banker__AggregateBalanceOperation__

#include <iostream>
#include "IOperation.h"

namespace Operations {
    class AggregateBalanceOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__AggregateBalanceOperation__) */
