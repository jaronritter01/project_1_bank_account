#ifndef ACCOUNT
#define ACCOUNT

#include <string>

class Account{
    private:
        int accountNumber;
        double balance;
        double interestRate;
        double annualServiceCharge;
    public:
        Account(int accNum, double bal, double intRate, double annServCharge);
        virtual bool deposit(double dAmount);
        virtual bool withdraw(double wAmount);
        double calcInt();
        void yearlyCharge();
        virtual bool closeAcc();
};

Account::Account(int accNum=0, double bal=0.0, double intRate=0.0, double annServCharge=0.0){
    accountNumber = accNum;
    balance = bal;
    interestRate = intRate;
    annualServiceCharge = annServCharge;
}

bool Account::deposit(double dAmount){
    if(dAmount > 0){
        balance += dAmount;
        return true;
    }else{
        return false;
    }
}

bool Account::withdraw(double wAmount){
    if(wAmount > 0){
        balance -= wAmount;
        return true;
    }else{
        return false;
    }
}

double Account::calcInt(){
    
}

#endif