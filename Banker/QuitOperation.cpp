//
//  QuitOperatin.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "QuitOperation.h"
#include "Logger.h"

namespace Operations {
    void QuitOperation::Execute( OptionContext context ) {
        ENTER( "QuitOperation::Execute" );
        
        context.GetSession().logout();
        
        EXIT( "QuitOperation::Execute" );
    }
}