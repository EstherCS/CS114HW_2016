#include <iostream>
using namespace std;

#include "Deposit.h"

Deposit::Deposit(int userAccountNumber, vector< Account > &atmAccounts)
:accountNumber(userAccountNumber),
accounts(atmAccounts)
{

}

void Deposit::execute()
{
	// �L�X�n�s�����A�ç�L�s�J ptr ���V���b��

	Account *ptr = getAccount(accountNumber, accounts);

	amount = promptForDepositAmount();

	if (amount != 0)
	{
		cout << "\nPlease insert a deposit envelope containing  $" << amount << "  in the deposit slot." << endl << endl;
		cout << "Your envelope has been received." << endl;
		cout << "NOTE : The money deposited will not be available until we verify " << endl;
		cout << "the amount of any enclosed cash, and any enclosed checks clear." << endl << endl;
		ptr->credit(amount);
	}
	else
		cout << "\nCanceling transaction..." << endl << endl;
}

Account *Deposit::getAccount(int accountNumber, vector< Account > &accounts)
{
	// �q vector �����ثe���b��
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return 0;
}

double Deposit::promptForDepositAmount() const
{
	double money;
	cout << "\nPlease enter a deposit amount in CENTS(or 0 to cancel) : ";
	cin >> money;

	if (money == 0)
		return 0;
	money /= 100;       // ���� CENT -> $

	return money;
}