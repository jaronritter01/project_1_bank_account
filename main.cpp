/*
   this program represents a bank account that can create a account that has two different sub accounts. One account is a checking account this account has interest and a yearly charge fee
   . the other account is a savings account, this account only has interest. Both of the accounts have sepeate balances and both have withdraw and deposit functions.
   The user can choose to enter a new account or login into a checking account or savings account and perform the widthdraw, deposit or just return the balance. 
*/


// declares different account types that are used 
#include "account.h"
#include "checkingAccount.h"
#include "savingsAccount.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <time.h>

using namespace std;



vector<CheckingAccount> readFromFileChecking();
vector<SavingsAccount> readFromFileSavings();
void writeToFile(vector<CheckingAccount> &checkingAccounts, vector<SavingsAccount> &savingsAccounts);
bool checkIfNumber(string number);
double howManyDays(string dateOne, string dateTwo);

int main()
{
   //creates two vectors that contain checking and saving accounts respectivly and then using hte readFromFile functions the accounts stored in accounts.txt are return to vectors.
   vector <CheckingAccount> checkingAccounts;
   vector <SavingsAccount> savingsAccounts;
   checkingAccounts = readFromFileChecking();
   savingsAccounts = readFromFileSavings();

   int userEnter;
   do{
      cout<<"[1] Open Account \n" << "[2] Login \n" << "[3] Exit \n";
      cin >> userEnter;
      string accountNumber;
      bool checkAccNum;
      switch (userEnter){
         case 1:{
            string newAccountNum;
            cin.ignore();
            cout<<"Enter new account number: ";
            getline(cin, newAccountNum);
            
            //This is to check if the account number inputed has letters in it, making it invalid
            checkAccNum = checkIfNumber(newAccountNum);

            if (checkAccNum == true ){
               int checkIfUnique = 0;
               for(int i=0; i < checkingAccounts.size(); i++)
               {
                  string savingsAccountNum = savingsAccounts[i].getAccountNumber().substr(1, savingsAccounts[i].getAccountNumber().length());
                  if (savingsAccountNum == newAccountNum)
                  {
                     checkIfUnique = 1;
                  }
               }
               
               if(checkIfUnique == 0)
               {
                  string sCheckInt;
                  cout<<"Enter Interest for checking Account ";
                  getline(cin,sCheckInt);
                  if(checkIfNumber(sCheckInt) == true)
                  {
                     string sCheckAnnCharge;
                     cout<<"Enter Annual charge for account";
                     getline(cin,sCheckAnnCharge);
                     if(checkIfNumber(sCheckAnnCharge) == true)
                     {
                        string sSaveInt;
                        cout<<"Enter Interest for savings Account";
                        getline(cin,sSaveInt);
                        if(checkIfNumber(sSaveInt) == true)
                        {
                           CheckingAccount newCheckAcc(newAccountNum,0,stod(sCheckInt),stod(sCheckAnnCharge));
                           SavingsAccount newSavAcc(newAccountNum,0,stod(sSaveInt),0);
                           newSavAcc.checkInterestRate();
                           checkingAccounts.push_back(newCheckAcc);
                           savingsAccounts.push_back(newSavAcc);
                        }
                        else
                        {
                           cout << "Invalid input"<<endl;
                        }
                     }
                     else
                     {
                        cout<<"Invalid input" <<endl;
                     }
                  }
                  else
                  {
                     cout <<"Invalid Input" <<endl;
                  }
               
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
                  cout << "Welcome\nPlease select an option\n[1] Checking\n[2] Savings\n[3] Return to Menu\n";
                  cin >> selection;

                  int option = 0;
                  switch (selection){
                     case 1:{
                        while(option != 4){
                           cout << "Checking\n[1] Balance\n[2] Deposit\n[3] Withdraw\n[4] Return to Menu\n";
                           cin >> option;
                           cin.ignore();
                           switch (option){
                              case 1:{
                                 cout << "$" << checkingAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                                 cout << "enter amount to deposit \n" ;
                                 bool checkDep;
                                 string amountDep;
                                 getline(cin,amountDep);
                                 checkDep = checkIfNumber(amountDep);
                                 if(checkDep == true)
                                 {
                                    double amount = stod(amountDep);
                                    bool value = checkingAccounts[accountLocation].deposit(amount);
                                    if(value = false)
                                    {
                                       cout<< "could not deposit" <<endl;
                                    }
                                 }
                                 else
                                 {
                                    cout << "invalid input" << endl;
                                 }             
                                 break;
                              }
                              case 3:{
                                 cout << "enter amount to withdraw \n";
                                 bool checkWth;
                                 string amountWth;
                                 getline(cin,amountWth);
                                 checkWth = checkIfNumber(amountWth);
                                 if(checkWth == true)
                                 {
                                    double amount = stod(amountWth);
                                    bool value = checkingAccounts[accountLocation].deposit(amount);
                                    if(value = false)
                                    {
                                       cout<< "could not withdraw" << endl;
                                    }
                                 }
                                 else
                                 {
                                    cout<<"invalid input"<<endl;
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
                           cin.ignore();
                           switch (option){
                              case 1:{
                                 cout << "$" << savingsAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                                 cout << "Enter amount to deposit \n";
                                 bool checkDep;
                                 string amountDep;
                                 getline(cin,amountDep);
                                 checkDep = checkIfNumber(amountDep);
                                 if(checkDep == true)
                                 {
                                    double amount = stod(amountDep);
                                    bool value = savingsAccounts[accountLocation].deposit(amount);
                                    if(value = false)
                                    {
                                       cout<< "could not deposit" <<endl;
                                    }
                                 }
                                 else
                                 {
                                    cout << "invalid input" << endl;
                                 }        
                                 break;
                              }
                              case 3:{
                                 cout << "Enter amount to withdraw \n";
                                 bool checkWth;
                                 string amountWth;
                                 getline(cin,amountWth);
                                 checkWth = checkIfNumber(amountWth);
                                 if(checkWth == true)
                                 {
                                    double amount = stod(amountWth);
                                    bool value = savingsAccounts[accountLocation].deposit(amount);
                                    if(value = false)
                                    {
                                       cout<< "could not withdraw" << endl;
                                    }
                                 }
                                 else
                                 {
                                    cout<<"invalid input"<<endl;
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
      outFile<< checkingAccounts[i].getDateCreated() << endl;
      outFile<< savingsAccounts[i].getAccountNumber() << endl;
      outFile<< savingsAccounts[i].getBalance()<< endl;
      outFile<< savingsAccounts[i].getInterestRate()<< endl;
      savingsAccounts[i].setAccountActiveStatus();
      outFile<< savingsAccounts[i].getAccountActiveStatus() << endl;
      outFile<< savingsAccounts[i].getDateCreated()<< endl;
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
         string date;
         string accountNumber = text.substr(1,text.length());
         getline(inFile,text);
         double balance = stod(text);
         getline(inFile,text);
         double interestRate = stod(text);
         getline(inFile, text);
         double annualServiceCharge = stod(text);
         getline(inFile,text);
         date = text;
         
         CheckingAccount chekAcc(accountNumber, balance, interestRate, annualServiceCharge);
         string newDate = chekAcc.getDateCreated();
         double days = howManyDays(date,newDate);
         for(int i = 0; i < days; i++)
         {
            chekAcc.calcInt();
         }
         
         days = days / 365;
         
         for(int i = 0; i < days; i++)
         {
            chekAcc.yearlyCharge();
         }
         
         
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
         string date;
         string accountNumber = text.substr(1,text.length());
         getline(inFile,text);
         double balance = stod(text);
         getline(inFile,text);
         double interestRate = stod(text);
         getline(inFile,text);
         string status = text;
         getline(inFile,text);
         date = text;
         
         SavingsAccount saveAcc(accountNumber, balance, interestRate, 0 ,status);
         
         string newDate = saveAcc.getDateCreated();
         double days = howManyDays(date,newDate);
         for(int i =0; i < days ; i++)
         {
            saveAcc.calcInt();
         }
         
         saveAcc.setAccountActiveStatus();
         
         temp.push_back(saveAcc);
         
      }
   }
   
   inFile.close();
    return temp;
}

bool checkIfNumber(string number) 
{
   try
   {
      double test = stod(number);
   }
   catch(const invalid_argument&)
   {
      return false;
   }
   return true;
}

double howManyDays(string dateOne, string dateTwo)
{
   int mon = stoi(dateOne.substr(0, dateOne.find(":")));
   dateOne = dateOne.substr(dateOne.find(":") +1 , dateOne.length());
   int day = stoi(dateOne.substr(0, dateOne.find(":")));
   dateOne = dateOne.substr(dateOne.find(":") +1 , dateOne.length());
   int year = stoi(dateOne.substr(0, dateOne.find(":")));
   
   tm firstDate = tm();
   firstDate.tm_mday = day;
   firstDate.tm_mon = mon - 1;
   firstDate.tm_year = year - 1900;
   
   time_t date1 = mktime(&firstDate);
   
   mon = stoi(dateTwo.substr(0, dateTwo.find(":")));
   dateOne = dateTwo.substr(dateTwo.find(":") +1 , dateTwo.length());
   day = stoi(dateTwo.substr(0, dateTwo.find(":")));
   dateOne = dateTwo.substr(dateTwo.find(":") +1 , dateTwo.length());
   year = stoi(dateTwo.substr(0, dateTwo.find(":")));
   
   tm secondDate = tm();
   secondDate.tm_mday = day;
   secondDate.tm_mon = mon - 1;
   secondDate.tm_year = year - 1900;
   
   time_t date2 = mktime(&secondDate);
   
   double days =  difftime(date2,date1) / (60 *60 * 24);
   return days;
}
