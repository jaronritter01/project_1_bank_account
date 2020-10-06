#ifndef SAVINGSACCOUNT
#define SAVINGSACCOUNT
#include "account.h"

class SavingsAccount : public Account{
    private:
        bool status;
    public:
        SavingsAccount(int accNum, double bal, double intRate, double annServCharge, bool AccStatus);
};

SavingsAccount::SavingsAccount(int SAccNum = 0, double SBal = 0.0, double SIntRate = 0.0, double SAnnServCharge = 0.0, bool AccStatus = true) : 
Account(SAccNum, SBal, SIntRate, SAnnServCharge){
    //Constructor
    status =  AccStatus;
}

#endif
