//
// AccountCreationOperation.cpp
// Banker
//
// Created by Brent Davis on 2014-09-16.
// Copyright (c) 2014 Saquib Mian. All rights reserved.
//


#ifndef Banker_AccountCreationOperation_h
#define Banker_AccountCreationOperation_h
#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"

namespace Operations {
    class AccountCreationOperation : public IOperation {
    private:
        void createAccount( AccountType type, OptionContext& context );
    public:
        void execute( OptionContext context ) ;
    };
}
#endif

