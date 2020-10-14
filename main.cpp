#include "account.h"
#include "checkingAccount.h"
#include "savingsAccount.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>

using namespace std;

vector<CheckingAccount> readFromFileChecking();
vector<SavingsAccount> readFromFileSavings();
void writeToFile(vector<CheckingAccount> &checkingAccounts, vector<SavingsAccount> &savingsAccounts);

int main()
{
   vector <CheckingAccount> checkingAccounts;
   vector <SavingsAccount> savingsAccounts;
   checkingAccounts = readFromFileChecking();
   savingsAccounts = readFromFileSavings();

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
                                 cout << "enter amount to deposit \n" ;
                                 string amountDep;
                                 getline(cin,amountDep);
                                 double amount = stod(amountDep);
                                 bool value = checkingAccounts[accountLocation].deposit(amount);
                                 if(value = false)
                                 {
                                    cout<< "could not deposit" <<endl;
                                 }               
                                 break;
                              }
                              case 3:{
                                 cout << "enter amount to withdraw \n";
                                 string amountWth;
                                 getline(cin,amountWth);
                                 double amount = stod(amountWth);
                                 bool value = checkingAccounts[accountLocation].deposit(amount);
                                 if(value = false)
                                 {
                                    cout<< "could not withdraw" << endl;
                                 }
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
                                 cout << "Enter amount to deposit \n";
                                 string amountDep;
                                 getline(cin,amountDep);
                                 double amount = stod(amountDep);
                                 bool value = savingsAccounts[accountLocation].deposit(amount);
                                 if(value = false)
                                 {
                                    cout<< "could not deposit" <<endl;
                                 }         
                                 break;
                              }
                              case 3:{
                                 cout << "Enter amount to withdraw \n";
                                 string amountWth;
                                 getline(cin,amountWth);
                                 double amount = stod(amountWth);
                                 bool value = savingsAccounts[accountLocation].deposit(amount);
                                 if(value = false)
                                 {
                                    cout<< "could not withdraw" << endl;
                                 }
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
   
   writeToFile(checkingAccounts, savingsAccounts);
   
   
   return 0;
}

void writeToFile( vector<CheckingAccount> &checkingAccounts, vector<SavingsAccount> &savingsAccounts)
{
   ofstream outFile;
   
   outFile.open("accounts.txt");
   for(int i =0; i < checkingAccounts.size() ;i++)
   {
      outFile<< checkingAccounts[i].getAccountNumber() << endl;
      outFile<< checkingAccounts[i].getBalance() << endl;
      outFile<< checkingAccounts[i].getInterestRate() <<endl;
      outFile<< checkingAccounts[i].getAnnualServiceCharge() <<endl;
      outFile<< savingsAccounts[i].getAccountNumber() << endl;
      outFile<< savingsAccounts[i].getBalance()<< endl;
      outFile<< savingsAccounts[i].getInterestRate()<< endl;
      outFile<< savingsAccounts[i].getAnnualServiceCharge()<< endl;
      outFile<< savingsAccounts[i].getAccountActiveStatus() << endl;
   }
   
   outFile.close();
}

vector<CheckingAccount> readFromFileChecking()
{
   vector<CheckingAccount> temp;
   ifstream inFile;
   string text;
   
   inFile.open("accounts.txt");

   while(inFile)
   {
      getline(inFile,text);
      if(text.find('C') == 0)
      {
         string accountNumber = text.substr(1,text.length());
         getline(inFile,text);
         double balance = stod(text);
         getline(inFile,text);
         double interestRate = stod(text);
         getline(inFile, text);
         double annualServiceCharge = stod(text);
         
         CheckingAccount chekAcc(accountNumber, balance, interestRate, annualServiceCharge);
         temp.push_back(chekAcc);
         
      }
   }
   
   inFile.close();
   return temp;
}

vector<SavingsAccount> readFromFileSavings()
{
   vector<SavingsAccount> temp;
   ifstream inFile;
   string text;
   
   inFile.open("accounts.txt");
   while(inFile)
   {
      getline(inFile,text);
      if(text.find('S') == 0)
      {
         string accountNumber = text.substr(1,text.length());
         getline(inFile,text);
         double balance = stod(text);
         getline(inFile,text);
         double interestRate = stod(text);
         getline(inFile, text);
         double annualServiceCharge = stod(text);
         getline(inFile,text);
         string status = text;
         
         SavingsAccount saveAcc(accountNumber, balance, interestRate, annualServiceCharge,status);
         temp.push_back(saveAcc);
         
      }
   }
   
   inFile.close();
    return temp;
}
