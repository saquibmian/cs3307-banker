//
//  MonthlyUpdateOperation.cpp
//  Banker
//
//  Created by Brent Davis on 2014-11-25.
//  Copyright (c) 2014 CS3307 Assignment 1 Group 22. All rights reserved.
//

#include "MonthlyUpdateOperation.h"
#include "FileIo.h"

using namespace Accounts;

namespace Operations{
    
    void MonthlyUpdateOperation::execute(OptionContext context){
        ENTER("MonthlyUpdateOperation::Execute");
        
        vector<User> users = context.getData().getAllUsers();
        
        
        for ( vector<User>::iterator iter = users.begin(); iter!= users.end(); iter++){
            
            User* user = iter.base();
            if (user->Role == Manager || user->Role == Client ){
                
                if (context.getData().doesAccountExist(*user, CreditCard)){
                    
                    string paymentchoice;
                    double payment;
                    double creditBalance;
                    
                    Io::initFromFile(user->Name + ".creditcard.dat.paymentchoice.dat", paymentchoice);
                    
                    
                    //cout << Configuration::dataDirectory+user->Name +".creditcard.dat.paymentchoice.dat" << endl;
                   // cout << paymentchoice << " debug" <<endl;
                    
                    if (paymentchoice.compare("full")==0){
                        Io::initFromFile(user->Name+".creditcard.dat", creditBalance);
                        payment = creditBalance * -1; // Balance is stored as -ve.
                        
                        //payment = creditBalance;
                        Account account = context.getData().getAccount(*user, Checking);
                        
                        if ( account.Balance - payment < 0 ){
                            
                            
                            ENTER("Bank::FailedPayment&freezingCustomerCard");
                            Logger::error() << "Card Frozen." << endl;
                            
                            if(Io::fileExists(user->Name+".creditcard.dat.payments.dat")){
                                
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Failed Payment";
                                
                                Io::appendLineToFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                creditBalance = (creditBalance+account.Balance)*1.02; //2% interest.
                                account.withdraw(account.Balance);
                                context.getData().storeAccount( *user, account );
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                Io::createFile(user->Name+".creditcard.frozen.dat","Frozen");
                                
                                
                            }
                            else{
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Failed Payment";
                                
                                Io::createFile(user->Name+".creditcard.dat.payments.dat", inputString);
                            
                                creditBalance = (creditBalance+account.Balance)*1.02;
                                account.withdraw(account.Balance);
                                context.getData().storeAccount( *user, account );
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                Io::createFile(user->Name+".creditcard.frozen.dat","Frozen");
                            
                            }
                            
                            
                            EXIT("Bank::FailedPayment&freezingCustomerCard");
                            
                            
                        } else {
                            account.withdraw( payment );
                            context.getData().storeAccount( *user, account );
                            
                            ENTER("customer::SuccessfulPayment");
                            
                            if(Io::fileExists(user->Name+".creditcard.dat.payments.dat")){
                                
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Successful Payment";
                                
                                Io::appendLineToFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                
                                creditBalance = (creditBalance+payment)*1.02;
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                
                                if (Io::fileExists(user->Name+".creditcard.frozen.dat")){
                                    string path = user->Name+".creditcard.frozen.dat";
                                    const char* pathchar = path.c_str();
                                    remove( pathchar );
                                }
                                
                            }
                            else{
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Successful Payment";
                                
                                Io::createFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                creditBalance = (creditBalance+payment)*1.02;
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                
                                if (Io::fileExists(user->Name+".creditcard.frozen.dat")){
                                    string path = user->Name+".creditcard.frozen.dat";
                                    const char* pathchar = path.c_str();
                                    remove( pathchar );
                                }
                                
                            }
                         EXIT("customer::SuccessfulPayment");
                        }
                        
                        
                        
                        
                        
                    }
                    else if (paymentchoice.compare("minimum")==0){
                        Io::initFromFile(user->Name+".creditcard.dat",creditBalance);
                        payment = creditBalance * -1 * 0.1; // Minimum payment is ten percent, hence 0.1
                        
                        Account account = context.getData().getAccount(*user, Checking);
                        
                        if ( account.Balance - payment < 0 ){
                            
                            
                            ENTER("Bank::FailedPayment&freezingCustomerCard");
                            
                            Logger::error() << "Card frozen." << endl;
                            
                            if(Io::fileExists(user->Name+".creditcard.dat.payments.dat")){
                                
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Failed Payment";
                                
                                Io::appendLineToFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                //creditBalance = creditBalance*1.02; //2% interest.
                                creditBalance = (creditBalance+account.Balance)*1.02;
                                account.withdraw(account.Balance);
                                context.getData().storeAccount( *user, account );
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                Io::createFile(user->Name+".creditcard.frozen.dat","Frozen");
                                
                                
                            }
                            else{
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Failed Payment";
                                
                                Io::createFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                //creditBalance = creditBalance*1.02;
                                creditBalance = (creditBalance+account.Balance)*1.02;
                                account.withdraw(account.Balance);
                                context.getData().storeAccount( *user, account );
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                Io::createFile(user->Name+".creditcard.frozen.dat","Frozen");
                                
                            }
                            
                            EXIT("Bank::FailedPayment&freezingCustomerCard");
                            
                            
                        } else {
                            account.withdraw( payment );
                            context.getData().storeAccount( *user, account );
                            
                            ENTER("customer::SuccessfulPayment");
                            
                            if(Io::fileExists(user->Name+".creditcard.dat.payments.dat")){
                                
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Successful Payment";
                                
                                Io::appendLineToFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                
                                creditBalance = (creditBalance+payment)*1.02;
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                Io::createFile(user->Name+".creditcard.transactions.dat","");
                                
                                if (Io::fileExists(user->Name+".creditcard.frozen.dat")){
                                    string path = user->Name+".creditcard.frozen.dat";
                                    const char* pathchar = path.c_str();
                                    remove( pathchar );
                                }
                                
                                
                            }
                            else{
                                
                                time_t timeVar;
                                struct tm * timeinfo;
                                char buffer[80];
                                
                                time(&timeVar);
                                timeinfo = localtime(&timeVar);
                                strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
                                string date (buffer);
                                
                                string inputString = buffer;
                                inputString += " Successful Payment";
                                
                                Io::createFile(user->Name+".creditcard.dat.payments.dat", inputString);
                                
                                creditBalance = (creditBalance+payment)*1.02;
                                Io::createFile(user->Name+".creditcard.dat",creditBalance);
                                
                                if (Io::fileExists(user->Name+".creditcard.frozen.dat")){
                                    string path = user->Name+".creditcard.frozen.dat";
                                    const char* pathchar = path.c_str();
                                    remove( pathchar );
                                }
                                
                            }
                            
                            EXIT("customer::SuccessfulPayment");
                            
                        }
                        
                        
                        
                        
                        
                        
                        
                    }
                    else{
                        cout << "Invalid payment choice on file"<< endl;
                    }
                    
                    
                    
                    
                }
                
            }
            
        }
        
        EXIT("MonthlyUpdateOperation::Execute");
        
    }
    
    
}