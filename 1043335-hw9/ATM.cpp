#include <iostream>
#include <string>
using namespace std;

#include "Account.h"
#include "ATM.h"

enum Option { ViewMyBalance = 1, WithdrawCash, DepositFunds, Exit };

ATM::ATM()
:counter(500)
{
}


void ATM::start()
{
	// �b���@�]�w
	Account a1("12345", "54321", 1000.00, 1200.00);

	// �b���G�]�w
	Account a2("98765", "56789", 200.00, 200.00);

	while (true)
	{
		char acc[5];
		char pin[5];
		cout << "\nWelcome!" << endl << endl;
		cout << "Please enter your account number: ";
		cin >> acc;
		cout << "\nEnter your PIN: ";
		cin >> pin;
		if (a1.IdentifyAccount(acc) && a1.IdentifyPIN(pin))       // �ˬd�b�K�O�_�ŦX
		{
			menu(a1);
		}
		else if (a2.IdentifyAccount(acc) && a2.IdentifyPIN(pin))
		{
			menu(a2);
		}
		else
		{
			cout << "\nerror number or PIN, please try again." << endl;
		}
		cout << endl;
	}

}

void ATM::menu(Account &account)
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
		case ViewMyBalance :          // �d�ݾl�B

			account.showBalance();
			break;

		case WithdrawCash:            // ����

			Withdraw(account);
			break;

		case DepositFunds:            // �s��

			Deposit(account);
			break;

		case Exit:                    // ���X

			EXIT = true;
			cout << "\nExiting the system..." << endl;
			cout << "Thank you! Goodbye!" << endl;
			break;
		}
	}
}

void ATM::Withdraw(Account &account)
{
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
		money = 20;
		break;
	case 2:
		money = 40;
		break;
	case 3:
		money = 60;
		break;
	case 4:
		money = 100;
		break;
	case 5:
		money = 200;
		break;
	case 6:
		return;
	}
	int num = money / 20;   // �p��ݭn�h�ֱi�r�� ( �����O 20 ������ )
	if (num > counter)
	{
		cout << "\nATM don't have enough money." << endl;
		return;
	}
	else
		counter -= num;     // ATM �ѤU���r���i��

	if ((account.getavailableBalance()) < money)
		cout << "\nyou don't have enough money." << endl;
	else
	{
		account.subavailableBalance(money);
		account.subtotalBalance(money);
		cout << "\nPlease take your cash from the cash dispenser." << endl;
	}
}

void ATM::Deposit(Account &account)
{
	double money;
	cout << "\nPlease enter a deposit amount in CENTS(or 0 to cancel) : ";
	cin >> money;

	if (money == 0)
		return;
	money /= 100;                     // ���� CENT -> $

	account.addtotalBalance(money);   // �[�b�`�@�l�B

	cout << "\nPlease insert a deposit envelope containing  $" << money << "  in the deposit slot." << endl << endl;
	cout << "Your envelope has been received." << endl;
	cout << "NOTE : The money deposited will not be available until we verify " << endl;
	cout << "the amount of any enclosed cash, and any enclosed checks clear." << endl << endl;
}