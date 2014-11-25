//
//  ViewPaymentOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__ViewPaymentOperation__
#define __Banker__ViewPaymentOperation__

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"
#include <stdio.h>

namespace Operations {
    
    class ViewPaymentOperation : public IOperation {
        
    public:
        void execute (OptionContext context) ;
        
    };
    
}

#endif /* defined(__Banker__ViewPaymentOperation__) */
