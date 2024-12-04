// Name        : Account.cpp
// Author      : Alyssa Risius
// Email	   : alrisius1@dmacc.edu
// Date        : 12/10/2024
// Description : This program is designed to help you efficiently manage and 
//      track your children's finances. It allows them to create accounts 
//      with secure PINs, make deposits and withdrawals, check their account 
//      balances, and view their transaction history. For added security, 
//      parental approval is required for all deposit and withdrawal 
//      transactions. 

#include <iostream>
#include "Account.h"
#include <vector>
using namespace std;


void DisplayMenu() {
    cout << "\n~The Bank of Mom~" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. View Transaction History" << endl;
    cout << "6. Reset Account PIN" << endl;
    cout << "7. Reset Parent PIN" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}
}

int GetUserAccountNumber() {
    int accountNumber;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    return accountNumber;
}

int main()
{
    std::vector<Account> accounts;
    Account::LoadAccounts(accounts);

    int choice;
    bool exit = false;

    do {
        DisplayMenu();
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Please enter a number between 1 and 8. Try again:";
            cin >> choice;
        }

        switch (choice) {
            // create account 
                // prompts user for account name and pin
                // verifies input
                // create account and add to vector 
                // displays sucess message and account details
        case 1: {
            string name;
            int pin;

            Account newAccount;

            cout << "Enter account name: ";
            cin.ignore();
            getline(cin, name);

            pin = newAccount.GetNewPin();

            newAccount = Account(name, pin);
            accounts.push_back(newAccount);

            cout << "Accout Name: " << newAccount.GetAccountName() << "\nAccount Number: " << newAccount.GetAccountNumber() << endl;
            cout << "Account created successfully!" << endl;
            break;
        }

              // deposit
                  // prompt user for number
                  // find account using pointer 
                  // if found, verify pin and complete transaction
                  // else error messages
        case 2: {

            int acctNum = GetUserAccountNumber();

            Account* acctPtr = Account::FindAccountByNum(accounts, acctNum);

            if (acctPtr != nullptr) {
                if (acctPtr->VerifyPin()) {
                    acctPtr->Deposit(accounts);
                }
                else {
                    cout << "Transaction Canceled" << endl;
                }
            }
            else {
                cout << "Error: Account was not found." << endl;
            }
            break;
        }

              // withdraw
                 // prompt user for number
                 // find account using pointer 
                 // if found, verify pin and complete transaction
                 // else error messages
        case 3: {

            int acctNum = GetUserAccountNumber();

            Account* acctPtr = Account::FindAccountByNum(accounts, acctNum);

            if (acctPtr != nullptr) {
                if (acctPtr->VerifyPin()) {
                    acctPtr->Withdraw(accounts);
                }
                else {
                    cout << "Transaction Canceled" << endl;
                }
            }
            else {
                cout << "Error: Account was not found." << endl;
            }
            break;
        }

              // check balance
                  // prompt user for number
                  // find account using pointer 
                  // if found, verify pin
                  // display account details and balance
                  // else error messages
        case 4: {

            int acctNum = GetUserAccountNumber();

            Account* acctPtr = Account::FindAccountByNum(accounts, acctNum);

            if (acctPtr != nullptr) {
                if (acctPtr->VerifyPin()) {
                    acctPtr->GetAccountBalance();
                    cout << "Account Name: " << acctPtr->GetAccountName() << "\nAccount Number: " << acctPtr->GetAccountNumber();
                    cout << "\nAccount Balance: " << fixed << setprecision(2) << acctPtr->GetAccountBalance() << endl;
                }
                else {
                    cout << "Transaction Canceled" << endl;
                }
            }
            else {
                cout << "Error: Account was not found." << endl;
            }
            break;

        }

              // transaction history
                  // prompt user for number
                  // find account using pointer 
                  // if found, verify pin and complete transaction
                  // else error messages
        case 5: {

            int acctNum = GetUserAccountNumber();

            Account* acctPtr = Account::FindAccountByNum(accounts, acctNum);

            if (acctPtr != nullptr) {
                if (acctPtr->VerifyPin()) {
                    acctPtr->GetTransactionHistory();
                }
                else {
                    cout << "Transaction Canceled" << endl;
                }
            }
            else {
                cout << "Error: Account was not found." << endl;
            }
            break;
        }

              // reset account pin
                  // prompt user for number
                  // find account using pointer 
                  // if found, reset pin
                  // else error messages
        case 6: {

            int acctNum = GetUserAccountNumber();

            Account* acctPtr = Account::FindAccountByNum(accounts, acctNum);

            // if found -> reset - else error message
            if (acctPtr != nullptr) {
                acctPtr->ResetAccountPin(accounts);
            }
            else {
                cout << "Error: Account was not found." << endl;
            }
            break;
        }

              // reset parent pin
        case 7: {
            Account::ResetParentPin();
            break;
        }

              // exit
                    // save accounts
                    // display message
                    // change exit to true
        case 8: {

            Account::SaveAllAccounts(accounts);
            cout << "Thank you. GoodBye!" << endl;
            exit = true;
            break;
        }
        }
    } while (!exit);

    return 0;
}
