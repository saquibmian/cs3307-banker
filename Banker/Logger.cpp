//
//  Logger.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-14.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "Logger.h"
#include <ctime>
#include "time.h"

#define MAX_TIME_LENGTH 80

namespace Logger {
    
    string getTimeAsString();
    int currentFunctionDepth = 0;
    
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
    
    ostream& Debug() {
        if (Configuration::IsDebug) {
            cout << "[" << getTimeAsString() << "] ";
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
    
    
    void Enter( string func ) {
        ++currentFunctionDepth;
        Logger::Debug() << "[depth " << currentFunctionDepth << "] Entering function: " << func << std::endl;
    }
    void Exit( string func ) {
        Logger::Debug() << "[depth " << currentFunctionDepth << "] Exiting function: " << func << std::endl;
        --currentFunctionDepth;
    }
    
    string getTimeAsString() {
        char buffer [MAX_TIME_LENGTH];
        
        time_t currentTime = time( 0 );
        strftime( buffer, MAX_TIME_LENGTH, "%c", localtime(&currentTime) );
        
        return string( buffer );
    }
}
