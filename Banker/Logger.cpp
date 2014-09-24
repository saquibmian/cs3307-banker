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

/*
 Note that this class is immune to the trace directly; any child-functions are not immune. 
 The reason is because we can get circular traces bu tracing trace functions.
 */
namespace Logger {
    
    bool _pauseTrace = false;
    int _currentFunctionDepth = 0;
    vector<string*> _traceLogs;
    
    string getTimeAsString( string formatString );
    string getTimeAndFunctionDepth();
    
    // null stream taken from:
    // http://forums.codeguru.com/showthread.php?460071-ostream-bit-bucket
    // This is an elegant way to create a stream that never writes its input. It is essentially a stream that does nothing, but responds in a way that makes it seem to the caller like all is well. It is well suited for cases where one may want to dynamically turn stream output ON or OFF, as is common in log level scenarios (e.g., turn debug logging ON, disable warnings, etc.).
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
    
    ostream& debug() {
        if ( Configuration::isDebug ) {
            cout << "DEBUG: ";
            return cout;
        }
        
        return cnul;
    }
    
    ostream& info() {
        return cout;
    }
    
    ostream& warn() {
        cout << "WARN: ";
        return cout;
    }
    
    ostream& error() {
        cerr << "ERROR: ";
        return cerr;
    }
    
    bool isTraceEnabled() {
        _pauseTrace = true;
        bool toReturn = Io::fileExists( Configuration::traceFile );
        _pauseTrace = false;
        return toReturn;
    }
    
    void toggleTrace() {
        if( isTraceEnabled() ) {
            if( Io::deleteFile( Configuration::traceFile ) != 0 ) {;
                error() << "Error deleting file: " << Configuration::traceFile << endl;
            }
            debug() << "Disabled trace" << endl;
        } else {
            Io::createFile( Configuration::traceFile, "" );
            debug() << "Enabled trace" << endl;
        }
    }
    
    string getTimeAndFunctionDepth() {
        stringstream buffer;
        buffer << "[" << getTimeAsString( "%X" ) << "] " << "[depth " << _currentFunctionDepth << "]";
        return buffer.str();
    }
    
    void enter( string func ) {
        if ( !_pauseTrace && isTraceEnabled() ) {
            ++_currentFunctionDepth;
            string* log = new string( getTimeAndFunctionDepth() + " Entering function: " + func  );
            _traceLogs.push_back( log );
            debug() << *log << endl;
        }
    }
    void exit( string func ) {
        if ( !_pauseTrace && isTraceEnabled() ) {
            string* log = new string( getTimeAndFunctionDepth() + " Exiting function: " + func  );
            _traceLogs.push_back( log );
            debug() << *log << endl;
            --_currentFunctionDepth;
        }
    }
    
    string getTimeAsString( string formatString ) {
        char buffer [MAX_TIME_LENGTH];
        
        time_t currentTime = time( 0 );
        strftime( buffer, MAX_TIME_LENGTH, formatString.c_str(), localtime(&currentTime) );
        
        return string( buffer );
    }
    
    void flushTrace( string username ) {
        if( !isTraceEnabled() ) {
            return;
        }
        
        string traceLogFile = getTraceFile( username );
        ofstream myfile;
        myfile.open( traceLogFile.c_str(), ios::out | ios::app );

        myfile << "Execution log for user '" << username << "' on " << getTimeAsString( "%c" ) << endl;
        for (int i = 0; i < _traceLogs.size(); i++) {
            string* log = _traceLogs.at( i );
            
            myfile << *log << endl;
            
            delete log;
        }

        myfile.close();
        _traceLogs.clear();
    }
    
    inline string getTraceFile( string username ) {
        return username + ".trace.dat";
    }

}
