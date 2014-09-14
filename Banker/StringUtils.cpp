//
//  StringUtils.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-12.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "StringUtils.h"

using namespace std;

namespace StringUtils {
    void tokenize( const string &s, char delim, vector<string> &elems ) {
        stringstream ss( s );
        
        string item;
        while( getline( ss, item, delim ) ) {
            if( !item.empty() ) {
                elems.push_back( item );
            }
        }
    }
    
    vector<string>* tokenize(const string &s, char delim) {
        vector<string>* elems = new vector<string>;
        
        tokenize( s, delim, *elems );
        
        return elems;
    }
    
    string* concat( vector<string> const &strings, char delim ) {
        string* toReturn = new string;
        
        for( vector<string>::const_iterator iter = strings.begin(); iter != strings.end(); iter++ ) {
            (*toReturn) += *iter.base();
            (*toReturn) += delim;
        }
        
        return toReturn;
    }
}
