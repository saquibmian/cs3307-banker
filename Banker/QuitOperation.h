//
//  QuitOperatin.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__QuitOperatin__
#define __Banker__QuitOperatin__

#include <iostream>
#include "IOperation.h"

namespace Operations {
    class QuitOperation : public IOperation {
    public:
        void execute( OptionContext context ) ;
    };
}

#endif /* defined(__Banker__QuitOperatin__) */
