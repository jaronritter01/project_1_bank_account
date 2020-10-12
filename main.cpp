#include "account.h"
#include "checkingAccount.h"
#include "savingsAccount.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

void readToCheckFile(CheckingAccount checkAcc);
void readToSavingsFile(SavingsAccount saveAcc);

int main()
{
   vector <CheckingAccount> checkingAccounts;
   vector <SavingsAccount> savingsAccounts;
   int userEnter;
   do{
      cout<<"[1] Open Account \n" << "[2] Login \n" << "[3] Exit \n";
      cin >> userEnter;
      string accountNumber;
      int checkAccNum = 0;
      switch (userEnter){
         case 1:{
            string newAccountNum;
            cin.ignore();
            cout<<"Enter new account number: ";
            getline(cin, newAccountNum);
            
            //This is to check if the account number inputed has letters in it, making it invalid
            for(int i = 0; i < newAccountNum.length(); i++){
               if(isalpha(newAccountNum[i])){
                  checkAccNum = 1;
               }
            }

            if (checkAccNum != 1){
               int checkIfUnique = 0;
               for(int i=0; i < checkingAccounts.size(); i++)
               {
                  string checkingAccountNum = checkingAccounts[i].getAccountNumber().substr(1, checkingAccounts[i].getAccountNumber().length());
                  if (checkingAccountNum == newAccountNum)
                  {
                     checkIfUnique = 1;
                  }
               }
               
               if(checkIfUnique == 0)
               {
                  CheckingAccount newCheckAcc(newAccountNum);
                  SavingsAccount newSavAcc(newAccountNum);
                  checkingAccounts.push_back(newCheckAcc);
                  savingsAccounts.push_back(newSavAcc);
               }else{
                  cout << "An account with this account number already exists\n";
               }

            }else{
               cout << "The inputed Account number is not a valid number\n";
            }
            break;
         }
         case 2:{
            cout << "Please enter your account number: ";
            cin >> accountNumber;


            int accountLocation = 0, doesExist = 0;

            for(int i = 0; i < checkingAccounts.size(); i++){
               string accountNumberNoLetter = checkingAccounts[i].getAccountNumber().substr(1, checkingAccounts[i].getAccountNumber().length());
               if (accountNumber == accountNumberNoLetter){
                  accountLocation = i;
                  doesExist = 1;
               }
            }

            int selection = 0;
            if (doesExist == 1){
               while(selection !=3){
                  cout << "Welcome\nPlease select an option\n[1] Checking\n[2] Savings\n[3] Return to Menu";
                  cin >> selection;

                  int option = 0;
                  switch (selection){
                     case 1:{
                        while(option != 4){
                           cout << "Checking\n[1] Balance\n[2] Deposit\n[3] Withdraw\n[4] Return to Menu\n";
                           cin >> option;
                           switch (option){
                              case 1:{
                                 cout << "$" << checkingAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                                 cout << "Case 2\n";
                                 break;
                              }
                              case 3:{
                                 cout << "Case 3\n";
                                 break;
                              }
                              case 4:{
                                 cout << "Returning...\n";
                                 break;
                              }
                              default:{
                                 cout << "Invalid Option Selection\n";
                              }
                           }
                        }
                        break;
                     }
                     case 2:{
                        while(option != 4){
                           cout << "Savings\n[1] Balance\n[2] Deposit\n[3] Withdraw\n[4] Return to Menu\n";
                           cin >> option;
                           switch (option){
                              case 1:{
                                 cout << "$" << savingsAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                                 cout << "Case 2\n";
                                 break;
                              }
                              case 3:{
                                 cout << "Case 3\n";
                                 break;
                              }
                              case 4:{
                                 cout << "Returning\n";
                                 break;
                              }
                              default:{
                                 cout << "Invalid Option Selection\n";
                              }
                           }
                        }
                        break;
                     }
                     
                     case 3:{
                        cout << "\nReturning...\n";
                        cout << '\n';
                        break;
                     }
                     default:{
                        cout << "Invalid Selection\n";
                        break;
                     }
                  }
               }
            }else{
               cout << "This account does not exist \n";
               cout << '\n';
            }
            break;
         }
         case 3:{
            cout << "Goodbye!\n"; 
            break;
         }
         default:{
            cout << "Enter a valid number: \n";
         }

      }
      
   }while(userEnter != 3);
   

   return 0;
}