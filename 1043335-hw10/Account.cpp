#include "Account.h"

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance)
:accountNumber(theAccountNumber),
pin(thePIN),
availableBalance(theAvailableBalance),
totalBalance(theTotalBalance)
{

}

bool Account::validatePIN(int userPIN) const // �ˬd PIN �O�_���T
{
	if (userPIN == pin)
		return true;
	else
		false;
}

double Account::getAvailableBalance() const  // ���o availableBalance
{
	return availableBalance;
}

double Account::getTotalBalance() const      // ���o totalBalance
{
	return totalBalance;
}

void Account::credit(double amount)          // �N�s�J�����[�� totalBalance
{
	totalBalance += amount;
}

void Account::debit(double amount)           // �N��X�����q availableBalance �M totalBalance ����h
{
	availableBalance -= amount;
	totalBalance -= amount;
}

int Account::getAccountNumber() const        // ���o accountNumber
{
	return accountNumber;
}