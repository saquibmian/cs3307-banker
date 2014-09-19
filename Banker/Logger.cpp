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
#include <fstream>
#include <sstream>
#include <cstdio>
#include "FileIo.h"

#define MAX_TIME_LENGTH 80

namespace Logger {
    
    bool pauseTrace = false;
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
        if ( Configuration::IsDebug ) {
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
    
    bool isTraceEnabled() {
        pauseTrace = true;
        bool toReturn = Io::fileExists( Configuration::TraceFile );
        pauseTrace = false;
        return toReturn;
    }
    
    void toggleTrace() {
        if( isTraceEnabled() ) {
            if( Io::deleteFile( Configuration::TraceFile ) != 0 ) {;
                Error() << "Error deleting file: " << Configuration::TraceFile << endl;
            }
            Debug() << "Disabled trace" << endl;
        } else {
            Io::createFile( Configuration::TraceFile, "" );
            Debug() << "Enabled trace" << endl;
        }
    }
    
    string getTimeAndFunctionDepth() {
        stringstream buffer;
        buffer << "[" << getTimeAsString() << "] " << "[depth " << currentFunctionDepth << "]";
        return buffer.str();
    }
    
    void Enter( string func ) {
        if ( !pauseTrace && isTraceEnabled() ) {
            ++currentFunctionDepth;
            cout << getTimeAndFunctionDepth() << " Entering function: " << func << std::endl;
        }
    }
    void Exit( string func ) {
        if ( !pauseTrace && isTraceEnabled() ) {
            cout << getTimeAndFunctionDepth() << " Exiting function: " << func << std::endl;
            --currentFunctionDepth;
        }
    }
    
    string getTimeAsString() {
        char buffer [MAX_TIME_LENGTH];
        
        time_t currentTime = time( 0 );
        strftime( buffer, MAX_TIME_LENGTH, "%c", localtime(&currentTime) );
        
        return string( buffer );
    }

}
