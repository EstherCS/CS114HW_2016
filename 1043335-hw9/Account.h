#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
public:
	Account(string, string, double, double);

	// 認證帳號密碼
	bool IdentifyAccount(string);
	bool IdentifyPIN(string);

	// 取得餘額
	double getavailableBalance();
	double gettotalBalance();
	
	void subavailableBalance(double);

	// 總餘額加減
	void subtotalBalance(double);
	void addtotalBalance(double);

	void showBalance();

private:
	string accountNum;                     // 帳號
	string PIN;                            // 密碼
	double availableBalance;               // 可用餘額
	double totalBalance;                   // 總共餘額
};

#endif