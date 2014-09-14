//
//  Definitions.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Definitions.h"

const char* TodoException::what() const throw() {
    return "This method is not implemented!";
}

TodoException todo;