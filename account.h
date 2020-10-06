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
        void calcInt();
        void yearlyCharge();
        double getBalance() const;
        int getAccountNumber() const;
        double getInterestRate() const;
        virtual void closeAcc();
};

Account::Account(int accNum=0, double bal=0.0, double intRate=0.0, double annServCharge=0.0){
    accountNumber = accNum;
    balance = bal;
    interestRate = intRate;
    annualServiceCharge = annServCharge;
}

double Account::getBalance() const{
    return balance;
}

int Account::getAccountNumber() const{
    return accountNumber;
}

double Account::getInterestRate() const{
    return interestRate;
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

void Account::calcInt(){
    double dailyInterestRate = interestRate / 365.25;
    double dailyInterest = balance * dailyInterestRate;
    balance += dailyInterest;
}

void Account::yearlyCharge(){
    //Only needs to happen once a year
    balance -= annualServiceCharge;
}

void Account::closeAcc(){
    balance = 0;
    annualServiceCharge = 0;
}

#endif