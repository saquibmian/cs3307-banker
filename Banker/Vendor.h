//
//  Vendor.h
//  Banker
//
//  Created by Brent Davis on 2014-11-22.
//  Copyright (c) 2014 CS3307 Final Project. All rights reserved.
//

#ifndef Banker_Vendor_h
#define Banker_Vendor_h



#include <vector>
#include <fstream>
#include <ctime>
#include <cstdio>
//#include <iostream>
//#include <stdio.h>
#include "FilesystemData.h"
//#include "MenuOption.h"
//#include "MainMenu.h"
#include "OptionContext.h"
#include "Logger.h"
#include "Session.h"
#include "User.h"
#include "FileIo.h"

using namespace std;

namespace Vendors{
    
    
    class Vendor{
        
    public:
        
        //Purchase purchase;
        
        Vendor ( string purchaseHistory, double balance );
        Vendor ( );
        
        static void purchaseSession(); // Could essentially be copied to a main.cpp file.
        bool checkPin(string inputPin, FilesystemData data, User user);
        bool isCardFrozen(FilesystemData data, User user);
        string updateCustomer(double purchasePrice);
        void updateVendor(double purchasePrice, string clientName);
        string getPurchaseHistory();
        static string loadPurchaseHistory();
    private:
        string purchaseHistory = "";
        double purchasePrice;
        double vendorFunds;
        // Something here to load in the customer information.
        
        
    };
    
    
}

#endif
