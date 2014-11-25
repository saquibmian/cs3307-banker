//
//  ViewTransactionsOperation.h
//  Banker
//
//  Created by Brent Davis on 2014-11-24.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#ifndef __Banker__ViewTransactionsOperation__
#define __Banker__ViewTransactionsOperation__

#include <stdio.h>
#include <iostream>
#include "IOperation.h"
#include "FilesystemData.h"


namespace Operations {
    class ViewTransactionsOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__ViewTransactionsOperation__) */
