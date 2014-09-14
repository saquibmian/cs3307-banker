//
//  StringUtils.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-12.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef Banker_StringUtils_h
#define Banker_StringUtils_h

#include <vector>
#include <sstream>

using namespace std;

namespace StringUtils {
    vector<string>* tokenize( const string &s, char delim );
    string* concat( vector<string> const &strings, char delim );
}

#endif
