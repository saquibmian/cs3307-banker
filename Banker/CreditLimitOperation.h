//
//  CreditLimitOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__CreditLimitOperation__
#define __Banker__CreditLimitOperation__

#include <stdio.h>
#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class CreditLimitOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}



#endif /* defined(__Banker__CreditLimitOperation__) */
