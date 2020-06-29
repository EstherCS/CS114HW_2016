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
	// 印出 ptr 指向的帳戶中的餘額

	Account *ptr = getAccount(accountNumber, accounts);

	cout << "\nBalance Information : " << endl;
	cout << "- Available balance : $" << fixed << setprecision(2) << ptr->getAvailableBalance() << endl;
	cout << "- Total balance : $" << ptr->getTotalBalance() << endl;
}
// get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
Account *BalanceInquiry::getAccount(int accountNumber, vector< Account > &accounts)
{
	// 從 vector 中找到目前的帳號
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return 0;
}