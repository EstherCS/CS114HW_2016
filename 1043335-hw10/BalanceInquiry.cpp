#include <iostream>
#include <iomanip>
using namespace std;

#include "BalanceInquiry.h"

BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account > &atmAccounts) // constructor
:accountNumber(userAccountNumber),
accounts(atmAccounts)
{

}

void BalanceInquiry::execute()
{
	// �L�X ptr ���V���b�ᤤ���l�B

	Account *ptr = getAccount(accountNumber, accounts);

	cout << "\nBalance Information : " << endl;
	cout << "- Available balance : $" << fixed << setprecision(2) << ptr->getAvailableBalance() << endl;
	cout << "- Total balance : $" << ptr->getTotalBalance() << endl;
}
// get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
Account *BalanceInquiry::getAccount(int accountNumber, vector< Account > &accounts)
{
	// �q vector �����ثe���b��
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return 0;
}