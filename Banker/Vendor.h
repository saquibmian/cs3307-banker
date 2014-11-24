//
//  Vendor.h
//  Banker
//
//  Created by Brent Davis on 2014-11-22.
//  Copyright (c) 2014 CS3307 Final Project. All rights reserved.
//

#ifndef Banker_Vendor_h
#define Banker_Vendor_h


#include "Logger.h"
#include <iostream>
#include "User.h"
#include "Account.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <stdio.h>
#include "FilesystemData.h"
#include "MenuOption.h"
#include "MainMenu.h"
#include "OptionContext.h"
#include "Logger.h"
#include "Session.h"
#include "User.h"
#include "FileIo.h"

namespace Vendors{
    
    
    class Vendor{
        
    public:
        
        //Purchase purchase;
        
        Vendor ( string purchaseHistory, double balance );
        Vendor ( );
        
        static void purchaseSession(); // Could essentially be copied to a main.cpp file.
        bool checkPin(int inputPin);
        bool isCardFrozen();
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
