#ifndef ACCOUNT
#define ACCOUNT

#include <string>
#include <time.h>
//make acc num a string

using namespace std;

class Account{
    protected:
        //Several data members all are protected so that the child classes can still access these

        string accountNumber; // stores account number
        double balance; // stores balance
        double interestRate; //stores getInterestRate
        double annualServiceCharge; // stores the service charge
        tm *timeCreated; // Stores the time the account was created
        
    public:
        //Several methods
        Account(string accNum, double bal, double intRate, double annServCharge);
        virtual bool deposit(double dAmount);
        virtual bool withdraw(double wAmount);
        void setAnnualServiceCharge(double rate);
        void calcInt();
        void yearlyCharge();
        double getBalance() const;
        string getAccountNumber() const;
        double getInterestRate() const;
        double getAnnualServiceCharge() const;
        virtual void closeAcc();
        int getMonthCreated() const;
        int getDayCreated() const;
        int getYearCreated() const;
        string getDateCreated() const;
};

Account::Account(string accNum="0", double bal=0.0, double intRate=0.0, double annServCharge=0.0){
    //constructor
    accountNumber = accNum;
    balance = bal;
    interestRate = intRate;
    annualServiceCharge = annServCharge;

    /********************************************/
    // This is what sets the time to the time of// 
    // creation                                 //
                                                //
    time_t currentTime;                         //
    time(&currentTime);                         //
    timeCreated = localtime(&currentTime);      //
    /********************************************/

}

string Account::getDateCreated() const{
    //Getter for the creation date of the account
    string dateLine, day, month, year;
    day = to_string(timeCreated->tm_mday);
    month = to_string(timeCreated->tm_mon + 1);
    year = to_string(timeCreated->tm_year + 1900);
    dateLine = month + ":" + day + ":" + year;
    
    return dateLine;
}

int Account::getYearCreated() const{
    //getter for the year of creation
    return timeCreated->tm_year + 1900;
}

int Account::getDayCreated() const{
    //getter for the day of creation
    return timeCreated->tm_mday;
}

int Account::getMonthCreated() const{
    //getter for the month of creation
    return timeCreated->tm_mon + 1;
}

void Account::setAnnualServiceCharge(double rate){
    //setter for the annual service charge
    annualServiceCharge = rate;
}

double Account::getAnnualServiceCharge() const{
    //getter for the annual service charge
    return annualServiceCharge;
}

double Account::getBalance() const{
    //getter for balance
    return balance;
}

string Account::getAccountNumber() const{
    //getter for account number
    return accountNumber;
}

double Account::getInterestRate() const{
    //getter for interest rate
    return interestRate;
}

bool Account::deposit(double dAmount){
    /*deposit function: will return true if the value inputed is a valid on and if the transaction occured succefully
      and will return false otherwise
    */
    if(dAmount > 0){
        balance += dAmount;
        return true;
    }else{
        return false;
    }
}

bool Account::withdraw(double wAmount){
    /*
    withdraw function: will return true if the value inputed is a valid on and if the transaction occured succefully
    and will return false otherwise
    */
    if(wAmount > 0){
        balance -= wAmount;
        return true;
    }else{
        return false;
    }
}

void Account::calcInt(){
    /*
    Will calculate interest and add it to the account 
    NOTE: INTEREST IS ADDED DAILY
    */
    double dailyInterestRate = interestRate / 365.25;
    double dailyInterest = balance * dailyInterestRate;
    balance += dailyInterest;
}

void Account::yearlyCharge(){
    /*
    Will charge the account a annual service fee
    NOTE: SHOULD ONLY HAPPEN ONCE A YEAR
    */
    balance -= annualServiceCharge;
}

void Account::closeAcc(){
    /*
    This will set the balance and the service fee to 0 
    NOTE: THE INTEREST RATE AND ACCOUNT NUMBER OF THE ACCOUNT WILL STILL BE ACCESSIBLE
    */
    balance = 0;
    annualServiceCharge = 0;
}

#endif