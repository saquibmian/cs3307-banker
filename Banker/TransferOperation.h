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
    private:
        void transfer( User& fromUser, User& toUser, AccountType fromAccount, AccountType toAccount, IData& data );
    public:
        void execute( OptionContext context ) ;
    };
}

#endif
