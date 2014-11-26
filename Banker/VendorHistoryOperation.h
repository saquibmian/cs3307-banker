//
//  VendorHistoryOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__VendorHistoryOperation__
#define __Banker__VendorHistoryOperation__

#include <stdio.h>
#include "IOperation.h"
#include "Logger.h"
#include "FileIo.h"
#include <vector>
#include <cctype>

namespace Operations {
    
    class VendorHistoryOperation : public IOperation {
    public:
        void execute (OptionContext context);
    };
    
}

#endif /* defined(__Banker__VendorHistoryOperation__) */
