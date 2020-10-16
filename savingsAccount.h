#ifndef SAVINGSACCOUNT
#define SAVINGSACCOUNT

#include "account.h" 
#include <iostream>
#include <string>

using namespace std; 

class SavingsAccount : public Account{ // Child of Account 
    private:
        //This is the only added data type
        string status;
    public:
        //Methods
        SavingsAccount(string SAccNum, double SBal, double SIntRate, double SAnnServCharge, string AccStatus);
        void setAccountActiveStatus();
        void checkInterestRate();
        void yearlyCharge();
        void setAnnualServiceCharge(double rate);
        bool withdraw(double wAmount);
        bool deposit(double dAmount);
        void closeAcc(); 
        string getAccountActiveStatus() const;
};

SavingsAccount::SavingsAccount(string SAccNum = "0", double SBal = 0.0, double SIntRate = 0.0, double SAnnServCharge = 0.0, string AccStatus = "active") : Account(SAccNum, SBal, SIntRate, SAnnServCharge){
    //Constructor 
    status =  AccStatus;
    accountNumber = "S" + accountNumber; // adds s to the account number entered so that it can be a savings account
}

string SavingsAccount::getAccountActiveStatus() const{
    // getter for the status
    return status;
}

void SavingsAccount::closeAcc(){
    //This will close the account and make it unusable but keep a record of it
    balance = 0.0;
    status = "closed";
}


bool SavingsAccount::deposit(double dAmount){
    /*
    This will make it so that if the account is closed no deposit can be made, and if the deposit brings the account above $50 the account will be reactivated
    and if it brings the account inbetween $1 and $50 the status will remain inactive;
    */
    if((dAmount > 0) && (status != "closed")){
        balance += dAmount;
        if(balance >= 50.0){
            status = "active";
            return true;
        }else if((balance >= 1.0) && (balance < 50.0)){
            status = "inactive";
            return true;
        }
        else
        {
            return false;
        }
    }
    else{
        return false;
    }
}

bool SavingsAccount::withdraw(double wAmount){
    /* 
    The way this is set up is that if the account isn't closed or inactive the charge will be taken out only if they have over $50
    or they wont go under $0 from the $5 dollar charge for being under $50 
    */
    if (status != "closed"){
        if ((status == "active") && (balance - wAmount >= 0)){

            if (balance - wAmount >= 50.0){
                balance -= wAmount;
                return true;
            }else if ((balance - wAmount < 50.0) && (balance - (wAmount + 5) >= 0)){
                balance -= wAmount;
                balance -= 5.0;
                return true;
            }else{
                return false;
            } 

        }else{
            return false;
        }
    }else{
        return false;
    }
}

void SavingsAccount::setAnnualServiceCharge(double rate = 0.0){
    //Setter for the annual service charge on the account 
    annualServiceCharge = 0.0;
}


void SavingsAccount::setAccountActiveStatus(){
    //This will set the account active status based on balance
    if (balance < 1.0){
        status = "closed";
    }else if(balance < 50.0){
        status = "inactive";
    }
}

void SavingsAccount::checkInterestRate(){
    // This will be used to see if the interest rate for the account is in the allowed limits 
    if(interestRate > 10.0){
        interestRate = 10.0;
        cout << "INTEREST RATE CANNOT BE LARGER THAN 10%\nINTEREST RATE WILL BE SET TO 10.0%\n";
    }else if(interestRate < 0.1){
        interestRate = 0.1;
        cout << "INTEREST RATE CANNOT BE SMALLER THAN 0.1%\nINTEREST RATE WILL BE SET TO 0.1%\n";
    }
}

void SavingsAccount::yearlyCharge(){
    //setter for the yearly service charge
    annualServiceCharge = 0.0;
}

#endif
