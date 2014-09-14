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

using namespace Authentication;

namespace Options {
    class OptionContext {
    private:
        const User & user;
    public:
        const User& GetUser();
        OptionContext( User &usr ) : user( usr ) { }
    };
}

#endif /* defined(__Banker__OptionContext__) */
