//
//  Logger.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Logger.h"

namespace Logger {
    
    // null stream taken from:
    // http://forums.codeguru.com/showthread.php?460071-ostream-bit-bucket
    class NullBuffer : public streambuf {
    public:
        virtual streamsize xsputn(const char * s, streamsize n) {
            return n;
        }
        virtual int overflow(int c) {
            return 1;
        }
    };
    class NullStream : public ostream {
    private:
        NullBuffer buffer;
    public:
        NullStream() : ostream(&buffer) {}
    };
    
    NullStream cnul;
    
    // method implementations
    ostream& Debug() {
        if (Configuration::IsDebug) {
            cout << "DEBUG: ";
            return cout;
        }
        
        return cnul;
    }
    
    ostream& Info() {
        return cout;
    }
    
    ostream& Warn() {
        cout << "WARN: ";
        return cout;
    }
    
    ostream& Error() {
        cerr << "ERROR: ";
        return cerr;
    }
}
