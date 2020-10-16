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
      //user chooses between these choices if not gets a invalid input cout and then enters again
      cout<<"[1] Open Account \n" << "[2] Login \n" << "[3] Exit \n";
      cin >> userEnter;
      string accountNumber;
      bool checkAccNum;
      switch (userEnter){
         // if the user enters one the system will start adding a new account 
         case 1:{
            //gets the new account number 
            string newAccountNum;
            cin.ignore();
            cout<<"Enter new account number: ";
            getline(cin, newAccountNum);
            
            //This is to check if the account number inputed has letters in it, making it invalid     
            checkAccNum = checkIfNumber(newAccountNum);
 
            //checks to see if the number entered if it is valid is also not been used before.
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
               
               //if the number is not in use then user has to enter interest for checking account,saving account, and the anuual service charge for the savings account. if any are 
               //invalid the system will not allow it and return to main menu
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
                           string sBalance;
                           cout<<"Enter balance for both acounts"; 
                           getline(cin,sBalance);
                           if(checkIfNumber(sBalance))
                           {
                           //creates the new accounts and adds them to the vectors 
                              CheckingAccount newCheckAcc(newAccountNum,stod(sBalance),stod(sCheckInt),stod(sCheckAnnCharge));
                              SavingsAccount newSavAcc(newAccountNum,stod(sBalance),stod(sSaveInt),0);
                              newSavAcc.checkInterestRate();
                              checkingAccounts.push_back(newCheckAcc);
                              savingsAccounts.push_back(newSavAcc);
                           }
                           else
                           {
                              cout << "Invalid input" << endl;
                           }
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
            //runs i user wants to login to old user 
            cout << "Please enter your account number: ";
            cin >> accountNumber;


            int accountLocation = 0, doesExist = 0;
            //checks to see if the account exists or not
            for(int i = 0; i < savingsAccounts.size(); i++){
               string accountNumberNoLetter = savingsAccounts[i].getAccountNumber().substr(1, savingsAccounts[i].getAccountNumber().length());
               if (accountNumber == accountNumberNoLetter){
                  accountLocation = i;
                  doesExist = 1;
               }
            }

            int selection = 0;
            if (doesExist == 1){
               //runs if the account exsists
               while(selection !=3){
                  //runs until the user enters one of the choices and if is invalid the user will get invalid input 
                  cout << "Welcome\nPlease select an option\n[1] Checking\n[2] Savings\n[3] Return to Menu\n";
                  cin >> selection;
                  int option = 0;
                  switch (selection){
                     //runs if checking is chosen
                     case 1:{
                        while(option != 4){
                           //checks to see what operation the user want to do will thorw invalid input if is not specified;
                           cout << "Checking\n[1] Balance\n[2] Deposit\n[3] Withdraw\n[4] Return to Menu\n";
                           cin >> option;
                           cin.ignore();
                           switch (option){
                              //returns the balance 
                              case 1:{
                                 cout << "$" << checkingAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                              //deposits money while also checking if it a valid amount and if it can be deposited
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
                                 //withdraws money while checking if amount is valid and if operation can be completed 
                                 cout << "enter amount to withdraw \n";
                                 bool checkWth;
                                 string amountWth;
                                 getline(cin,amountWth);
                                 checkWth = checkIfNumber(amountWth);
                                 if(checkWth == true)
                                 {
                                    double amount = stod(amountWth);
                                    bool value = checkingAccounts[accountLocation].withdraw(amount);
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
                                 //returns to checking/ savings/ return screen
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
                        //runs if savings is chosen
                        while(option != 4){
                           cout << "Savings\n[1] Balance\n[2] Deposit\n[3] Withdraw\n[4] Return to Menu\n";
                           cin >> option;
                           cin.ignore();
                           switch (option){
                              // returns balance 
                              case 1:{
                                 cout << "$" << savingsAccounts[accountLocation].getBalance() << "\n";
                                 break;
                              }
                              case 2:{
                                 //deposits money while checking if amount is valid an also if the deposit was successful
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
                                 //withdraws money from the acount checks if amount is valid and also returns if the withdraw  is successful 
                                 cout << "Enter amount to withdraw \n";
                                 bool checkWth;
                                 string amountWth;
                                 getline(cin,amountWth);
                                 checkWth = checkIfNumber(amountWth);
                                 if(checkWth == true)
                                 {
                                    double amount = stod(amountWth);
                                    bool value = savingsAccounts[accountLocation].withdraw(amount);
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
                                 //returns to checking/saving screen
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
                        //returns to main screen 
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
            // exits the program 
            cout << "Goodbye!\n"; 
            break;
         }
         default:{
            cout << "Enter a valid number: \n";
         }

      }
      
   }while(userEnter != 3);
   
   //writes all accounts present to accounts.txt file 
   writeToFile(checkingAccounts, savingsAccounts);
   
   
   return 0;
}

void writeToFile( vector<CheckingAccount> &checkingAccounts, vector<SavingsAccount> &savingsAccounts)
{
   //function that writes out to accounts .txt to store account information
   ofstream outFile;
   
   //opens file and prints all valuable information to the accouts.txt File 
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
   //reads from the file and pulls out the checking account
   vector<CheckingAccount> temp;
   ifstream inFile;
   string text;
   
   inFile.open("accounts.txt");

   while(inFile)
   {
      getline(inFile,text);
      //checks to see if the start of a string in file contains c if so it is start of checking file 
      if(text.find('C') == 0)
      {
         //retrives all valuable data 
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
         
         //creats a new cheching account that contain old information
         CheckingAccount chekAcc(accountNumber, balance, interestRate, annualServiceCharge);
         //retrives date of new account object
         string newDate = chekAcc.getDateCreated();
         //function used to calculate days between the old date stored in file and the new date the was just created in new file 
         double days = howManyDays(date,newDate);
         
         //for amount of of days will calculate interest
         for(int i = 0; i < days; i++)
         {
            chekAcc.calcInt();
         }
         
         //finds amount of years
         days = days / 365;
         
         //withdraws yearly charge from acocount by amount of years 
         for(int i = 0; i < days; i++)
         {
            chekAcc.yearlyCharge();
         }
         
         //add object to checking account
         temp.push_back(chekAcc);
         
      }
   }
   
   inFile.close();
   return temp;
}

vector<SavingsAccount> readFromFileSavings()
{
   //reads from the accounts.txt file and retives the savings accounts and puts into vector which is returned by function
   vector<SavingsAccount> temp;
   ifstream inFile;
   string text;
   
   inFile.open("accounts.txt");
   while(inFile)
   {
      getline(inFile,text);
      //if string contains S at start is is a savings account and will then collect all infromation
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
         
         //creates a new accont with all relevent information
         SavingsAccount saveAcc(accountNumber, balance, interestRate, 0 ,status);
         
         //gets date created by new object 
         string newDate = saveAcc.getDateCreated();
         
         //calculates days between the two dates
         double days = howManyDays(date,newDate);
         //gets interest for amount of days 
         for(int i =0; i < days ; i++)
         {
            saveAcc.calcInt();
         }
         
         //sets accont status 
         saveAcc.setAccountActiveStatus();
         
         //pushed account back of the vector 
         temp.push_back(saveAcc);
         
      }
   }
   
   inFile.close();
    return temp;
}

bool checkIfNumber(string number) 
{
   //checks to see if the number is double or not 
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
   //assigns day month year from the string into own variable 
   int mon = stoi(dateOne.substr(0, dateOne.find(":")));
   dateOne = dateOne.substr(dateOne.find(":") +1 , dateOne.length());
   int day = stoi(dateOne.substr(0, dateOne.find(":")));
   dateOne = dateOne.substr(dateOne.find(":") +1 , dateOne.length());
   int year = stoi(dateOne.substr(0, dateOne.find(":")));
   
   
   //creates tm struct and assigns values of year day and mon into respective poitions 
   tm firstDate = tm();
   firstDate.tm_mday = day;
   firstDate.tm_mon = mon - 1;
   firstDate.tm_year = year - 1900;
   
   //makes time_t object from mktime at tm object firstDate
   time_t date1 = mktime(&firstDate);
   
   //assigns day month year from the second sring int own variable s
   mon = stoi(dateTwo.substr(0, dateTwo.find(":")));
   dateTwo = dateTwo.substr(dateTwo.find(":") +1 , dateTwo.length());
   day = stoi(dateTwo.substr(0, dateTwo.find(":")));
   dateTwo = dateTwo.substr(dateTwo.find(":") +1 , dateTwo.length());
   year = stoi(dateTwo.substr(0, dateTwo.find(":")));
   
   
   
   //creates a tm struct that contain the day mon and year of each
   tm secondDate = tm();
   secondDate.tm_mday = day;
   secondDate.tm_mon = mon - 1;
   secondDate.tm_year = year - 1900;
   
   
   //creeates time _t object from mktime tm second dat
   time_t date2 = mktime(&secondDate);
   
   //find the amount of days between both dates and returns it 
   double days =  difftime(date2,date1) / (60 *60 * 24);
   return days;
}
