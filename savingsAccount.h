#ifndef SAVINGSACCOUNT
#define SAVINGSACCOUNT
#include "account.h"
#include <string>

using namespace std; 

class SavingsAccount : public Account{
    private:
        string status;
    public:
        SavingsAccount(string SAccNum, double SBal, double SIntRate, double SAnnServCharge, string AccStatus);
        void setAccountActiveStatus();
        virtual void serviceCharge();
        void checkInterestRate();
        void yearlyCharge();
        void setAnnualServiceCharge(double rate);
};

SavingsAccount::SavingsAccount(string SAccNum = "0", double SBal = 0.0, double SIntRate = 0.0, double SAnnServCharge = 0.0, string AccStatus = "active") : Account(SAccNum, SBal, SIntRate, SAnnServCharge){
    //Constructor 
    status =  AccStatus;
    accountNumber = "S" + accountNumber;
}

void SavingsAccount::setAnnualServiceCharge(double rate = 0.0){
    annualServiceCharge = 0.0;
}


void SavingsAccount::setAccountActiveStatus(){
    if (balance < 1.0){
        status = "closed";
    }else if(balance < 50.0){
        status = "inactive";
    }
}

void SavingsAccount::serviceCharge(){
    if (balance < 50.0){
        balance -= 5.0;
    }
}

void SavingsAccount::checkInterestRate(){
    if(interestRate > 10.0){
        interestRate = 10.0;
        cout << "INTEREST RATE CANNOT BE LARGER THAN 10%\nINTEREST RATE WILL BE SET TO 10.0%\n";
    }else if(interestRate < 0.1){
        interestRate = 0.1;
        cout << "INTEREST RATE CANNOT BE SMALLER THAN 0.1%\nINTEREST RATE WILL BE SET TO 0.1%\n";
    }
}

void SavingsAccount::yearlyCharge(){
    annualServiceCharge = 0.0;
}

#endif
