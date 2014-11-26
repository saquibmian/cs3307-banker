//
//  VendorHistoryOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "VendorHistoryOperation.h"
#include "Logger.h"
#include "FileIo.h"
#include <vector>
#include <cctype>

namespace Operations {
    
    void VendorHistoryOperation::execute(OptionContext context){
        ENTER("VendorHistoryOperation::execute");
        
        //IData& data = context.getData();
        
        ENTER("Vendor::loadPurchaseHistory");
        
        string readIn;
        vector<string> purchaseHistory = Io::readAllLinesFromFile("vendorandbank.history.dat");
        
        for ( int i = 0; i <= purchaseHistory.size()-1; i++){
            
            cout << purchaseHistory[i] << endl;
            
        }
        
        
        
        //cout << purchaseHistory;
        
        EXIT("VendorHistoryOperation::execute");
    }
    
}