//
//  Defintions.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_Defintions_h
#define Banker_Defintions_h

#define TOGGLE(x) ((x) = !(x))
#define TODO (throw todo)

#include <exception>

class TodoException: public std::exception {
    virtual const char* what() const throw();
};

extern TodoException todo;

#endif
