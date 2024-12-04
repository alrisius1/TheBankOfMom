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
    std::cout << "\n~The Bank of Mom~" << std::endl;
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Deposit Money" << std::endl;
    std::cout << "3. Withdraw Money" << std::endl;
    std::cout << "4. Check Balance" << std::endl;
    std::cout << "5. View Transaction History" << std::endl;
    std::cout << "6. Reset Account PIN" << std::endl;
    std::cout << "7. Reset Parent PIN" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int GetUserAccountNumber() {
    int accountNumber;

    std::cout << "Enter Account Number: ";
    std::cin >> accountNumber;

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
        std::cin >> choice;

        while (std::cin.fail() || choice < 1 || choice > 8) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input. Please enter a number between 1 and 8. Try again:";
            std::cin >> choice;
        }

        switch (choice) {
            // create account 
                // prompts user for account name and pin
                // verifies input
                // create account and add to vector 
                // displays sucess message and account details
        case 1: {
            std::string name;
            int pin;

            Account newAccount;

            std::cout << "Enter account name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            pin = newAccount.GetNewPin();

            newAccount = Account(name, pin);
            accounts.push_back(newAccount);

            std::cout << "Accout Name: " << newAccount.GetAccountName() << "\nAccount Number: " << newAccount.GetAccountNumber() << std::endl;
            std::cout << "Account created successfully!" << std::endl;
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
                    std::cout << "Transaction Canceled" << std::endl;
                }
            }
            else {
                std::cout << "Error: Account was not found." << std::endl;
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
                    std::cout << "Transaction Canceled" << std::endl;
                }
            }
            else {
                std::cout << "Error: Account was not found." << std::endl;
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
                    std::cout << "Account Name: " << acctPtr->GetAccountName() << "\nAccount Number: " << acctPtr->GetAccountNumber();
                    std::cout << "\nAccount Balance: " << std::fixed << std::setprecision(2) << acctPtr->GetAccountBalance() << std::endl;
                }
                else {
                    std::cout << "Transaction Canceled" << std::endl;
                }
            }
            else {
                std::cout << "Error: Account was not found." << std::endl;
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
                    std::cout << "Transaction Canceled" << std::endl;
                }
            }
            else {
                std::cout << "Error: Account was not found." << std::endl;
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
                std::cout << "Error: Account was not found." << std::endl;
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
            std::cout << "Thank you. GoodBye!" << std::endl;
            exit = true;
            break;
        }
        }
    } while (!exit);

    return 0;
}
