#include "account.h"
#include "checkingAccount.h"
#include "savingsAccount.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void readToCheckFile(CheckingAccount checkAcc);
void readToSavingsFile(SavingsAccount saveAcc);

int main()
{
   vector <CheckingAccount> checkingAccounts;
   vector <SavingsAccount> savingsAccounts;
   string userEnter;
   do{
      cout<<"open account [1]\n" << "login [2]\n" << "exit [3]\n";
      getline(cin,userEnter);
      if(userEnter == "1")
      {
         string newAccount;
         cout<<"Enter new account number";
         getline(cin, newAccount);
         
         int checkIfUnique =0;
         for(int i=0; i < checkingAccounts.size(); i++)
         {
            if (checkingAccounts[i].getAccountNumber() == newAccount)
            {
               checkIfUnique = 1;
            }
         }
         if(checkIfUnique == 0)
         {
            CheckingAccount newCheckAcc(newAccount);
            SavingsAccount newSavAcc(newAccount);
            
         }
         
      }
      else if(userEnter == "2")
      {
         
      }
      else if(userEnter == "3")
      {
         cout<<"Goodbye"<<endl;
      }
      else
      {
         cout<<"Enter valid number"<<endl;
      }
   }while(userEnter != "3");
   

   return 0;
}

