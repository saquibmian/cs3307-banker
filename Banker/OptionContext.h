//
//  OptionContext.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__OptionContext__
#define __Banker__OptionContext__

#include <iostream>
#include "User.h"
#include "Data.h"

using namespace Authentication;
using namespace Data;

namespace Options {
    class OptionContext {
    private:
        User user;
        IData& data;
    public:
        User GetUser();
        IData& GetData();
        OptionContext( User usr, IData& d ) : user( usr ), data( d ) { }
    };
}

#endif /* defined(__Banker__OptionContext__) */
