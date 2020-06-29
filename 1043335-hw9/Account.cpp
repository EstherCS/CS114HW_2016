#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;

#include "Account.h"

Account::Account(string AccountNumber, string pin, double AvailableBalance, double TotalBalance) 
: accountNum(AccountNumber),
PIN(pin),
availableBalance(AvailableBalance),
totalBalance(TotalBalance)
{
}

bool Account::IdentifyAccount(string acc)
{
	if (accountNum.compare(acc) == 0)
		return true;
	else
		return false;
}

bool Account::IdentifyPIN(string pin)
{
	if (PIN.compare(pin) == 0)
		return true;
	else
		return false;
}

double Account::getavailableBalance()
{
	return availableBalance;
}

double Account::gettotalBalance()
{
	return totalBalance;
}

// 可用餘額減少
void Account::subavailableBalance(double money)
{
	if (availableBalance != 0)
		availableBalance -= money;
	else
		availableBalance = money;
}

// 總共餘額減少
void Account::subtotalBalance(double money)
{
	totalBalance -= money;
}

// 總共餘額增加
void Account::addtotalBalance(double money)
{
	totalBalance += money;
}

// 顯示餘額
void Account::showBalance()
{
	cout << "\nBalance Information : " << endl;
	cout << "- Available balance : $" << fixed << setprecision(2) << availableBalance << endl;
	cout << "- Total balance : $" << totalBalance << endl;
}
