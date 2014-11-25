//
//  Vendor.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-22.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include <stdio.h>
#include "Vendor.h"
#include <iostream>
#include "Logger.h"
#include <sstream>


using namespace std;

namespace Vendors{
    
    Vendor::Vendor ( string inputPurchaseHistory, double balance ){
        
        purchaseHistory = inputPurchaseHistory;
        vendorFunds = balance;
        
    }
    
    Vendor::Vendor(){
        purchaseHistory = "";
        vendorFunds = 0;
    }
    
    string Vendor::getPurchaseHistory(){
        ENTER("Vendor::getPurchaseHistory");
        
        return purchaseHistory;
        
        EXIT("Vendor::getPurchaseHistory");
        
    }
    
    bool Vendor::checkPin (string inputPin, FilesystemData data, User customer ){ // Will need some way to access user's pin. Maybe do this
        // on account end?
        ENTER("Vendor::checkPin");
       // User customer = context.getData().getUser(inputUsername);
        
        if (data.checkPin(customer, inputPin) ) { // CHANGE THIS TO APPROPRIATE MODIFIER
        
            return true;
        }
        else{
            return false;
        }
        
        EXIT("Vendor::checkPin"); //May not be reached.
    }
    
    bool Vendor::isCardFrozen (FilesystemData data, User customer){
        
        //Have to wait and see how the credit card is implemented.
        if(Io::fileExists(customer.Name+".creditcard.frozen.dat")){
            return true;
        }
        else{
            return false;
           }
        
    }
    
    string Vendor::loadPurchaseHistory(){
        
        ENTER("Vendor::loadPurchaseHistory");
        
        string readIn;
        string purchaseHistory = "";
        ifstream file("/vendor.history.dat");
        
        while (getline(file,readIn))
        {
            purchaseHistory += readIn;
            purchaseHistory.push_back('\n');
        }
        
        EXIT("Vendor::loadPurchaseHistory");
        
        return purchaseHistory;
        
       
        
        
    }
    
    void Vendor::purchaseSession (){
        
        // You did a lot of -> without checking whether you should in this one.
        
        /* Real date function adapted from http://stackoverflow.com/questions/16357999/current-date-and-time-as-string . This one suited my purpose by providing a simple, streamlined way to get the real date. I didn't feel it should be controlled by the vendor. */
        
       /* time_t timeVar;
        struct tm * timeinfo;
        char buffer[80];
        
        time(&timeVar);
        timeinfo = localtime(&timeVar);
        strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
        string date (buffer); */ //Turns out you'll use this in the update function.
        //cout << date;
        
        
        /*
         
         This chunk is for accessing and saving information to the User's account.
         
         */
        FilesystemData* _transferData;
        Options::OptionContext* _transferContext;
        Session* _transferSession;
        
        _transferData = new FilesystemData();
        _transferSession = new Session( *_transferData );
        _transferContext = 0;
        
        _transferData->initialize();
        
        Vendor thisVendor = Vendor(Vendor::loadPurchaseHistory(), 0);
    
        
        string inputUsername = _transferSession->vendorHelper();
        
        
        
        _transferContext = new Options::OptionContext( *_transferData, *_transferSession );
        
        //OptionContext transferContext = *_transferContext;
        
        
        //string inputUsername;
        string inputPin;
        double purchasePrice = (rand () % 10000 + 1)/100;
        
        //cout << "To simulate swiping a card, please enter the username of the person to be used";
        //cin >> inputUsername;
        
        // Log in username and check if valid. If no checking account, cancel.
        
        
        
        cout << "Please enter your pin (####): ";
        cin >> inputPin;
        User customer = _transferContext->getData().getUser(inputUsername);
        
        if (thisVendor.checkPin(inputPin, *_transferData, customer)){
            
            if (thisVendor.isCardFrozen(*_transferData,customer)){
                cout << "Sorry, but your card has been frozen. Please contact the bank for details" << endl;
            }
            else{
            char inputChoice;
            
            cout << "The price of this purchase is $" << purchasePrice << ". Accept? [y/n]: ";
            cin >> inputChoice;
            
            if (inputChoice == 'y'){
                
                
                cout << inputUsername << " test." << endl;
                Account creditAccount = _transferData->getAccount(customer, CreditCard);
                
                if (_transferData->doesAccountExist(customer, CreditCard) == false){
                    Logger::error() << "No account exists!" << endl;
                }
                else{
                    
                    //Specifically does not check at this point whether this is a valid op or not
                    creditAccount.withdraw( purchasePrice );
                   
                    // Collectively, these three statements will add a transaction history.
                    _transferData->storeAccount( customer, creditAccount );
                    _transferData->storeTransaction ( inputUsername, CreditCard, thisVendor.updateCustomer(purchasePrice) );
                    thisVendor.updateVendor(purchasePrice, inputUsername);
                    
                    
                }
                
                
                
                
            }
            else {
                
                cout << "Purchase rejected" << endl;
                
            }
            }

        }
        else{
            cout << "Incorrect pin" << endl;
        }
        
       // -------------
    }
    
    /**
     
     Adds the purchase to the log for both the Vendor and the bank, and updates vendor funds.
     
     */
    void Vendor::updateVendor (double purchasePrice, string clientName ){
        
        time_t timeVar;
        struct tm * timeinfo;
        char buffer[80];
        
        time(&timeVar);
        timeinfo = localtime(&timeVar);
        strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
        string date (buffer);
        
        string inputString = buffer;
        inputString += " ";
        inputString += clientName;
        inputString += " $";
        
        
        std::ostringstream appendingDouble;
        appendingDouble << purchasePrice;
        std::string appendingDoubleString = appendingDouble.str();
        
        cout << appendingDoubleString;
        
        inputString += appendingDoubleString;
        
        if (Io::fileExists(Configuration::dataDirectory+"/vendor.history.dat")==false){
            
            cout << "Creating vend history";
            
            Io::createFile(Configuration::dataDirectory + "/" + "vendor.history.dat", inputString);
            Io::createFile(Configuration::dataDirectory + "/"+"/vendorandbank.history.dat", inputString);
            
        }
        else{
        string location = Configuration::dataDirectory + "/" + "vendor.history.dat";
            //const char * locationchar = location.c_str();
       /* ofstream vendorFile (locationchar , ofstream::app);
        ofstream bankFile (locationchar, ofstream::app);
        
        
        vendorFile << inputString;
        bankFile << inputString;
        vendorFile.close();
        bankFile.close(); */
            
            Io::appendLineToFile(location, inputString);
            Io::appendLineToFile(Configuration::dataDirectory+"/vendorandbank.history.dat",inputString);
            
        }
        
        ifstream vendorFileRead;
        double vendorFunds = 0;
        
        if (Io::fileExists(Configuration::dataDirectory+"/vendor.purchase.dat")==false){
            
            Io::createFile(Configuration::dataDirectory+"/vendor.purchase.dat", purchasePrice);
            
        }
        else{
            
            //Gets the previous balance, adds the new balance, overwrites the file.
            string location = Configuration::dataDirectory + "/vendor.purchase.dat";
            const char * charLocation = location.c_str();
            
            vendorFileRead.open(charLocation);
            vendorFileRead >> vendorFunds;
            vendorFileRead.close();
            vendorFunds += purchasePrice;
            ofstream fundsOverwrite (charLocation, ofstream::trunc);
            fundsOverwrite << vendorFunds;
            fundsOverwrite.close();
            
        }
        
        
        
        
        
        /*myfile.open ("example.txt");
        myfile << "Writing this to a file.\n";
        myfile.close(); */
        
    }
    //Not entirely sure what parameters I'll need here. Context, maybe? Context would work.
    string Vendor::updateCustomer(double purchasePrice){
        
        ENTER("Vendor::updateCustomer");
        
        time_t timeVar;
        struct tm * timeinfo;
        char buffer[80];
        
        time(&timeVar);
        timeinfo = localtime(&timeVar);
        strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
        string date (buffer);
        
        string inputString = buffer;
        inputString += " ";
        
        std::ostringstream appendingDouble;
        appendingDouble << purchasePrice;
        std::string appendingDoubleString = appendingDouble.str();
        
        inputString += appendingDoubleString;
        
        EXIT("Vendor::updateCustomer");
        
        return inputString;
        
        
    }
    
    
    }
    
    
    
