//
//  AccountDeletionOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-09-17.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_AccountDeletionOperation_h
#define Banker_AccountDeletionOperation_h

#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class AccountDeletionOperation : public IOperation {
    private:
        void deleteAccount( AccountType type, OptionContext& context  );
    public:
        void execute( OptionContext context ) ;
    };
}

#endif
