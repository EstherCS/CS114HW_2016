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

// �i�ξl�B���
void Account::subavailableBalance(double money)
{
	if (availableBalance != 0)
		availableBalance -= money;
	else
		availableBalance = money;
}

// �`�@�l�B���
void Account::subtotalBalance(double money)
{
	totalBalance -= money;
}

// �`�@�l�B�W�[
void Account::addtotalBalance(double money)
{
	totalBalance += money;
}

// ��ܾl�B
void Account::showBalance()
{
	cout << "\nBalance Information : " << endl;
	cout << "- Available balance : $" << fixed << setprecision(2) << availableBalance << endl;
	cout << "- Total balance : $" << totalBalance << endl;
}
