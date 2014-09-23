//
//  TransferOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_TransferOperation_h
#define Banker_TransferOperation_h

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"
#include "DepositOperation.h"
#include "WithdrawOperation.h"

namespace Operations {
    class TransferOperation : public IOperation {
        void transfer( AccountType from, AccountType to, OptionContext& context );
        void transferExternal ( User destinationUser, AccountType from, AccountType to, OptionContext& context );
    public:
        void execute( OptionContext context ) ;
    };
}

#endif
