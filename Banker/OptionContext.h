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
        IData& _data;
        Session& _session;
    public:
        Session& getSession();
        IData& getData();
        OptionContext( IData& d, Session& session )
            : _data( d ), _session( session ) { }
    };
}

#endif /* defined(__Banker__OptionContext__) */
