#include <iostream>
using namespace std;

#include "Account.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "Withdrawal.h"

enum Option { ViewMyBalance = 1, WithdrawCash, DepositFunds, Exit };

void menu(Account &account);

int billNum = 500;               // 每一天 ATM 中有 500 張 $20
vector< Account > accounts;      // 帳號

int main()
{

	// 帳號一設定
	Account a1(12345, 54321, 1000.00, 1200.00);

	// 帳號二設定
	Account a2(98765, 56789, 200.00, 200.00);

	accounts.push_back(a1);      // 將帳號放入 vector
	accounts.push_back(a2);

	while (true)
	{
		bool checkAcc = false;   // 檢查帳號密碼是否符合 
		int acc;
		int pin;

		cout << "\nWelcome!" << endl << endl;
		cout << "Please enter your account number: ";
		cin >> acc;
		cout << "\nEnter your PIN: ";
		cin >> pin;

		if (a1.getAccountNumber() == acc && a1.validatePIN(pin))       // 檢查帳密是否符合
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
			bool EXIT = false;      // 是否跳出
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
				case ViewMyBalance:             // 查看餘額
				{
												 BalanceInquiry balance(acc, accounts);
												 balance.execute();
												 break;
				}
				case WithdrawCash:               // 提錢
				{
												  Withdrawal withdrawal(acc, accounts, billNum);
												  withdrawal.execute();
												  break;
				}
				case DepositFunds:               // 存錢
				{
												  Deposit deposit(acc, accounts);
												  deposit.execute();
												  break;
				}
				case Exit:                       // 跳出
					EXIT = true;
					cout << "\nExiting the system..." << endl;
					cout << "Thank you! Goodbye!" << endl;
					break;
				}
			}
		}
	}
}