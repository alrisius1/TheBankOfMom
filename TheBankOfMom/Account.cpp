// Name        : Account.cpp
// Author      : Alyssa Risius
// Email	   : alrisius1@dmacc.edu
// Date        : 12/10/2024

#include "Account.h"
#include "TransactionTime.h"

// initialize account number and parent pin
int Account::nextAccountNum = 1000;
int Account::parentPIN = 1738;

// default constructor
Account::Account() {};

// constructor
Account::Account(const string& name, const int& pin) : accountName(name), accountPIN(pin), accountBalance(0.0)
{
	accountNumber = nextAccountNum++;
}

// getters
string Account::GetAccountName() const {
	return accountName;
}

int Account::GetAccountNumber() const {
	return accountNumber;
}

double Account::GetAccountBalance() const {
	return accountBalance;
}

// prompt user for new pin
// validate input
// return newPIN
int Account::GetNewPin() const {
	int newPIN;

	cout << "Please enter new PIN: ";
	cin >> newPIN;

	while (cin.fail() || newPIN < 1000 || newPIN > 9999) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: PIN must be a 4-digit number. Try again: ";
		cin >> newPIN;
	}
	return newPIN;
}

// setters
void Account::SetAccountName(const string& name) {
	accountName = name;
}

// call VerifyPIN to verify
// if valid, call GetNewPin 
// set new PIN
// log transaction and save updates
void Account::ResetAccountPin(vector<Account>& accounts) {
	const string TRANSTYPE = "Reset PIN";
	const double AMOUNT = 0.00;
	int newPIN;
	bool verified;

	cout << "Reset Account PIN" << endl;

	if (VerifyPin()) {
		accountPIN = GetNewPin();
		cout << "PIN successfully reset!" << endl;
		LogTransaction(TRANSTYPE, AMOUNT);
		SaveAllAccounts(accounts);
	}
}

// static methods

// writes each account to a text file
	// open and save each account details to file and close 
	// else, error message
void Account::SaveAllAccounts(vector<Account>& accounts) {
	ofstream outputFS;
	outputFS.open("accounts.txt", ios::trunc);

	if (outputFS.is_open()) {
		for (const auto& acct : accounts) {
			outputFS << acct.GetAccountName() << "," << acct.GetAccountNumber() << "," << acct.accountPIN << "," << fixed << setprecision(2) << acct.GetAccountBalance() << endl;
		}
		outputFS.close();
	}
	else {
		cout << "Error: Could not open accounts.txt" << endl;
	}
}

// reads saved accounts from accounts text file
	// opens accounts.txt and seperates by comma
	// creates accounts and adds to vector
void Account::LoadAccounts(vector<Account>& accounts) {
	ifstream acctFS;
	acctFS.open("accounts.txt");

	if (acctFS.is_open()) {
		string acct;

		while (getline(acctFS, acct)) {
			stringstream ss(acct);
			string name;
			int acctNum;
			int pin;
			double balance;

			if (getline(ss, name, ',') && ss >> acctNum && ss.ignore(1)
				&& ss >> pin && ss.ignore(1) && ss >> balance) {
				Account newAcct(name, pin);
				newAcct.accountNumber = acctNum;
				newAcct.accountBalance = balance;

				accounts.push_back(newAcct);
			}
			else {
				cout << "Error: Skipping invalid account entry: " << acct << endl;
			}
		}
		acctFS.close();
	}
	else {
		cout << "Error: Could not load accounts.txt" << endl;
	}
}

// find account by account number
Account* Account::FindAccountByNum(vector<Account>& accounts, int acctNum) {
	for (size_t i = 0; i < accounts.size(); ++i) {
		if (accounts[i].GetAccountNumber() == acctNum) {
			return &accounts[i];
		}
	}
	return nullptr;
}

// reset parent pin
	// prompts user for old pin
	// if cannot validate within 3 attempts - back to main 
	// if valid, create new PIN - 4 digits
	// update parent pin
void Account::ResetParentPin() {
	const int MAX_ATTEMPTS = 3;
	int attempts = 0;
	int oldPIN;
	int newPIN;

	cout << "Reset Parent PIN:" << endl;

	while (attempts < MAX_ATTEMPTS) {
		cout << "Enter current Parent PIN: ";
		cin >> oldPIN;

		if (oldPIN == parentPIN) {
			break;
		}

		attempts++;
		if (attempts == MAX_ATTEMPTS) {
			cout << "Error: Could not verify Parent PIN. Reset failed." << endl;
			return;
		}
		else {
			cout << "Error: Incorrect PIN. Try again." << endl;
		}
	}

	cout << "Enter new Parent PIN: ";
	cin >> newPIN;

	while (cin.fail() || newPIN < 1000 || newPIN > 9999) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error: PIN must be a 4-digit number. Try again: ";
		cin >> newPIN;
	}

	parentPIN = newPIN;
	cout << "Parent PIN reset successfully!" << endl;
}

// saves transaction details
	// creates transactions.txt file and writes each transaction to file
void Account::LogTransaction(const string& transType, double amount) {
	ofstream outputFS;
	outputFS.open("transactions.txt", ios::app);

	if (outputFS.is_open()) {
		TransactionTime transTime;
		transTime.SetCurrentTime();

		outputFS << accountNumber << "," << transTime.ToString() << "," << transType << "," << fixed << setprecision(2) << amount << "," << accountBalance << endl;
		outputFS.close();
	}
	else {
		cout << "Error: Unable to open transactions.txt." << endl;
	}
}

// reads transaction history and displays
void Account::GetTransactionHistory() const {
	ifstream inputFS;
	inputFS.open("transactions.txt");

	if (inputFS.is_open()) {
		string line;
		bool found = false;

		cout << string(115, '=') << endl;
		cout << "Transaction History for Account #" << accountNumber << ":" << endl;

		while (getline(inputFS, line)) {
			stringstream ss(line);
			int loggedAcctNum;
			string dateTime;
			string transType;
			double amount;
			double balance;

			if (ss >> loggedAcctNum && loggedAcctNum == accountNumber) {
				ss.ignore(1);
				getline(ss, dateTime, ',');
				getline(ss, transType, ',');
				ss >> amount, ',';
				ss.ignore(1);
				ss >> balance;

				string date = dateTime.substr(0, 10);
				string time = dateTime.substr(11);

				cout << "Date: " << date;
				cout << " Time: " << time;
				cout << "   Transaction Type: " << setw(10) << transType;
				cout << "   Transaction Amount: $" << setw(8) << fixed << setprecision(2) << amount;
				cout << "   New Balance: $" << setw(8) << fixed << setprecision(2) << balance << endl;
				found = true;
			}
		}

		if (!found) {
			cout << "No transactions found for this account." << endl;
		}
		cout << string(115, '=') << endl;
		inputFS.close();
	}
	else {
		cout << "Error: Unable to open transactions.txt." << endl;
	}
}

// parent verification
	// called to verify deposits and withdraws
	// prompt parent to enter parent PIN to approve or -1 to deny
	// 3 attempts 
	// validates input 
	// returns true if approved and false if denied
bool Account::ParentValidation(const string& transType, const double& amount) {
	const int MAX_ATTEMPTS = 3;
	const int DENY = -1;

	int attempts = 0;
	int inputPIN;

	while (attempts < MAX_ATTEMPTS) {
		cout << "Please enter Parent PIN to approve the " << transType << " of $" << fixed << setprecision(2) << amount << " or '-1' to deny: ";
		cin >> inputPIN;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Input must be numeric. Try again. " << endl;
			continue;
		}

		if (inputPIN == parentPIN) {
			cout << transType << " Approved by parent." << endl;
			return true;
		}
		else if (inputPIN == DENY) {
			cout << transType << " Denied by parent." << endl;
			return false;
		}

		attempts++;

		if (attempts == MAX_ATTEMPTS) {
			cout << "Error: Could not verify. Accessed Denied. " << endl;
			return false;
		}
		else {
			cout << "Error: Incorrect Pin. Try again. " << endl;
			return false;
		}
	}
}

// verify pin
	// prompt user for PIN
	// PIN validation
	// only 3 attempts
	// returns true if verified
bool Account::VerifyPin() const {
	const int MAX_ATTEMPTS = 3;
	int attempts = 0;
	int pin;

	while (attempts < MAX_ATTEMPTS) {
		cout << "Please enter PIN: ";
		cin >> pin;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Cannot use letters or symbols. Please enter a 4-digit PIN. " << endl;
			continue;
		}

		if (pin == accountPIN) {
			return true;
		}

		attempts++;

		if (attempts == MAX_ATTEMPTS) {
			cout << "Error: Could not verify. Try again later. " << endl;
			return false;
		}
		else {
			cout << "Error: Incorrect Pin. Try again. " << endl;;
		}
	}
	return false;
}

// deposit money
	// prompt user for desposit amount
	// validate input
	// obtain parent approval
	// if approved - add amount to balance
	// save account balance and log transaction
void Account::Deposit(vector<Account>& accounts) {
	const double MIN_DEPOSIT = 0.01;
	const string TRANSTYPE = "Deposit";
	const int QUIT = -1;
	double amount;

	cout << "Enter -1 to return to main. " << endl;

	cout << "Please enter deposit amount: $";
	cin >> amount;

	while (cin.fail() || amount < MIN_DEPOSIT) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (amount == QUIT) {
			cout << "Deposit Ended." << endl;
			return;
		}

		cout << "Error: Deposit amount must be at least $0.01. Try again: $";
		cin >> amount;
	}

	if (!ParentValidation(TRANSTYPE, amount)) {
		return;
	}

	accountBalance += amount;
	cout << "Deposited $" << fixed << setprecision(2) << amount << " successfully!\nNew Balance $" << GetAccountBalance() << endl;

	LogTransaction(TRANSTYPE, amount);
	SaveAllAccounts(accounts);
}

// withdraw money
	// prompt user for withdraw amt
	// validate input
	// checks current balance
	// prompts for parent approval 
	// if approved - subtract amount from balance
	// save account balance and log transaction
void Account::Withdraw(vector<Account>& accounts) {
	const double MIN_WITHDRAW = 0.00;
	const string TRANSTYPE = "Withdraw";
	const int QUIT = -1;
	double amount;

	cout << "Enter -1 to return to main. " << endl;

	cout << "Please enter withdraw amount: $";
	cin >> amount;
	while (cin.fail() || amount <= MIN_WITHDRAW) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (amount == QUIT) {
			cout << "Withdraw Ended." << endl;
			return;
		}

		cout << "Error: Withdraw must be more than $0.00. Try again: $";
		cin >> amount;
	}

	while (amount > accountBalance) {
		cout << "Insufficient funds. Try again: $";
		cin >> amount;
	}

	if (!ParentValidation(TRANSTYPE, amount)) {
		return;
	}

	accountBalance -= amount;
	cout << "Withdrew $" << fixed << setprecision(2) << amount << " successfully!\nNew Balance $" << GetAccountBalance() << endl;

	LogTransaction(TRANSTYPE, amount);
	SaveAllAccounts(accounts);
}