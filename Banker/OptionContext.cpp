//
//  OptionContext.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "OptionContext.h"

namespace Options {
    User OptionContext::GetUser() {
        return user;
    }
    IData& OptionContext::GetData() {
        return data;
    }
}