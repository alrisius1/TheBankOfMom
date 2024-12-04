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
	string accountName;
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
	Account(const string& name, const int& pin);

	// getters 
	string GetAccountName() const;
	int GetAccountNumber() const;
	double GetAccountBalance() const;
	int GetNewPin() const;

	// setters
	void SetAccountName(const string& name);
	void ResetAccountPin(vector<Account>& accounts);

	// static methods
	static void SaveAllAccounts(vector<Account>& accounts);
	static void LoadAccounts(vector<Account>& accounts);
	static Account* FindAccountByNum(vector<Account>& accounts, int acctNum);
	static void ResetParentPin();

	// methods
	void LogTransaction(const string& transType, double amount);
	void GetTransactionHistory() const;
	bool ParentValidation(const string& transType, const double& amount);
	bool VerifyPin() const;
	void Deposit(vector<Account>& accounts);
	void Withdraw(vector<Account>& accounts);
};

#endif

