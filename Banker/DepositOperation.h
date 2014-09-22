//
//  DepositOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_DepositOperation_h
#define Banker_DepositOperation_h

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class DepositOperation : public IOperation {
    private:
        void depositIntoAccount( AccountType type, OptionContext& context );
    public:
        void Execute( OptionContext context ) ;
    };
}


#endif
