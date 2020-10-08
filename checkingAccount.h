#ifndef CHECKINGACCOUNT
#define  CHECKINGACCOUNT

#include "account.h"
#include <string>

using namespace std;

class CheckingAccount : public Account{
   public:
      CheckingAccount(string accNumber, double bal, double intRate, double annServiceCharge);
      bool deposit(double dAmount);
      bool withdraw(double wAmount);
      void checkBalance();
      
      
};

CheckingAccount:: CheckingAccount(string accNumber = " ", double bal = 0.0, double intRate = 0.0, double annServiceCharge = 0.0) : Account(accNumber,bal,intRate,annServiceCharge)
{
   //constructor
   accountNumber = "C" + accNumber;
}

bool CheckingAccount::deposit(double dAmount)
{
   //allows user to deposit a set amount. if the amount is more than 9999 the account will be flaged with * at end 
   if(dAmount > 0){
        if(dAmount > 9999.0)
         {
            accountNumber = accountNumber + "*";
            balance += dAmount;
         }
         else
         {
            balance += dAmount;
         }
        return true;
    }else{
        return false;
    }  
}

bool CheckingAccount::withdraw(double wAmount)
{
   //withdraws set amount if the amount is more than in balance no money is withdrawn from account and 25 fee is applied. it will also check to see if the account is in the negative 
   //if the amount can be withdrawn then the amount will be withdrawn
    if(wAmount > 0){
        if(balance < wAmount)
        {
           balance -= 25;
           checkBalance();
        }
        else
        {
           balance -= wAmount;
        }
        return true;
    }else{
        return false;
    }
}

void CheckingAccount:: checkBalance()
{
   //checks to see if balance is no longer in the positive if not it will flage account with *
   if(balance < 0.0)
   {
      accountNumber = accountNumber + "*";
   }
}

#endif
