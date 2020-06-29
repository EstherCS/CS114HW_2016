#include <iostream>
using namespace std;

#include "Account.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "Withdrawal.h"

enum Option { ViewMyBalance = 1, WithdrawCash, DepositFunds, Exit };

void menu(Account &account);

int billNum = 500;               // �C�@�� ATM ���� 500 �i $20
vector< Account > accounts;      // �b��

int main()
{

	// �b���@�]�w
	Account a1(12345, 54321, 1000.00, 1200.00);

	// �b���G�]�w
	Account a2(98765, 56789, 200.00, 200.00);

	accounts.push_back(a1);      // �N�b����J vector
	accounts.push_back(a2);

	while (true)
	{
		bool checkAcc = false;   // �ˬd�b���K�X�O�_�ŦX 
		int acc;
		int pin;

		cout << "\nWelcome!" << endl << endl;
		cout << "Please enter your account number: ";
		cin >> acc;
		cout << "\nEnter your PIN: ";
		cin >> pin;

		if (a1.getAccountNumber() == acc && a1.validatePIN(pin))       // �ˬd�b�K�O�_�ŦX
		{
			checkAcc = true;
		}
		else if (a2.getAccountNumber() == acc && a2.validatePIN(pin))
		{
			checkAcc = true;
		}
		else
		{
			cout << "\nerror number or PIN, please try again." << endl;
		}
		cout << endl;

		if (checkAcc)
		{
			bool EXIT = false;      // �O�_���X
			while (!EXIT)
			{
				int choice;
				do
				{
					cout << "\nMain menu :" << endl;
					cout << "1 - View my balance" << endl;
					cout << "2 - Withdraw cash" << endl;
					cout << "3 - Deposit funds" << endl;
					cout << "4 - Exit" << endl;
					cin >> choice;
				} while (choice > 4 || choice < 1);

				switch (choice)
				{
				case ViewMyBalance:             // �d�ݾl�B
				{
												 BalanceInquiry balance(acc, accounts);
												 balance.execute();
												 break;
				}
				case WithdrawCash:               // ����
				{
												  Withdrawal withdrawal(acc, accounts, billNum);
												  withdrawal.execute();
												  break;
				}
				case DepositFunds:               // �s��
				{
												  Deposit deposit(acc, accounts);
												  deposit.execute();
												  break;
				}
				case Exit:                       // ���X
					EXIT = true;
					cout << "\nExiting the system..." << endl;
					cout << "Thank you! Goodbye!" << endl;
					break;
				}
			}
		}
	}
}