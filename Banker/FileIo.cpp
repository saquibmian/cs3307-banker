//
//  FileIo.cpp
//  Banker
//
//  Created by Saquib Mian on 2014-09-18.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include "FileIo.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

namespace Io {
    
    bool dirExists( string path ) {
        ENTER( "dirExists" );
        struct stat info;
        bool toReturn;
        
        if( stat( path.c_str(), &info ) != 0 )
            toReturn = false;
        else if( info.st_mode & S_IFDIR )
            toReturn = true;
        else
            toReturn = false;
        
        EXIT( "dirExists" );
        return toReturn;
    }
    
    bool fileExists( string path ) {
        ENTER( "fileExists" );
        struct stat info;
        bool toReturn;
        
        if( stat( path.c_str(), &info ) != 0 )
            toReturn = false;
        else if( info.st_mode & S_IFDIR )
            toReturn = false;
        else
            toReturn = true;
        
        EXIT( "fileExists" );
        return toReturn;
    }
    
    int deleteFile( string path ) {
        ENTER( "createFile" );
        
        int toReturn = remove( path.c_str() );
        
        EXIT( "createFile" );
        return toReturn;
    }
    
    vector<string> readAllLinesFromFile( string path ) {
        ENTER( "readAllLinesFromFile" );
        
        ifstream myfile;
        myfile.open( path.c_str(), ios::in );
        
        vector<string> lines;
        string line;
        while ( myfile.good() ) {
            getline ( myfile, line, '\n' );
            lines.push_back( line );
        }
        
        myfile.close();
        
        EXIT( "readAllLinesFromFile" );
        return lines;
    }
    
}
