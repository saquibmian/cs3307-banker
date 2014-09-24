//
//  TraceDisplayOperation.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-24.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "TraceDisplayOperation.h"
#include "FileIo.h"

using namespace Io;

namespace Operations {
    void TraceDisplayOperation::execute( OptionContext context ) {
        ENTER( "TraceDisplayOperation::Execute" );
        
        string username;
        Logger::info() << "Please enter the username to obtain the trace file: ";
        cin >> username;
        
        if( !context.getData().doesUserExist( username ) ) {
            Logger::error() << "No such user: '" << username << "'." << endl;
        } else {
            string traceFile = Logger::getTraceFile( username );
            if( !fileExists( traceFile ) ) {
                Logger::info() << "This user has no trace data." << endl;
            } else {
                Logger::info() << "Printing trace for user " << username << " ..." << endl;
                
                vector<string> lines = readAllLinesFromFile( traceFile );
                for ( int i = 0; i < lines.size(); i++ ) {
                    Logger::info() << lines.at( i ) << endl;
                }
                
                Logger::info() << "Done printing trace ..." << endl;
            }
        }
        
        EXIT( "TraceDisplayOperation::Execute" );
    }
}
