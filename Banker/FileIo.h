//
//  FileIo.h
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#ifndef __Banker__FileIo__
#define __Banker__FileIo__

#include <iostream>
#include <vector>
#include <fstream>
#include "Logger.h"

using namespace std;

namespace Io {
    
    bool dirExists( string path );
    bool fileExists( string path );
    int deleteFile( string path );
    vector<string> readAllLinesFromFile( string path );

    // template functions have to be instantiated in the header file,
    // so that they are available during compilation
    
    template<class T> void createFile( string path, T& data )  {
        ENTER( "createFile" );
        
        ofstream myfile;
        myfile.open( path.c_str(), ios::out );
        myfile << data;
        myfile.close();
        
        EXIT( "createFile" );
    }
    
    template<class T> void appendLineToFile( string path, T& data ) {
        ENTER( "appendLineToFile" );
        
        ofstream myfile;
        myfile.open( path.c_str(), ios::out | ios::app );
        myfile << endl << data;
        myfile.close();
        
        EXIT( "appendLineToFile" );
    }

    template<class T> void initFromFile( string path, T& data ) {
        ENTER( "initFromFile" );
        
        ifstream myfile;
        myfile.open( path.c_str(), ios::in );
        myfile >> data;
        myfile.close();
        
        EXIT( "initFromFile" );
    }

}

#endif /* defined(__Banker__FileIo__) */
