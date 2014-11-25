//
//  MonthlyUpdateOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__MonthlyUpdateOperation__
#define __Banker__MonthlyUpdateOperation__

#include <stdio.h>
#include "Account.h"
#include "Logger.h"
#include "IOperation.h"

namespace Operations {
    class MonthlyUpdateOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}


#endif /* defined(__Banker__MonthlyUpdateOperation__) */
