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
#include "FilesystemData.h"
#include "MenuOption.h"
#include "MainMenu.h"
#include "OptionContext.h"
#include "Logger.h"
#include "Session.h"



namespace Operations {
    class TransferOperation : public IOperation {
        void transfer( AccountType from, AccountType to, OptionContext& context );
        void transferExternal ( OptionContext destinationContext, AccountType from, AccountType to, OptionContext& context );
        IData* _transferData;
        OptionContext* _transferContext;
        Session* _transferSession;
    public:
        void execute( OptionContext context ) ;
    };
}

#endif
