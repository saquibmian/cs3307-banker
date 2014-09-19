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
    
    bool pauseTrace = false;
    string getTimeAsString( string formatString );
    string getTimeAndFunctionDepth();
    int currentFunctionDepth = 0;
    vector<string*> traceLogs;
    
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
        buffer << "[" << getTimeAsString( "%X" ) << "] " << "[depth " << currentFunctionDepth << "]";
        return buffer.str();
    }
    
    void enter( string func ) {
        if ( !pauseTrace && isTraceEnabled() ) {
            ++currentFunctionDepth;
            string* log = new string( getTimeAndFunctionDepth() + " Entering function: " + func  );
            traceLogs.push_back( log );
        }
    }
    void exit( string func ) {
        if ( !pauseTrace && isTraceEnabled() ) {
            string* log = new string( getTimeAndFunctionDepth() + " Exiting function: " + func  );
            traceLogs.push_back( log );
            --currentFunctionDepth;
        }
    }
    
    string getTimeAsString( string formatString ) {
        char buffer [MAX_TIME_LENGTH];
        
        time_t currentTime = time( 0 );
        strftime( buffer, MAX_TIME_LENGTH, formatString.c_str(), localtime(&currentTime) );
        
        return string( buffer );
    }
    
    void flushTrace( Authentication::User& user ) {
        if( !isTraceEnabled() ) {
            return;
        }
        
        string traceLogFile = user.Name + ".trace.dat";
        ofstream myfile;
        myfile.open( traceLogFile.c_str(), ios::out | ios::app );

        myfile << "Execution log for user '" << user.Name << "' on " << getTimeAsString( "%c" ) << endl;
        for (int i = 0; i < traceLogs.size(); i++) {
            string* log = traceLogs.at( i );
            
            myfile << *log << endl;
            
            delete log;
        }

        myfile.close();
        traceLogs.clear();
    }

}
