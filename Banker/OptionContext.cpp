//
//  OptionContext.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "OptionContext.h"
#include "Logger.h"

namespace Options {
    Session& OptionContext::getSession() {
        ENTER( "OptionContext::getSession" );
        EXIT( "OptionContext::getSession" );
        return _session;
    }
    IData& OptionContext::getData() {
        ENTER( "OptionContext::getSession" );
        EXIT( "OptionContext::getSession" );
        return _data;
    }
}
