//
//  WithdrawOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_WithdrawOperation_h
#define Banker_WithdrawOperation_h

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class WithdrawOperation : public IOperation {
    public:
        void Execute( OptionContext context ) ;
    };
}



#endif
