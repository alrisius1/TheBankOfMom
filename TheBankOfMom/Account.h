// Name        : Account.h
// Author      : Alyssa Risius
// Email	   : alrisius1@dmacc.edu
// Date        : 12/10/2024

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class Account
{
private:
	// variables
	std::string accountName;
	int accountPIN;
	double accountBalance;

	// auto generated
	int accountNumber;
	static int nextAccountNum;
	static int parentPIN;

public:
	// default constructor 
	Account();

	// constructor 
	Account(const std::string& name, const int& pin);

	// getters 
	std::string GetAccountName() const;
	int GetAccountNumber() const;
	double GetAccountBalance() const;
	int GetNewPin() const;

	// setters
	void SetAccountName(const std::string& name);
	void ResetAccountPin(std::vector<Account>& accounts);

	// static methods
	static void SaveAllAccounts(std::vector<Account>& accounts);
	static void LoadAccounts(std::vector<Account>& accounts);
	static Account* FindAccountByNum(std::vector<Account>& accounts, int acctNum);
	static void ResetParentPin();

	// methods
	void LogTransaction(const std::string& transType, double amount);
	void GetTransactionHistory() const;
	bool ParentValidation(const std::string& transType, const double& amount);
	bool VerifyPin() const;
	void Deposit(std::vector<Account>& accounts);
	void Withdraw(std::vector<Account>& accounts);
};

#endif

