//
//  Account.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__Account__
#define __Banker__Account__

#include <iostream>

namespace Accounts {
    
    enum AccountType {
        Savings, Checking
    };
    class Account {
    public:
        AccountType GetType();
        double GetBalance();
    };
}

#endif /* defined(__Banker__Account__) */
