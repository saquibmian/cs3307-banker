//
//  AccountBalanceOperation.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-15.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__AccountBalanceOperation__
#define __Banker__AccountBalanceOperation__

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class AccountBalanceOperation : public IOperation {
    public:
        void Execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__AccountBalanceOperation__) */
