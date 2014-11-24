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
    
    bool checkPin (int inputPin ){ // Will need some way to access user's pin. Maybe do this
        // on account end?
        ENTER("Vendor::checkPin");
        
        if (inputPin == 2332 ) { // CHANGE THIS TO APPROPRIATE MODIFIER
        
            return true;
        }
        else{
            return false;
        }
        
        EXIT("Vendor::checkPin"); //May not be reached.
    }
    
    bool isCardFrozen (){
        
        //Have to wait and see how the credit card is implemented.
        int funny = 2;
        
        return true;
    }
    
    static string loadPurchaseHistory(){
        
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
    
    static void purchaseSession (){
        
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
        IData* _transferData;
        OptionContext* _transferContext;
        Session* _transferSession;
        
        _transferData = new FilesystemData();
        _transferSession = new Session( *_transferData );
        _transferContext = 0;
        
        _transferData->initialize();
        
        Vendor thisVendor = Vendor(Vendor::loadPurchaseHistory(), 0);
    
        
        string inputUsername = _transferSession->vendorHelper();
        
        
        
        _transferContext = new OptionContext( *_transferData, *_transferSession );
        
        //OptionContext transferContext = *_transferContext;
        
        
        //string inputUsername;
        int inputPin;
        int purchasePrice = (rand () % 10000 + 1)/100;
        
        //cout << "To simulate swiping a card, please enter the username of the person to be used";
        //cin >> inputUsername;
        
        // Log in username and check if valid. If no checking account, cancel.
        
        
        
        cout << "Please enter your pin (####): ";
        cin >> inputPin;
        
        if (checkPin(inputPin)){
            
            if (isCardFrozen()){
                cout << "Sorry, but your card has been frozen. Please contact the bank for details" << endl;
            }
            else{
            char inputChoice;
            
            cout << "The price of this purchase is $" << purchasePrice << ". Accept? [y/n]: ";
            cin >> inputChoice;
            
            if (inputChoice == 'y'){
                
                User customer = _transferContext->getData().getUser(inputUsername);
                cout << inputUsername << " test." << endl;
                Account creditAccount = _transferData->getAccount(customer, CreditCard);
                
                if (_transferData->doesAccountExist(customer, CreditCard) == false){
                    Logger::error() << "No account exists!" << endl;
                }
                else{
                    
                    //Specifically does not check at this point whether this is a valid op or not
                    creditAccount.withdraw( purchasePrice );
                    _transferData->storeAccount( customer, creditAccount );
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
    void updateVendor (double purchasePrice, string clientName ){
        
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
        inputString += purchasePrice;
        
        ofstream vendorFile ("/vendor.history.dat", ofstream::app);
        ofstream bankFile ("/vendorandbank.history.dat", ofstream::app);
        ifstream vendorFileRead;
        
        vendorFile << inputString;
        bankFile << inputString;
        vendorFile.close();
        bankFile.close();
        
        double vendorFunds = 0;
        vendorFileRead.open("/vendor.purchase.dat");
        vendorFileRead >> vendorFunds;
        vendorFileRead.close();
        ofstream fundsOverwrite ("/vendor.purchase.dat", ofstream::trunc);
        fundsOverwrite << vendorFunds;
        fundsOverwrite.close();
        
        
        
        
        
        /*myfile.open ("example.txt");
        myfile << "Writing this to a file.\n";
        myfile.close(); */
        
    }
    //Not entirely sure what parameters I'll need here. Context, maybe? Context would work.
    void updateCustomer(double purchasePrice, OptionContext customerContext){
        
        User customer = customerContext.getSession().getUser();
        IData& data = customerContext.getData();
        Account account = data.getAccount(customer,CreditCard);
        
        
    }
    
    
    }
    
    
    
