// AccountDatabase.h
// AccountDatabase class definition.
#ifndef ACCOUNT_DATABASE_H
#define ACCOUNT_DATABASE_H

#include <fstream>
#include <vector>
#include "Account.h" // Account class definition

#include <iostream>
using namespace std;

class AccountDatabase
{
public:
	AccountDatabase(); // constructor loads accounts from Accounts.dat
	~AccountDatabase(); // destructor saves accounts into Accounts.dat

	// called in LogIn::run() to determine whether email address and password match those of an Account
	bool authenticateUser(string, string);

	bool ExistMail(string &MAIL); // 是否已經有存在的 EMAIL

	void pushBack(Account &newAccount); // add newAccount at the end of accounts

	Account *GetNowAccount(string nowAccount);

private:
	vector< Account > accounts; // vector of the customer's accounts

	// return a pointer to the first Account object in accounts, containing specified email address
	Account * getAccount(string);

	void loadAccountDetails();
	void saveAccountDetails();
}; // end class AccountDatabase



AccountDatabase::AccountDatabase() // constructor loads accounts from Accounts.dat
{
	loadAccountDetails();
}

AccountDatabase::~AccountDatabase() // destructor saves accounts into Accounts.dat
{
	saveAccountDetails();
}

// called in LogIn::run() to determine whether email address and password match those of an Account
bool AccountDatabase::authenticateUser(string acc, string pin)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (acc == accounts[i].getEmail())
		{
			if (accounts[i].validatePassword(pin))
				return true;
			else
				return false;
		}
	}
}

bool AccountDatabase::ExistMail(string &MAIL)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (MAIL == accounts[i].getEmail())
			return true;
	}
	return false;
}

void AccountDatabase::pushBack(Account &newAccount)
{
	accounts.push_back(newAccount);
}

Account *AccountDatabase::GetNowAccount(string nowAccount) 
{
	return getAccount(nowAccount);
}

// return a pointer to the first Account object in accounts, containing specified email address
Account *AccountDatabase::getAccount(string acc)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getEmail() == acc)
			return &accounts[i];
	}
	return 0;
}

void AccountDatabase::loadAccountDetails()
{
	ifstream inFile("Accounts.dat", ios::binary);

	if (!inFile)
	{
		cerr << "Error" << endl;
		system("pause");
		exit(1);

	}
	else
	{
		Account temp;
		while (!inFile.eof())
		{
			inFile.read(reinterpret_cast<char *>(&temp), sizeof(Account));
			if (temp.getEmail() != "")
				accounts.push_back(temp);
		}
		inFile.close();                                                      // 關閉檔案
	}
}

void AccountDatabase::saveAccountDetails()
{
	ofstream outFile("Accounts.dat", ios::out | ios::app | ios::binary);

	for (int i = 0; i < accounts.size(); i++)
	{
		outFile.write(reinterpret_cast<char *>(&accounts[i]), sizeof Account);
	}
	outFile.close();
}
#endif // ACCOUNT_DATABASE_H