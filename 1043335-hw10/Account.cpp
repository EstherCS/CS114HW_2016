#include "Account.h"

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance)
:accountNumber(theAccountNumber),
pin(thePIN),
availableBalance(theAvailableBalance),
totalBalance(theTotalBalance)
{

}

bool Account::validatePIN(int userPIN) const // 檢查 PIN 是否正確
{
	if (userPIN == pin)
		return true;
	else
		false;
}

double Account::getAvailableBalance() const  // 取得 availableBalance
{
	return availableBalance;
}

double Account::getTotalBalance() const      // 取得 totalBalance
{
	return totalBalance;
}

void Account::credit(double amount)          // 將存入的錢加到 totalBalance
{
	totalBalance += amount;
}

void Account::debit(double amount)           // 將領出的錢從 availableBalance 和 totalBalance 中減去
{
	availableBalance -= amount;
	totalBalance -= amount;
}

int Account::getAccountNumber() const        // 取得 accountNumber
{
	return accountNumber;
}