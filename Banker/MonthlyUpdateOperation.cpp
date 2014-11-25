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
                    
                    Io::initFromFile(user->Name + ".creditcard.dat.paymentchoice.dat", paymentchoice);
                    
                    
                    //cout << Configuration::dataDirectory+user->Name +".creditcard.dat.paymentchoice.dat" << endl;
                    cout << paymentchoice << " debug" <<endl;
                    
                    if (paymentchoice.compare("full")==0 || paymentchoice.compare("minimum")==0){
                        Io::initFromFile(user->Name+".creditcard.dat", payment);
                        payment = payment * -1; // Balance is stored as -ve.
                        
                        Account account = context.getData().getAccount(*user, Checking);
                        
                        if ( account.Balance - payment < 0 ){
                            
                            Logger::error() << "Invalid. The balance will be less than 0. Overdraft is not enabled" << endl;
                            
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
                            }
                            
                            
                        } else {
                            account.withdraw( payment );
                            context.getData().storeAccount( *user, account );
                            
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
                            }
                            
                        }
                        
                        
                        
                        
                        
                    }
                    else if (paymentchoice.compare("minimum")==0){
                        Io::initFromFile(Configuration::dataDirectory+user->Name+".creditcard.dat",payment);
                        payment = payment * -1 * 0.1; // Minimum payment is ten percent, hence 0.1
                    }
                    else{
                        cout << "Invalid payment choice on file"<< endl;
                    }
                    
                    
                    
                    
                }
                
            }
            
        }
        
    }
    
    
}