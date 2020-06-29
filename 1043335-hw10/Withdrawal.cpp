#include <iostream>
using namespace std;

#include "Withdrawal.h"

Withdrawal::Withdrawal(int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills)
:accountNumber(userAccountNumber),
accounts(atmAccounts),
remainingBills(atmRemainingBills)
{

}

void Withdrawal::execute()
{
	Account *ptr = getAccount(accountNumber, accounts); // ���V account ������

	bool check = false;                                 // �ˬd�O�_�����άO���X

	do
	{
		amount = displayMenuOfAmounts();
		if (amount != 0)
		{
			if (amount <= ptr->getAvailableBalance())   // �b�ᦳ���������i�H��
			{
				int num = amount / 20;                  // �p��ݭn�h�ֱi�r�� ( �����O 20 ������ )

				if (num > remainingBills)
				{
					cout << "\nATM don't have enough money." << endl;
					return;
				}
				else
				{
					remainingBills -= num;               // ATM �ѤU���r���i��
					check = true;
				}

				ptr->debit(amount);
				cout << "\nPlease take your cash from the cash dispenser." << endl;
			}
			else
			{
				cout << "\nyou don't have enough money." << endl;
			}
		}
		else
		{
			cout << "\nCanceling transaction..." << endl;
			check = true;
		}
	} while (!check);

}

Account * Withdrawal::getAccount(int accountNumber, vector< Account > &accounts)
{
	// �q vector �����ثe���b��
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	}
	return 0;
}

int Withdrawal::displayMenuOfAmounts() const
{
	int amount[5] = { 20, 40, 60, 100, 200 };
	int choice;
	do
	{
		cout << "\nWithdrawal options : " << endl;
		cout << "1 - $20" << endl;
		cout << "2 - $40" << endl;
		cout << "3 - $60" << endl;
		cout << "4 - $100" << endl;
		cout << "5 - $200" << endl;
		cout << "6 - Cancel transaction" << endl << endl;
		cout << "Choose a withdrawal option(1 - 6) : ";

		cin >> choice;
	} while (choice < 1 || choice > 6);

	double money = 0;
	switch (choice)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		money = amount[choice - 1];    // �N�n�⪺���^��
		break;
	case 6:
		return 0;
	}

	return money;
}