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
#include "Session.h"

using namespace Authentication;
using namespace Data;

namespace Options {
    class OptionContext {
    private:
        IData& data;
        Session& session;
    public:
        Session& GetSession();
        IData& GetData();
        OptionContext( IData& d, Session& session )
            : data( d ), session( session ) { }
    };
}

#endif /* defined(__Banker__OptionContext__) */
