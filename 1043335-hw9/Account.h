#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
public:
	Account(string, string, double, double);

	// �{�ұb���K�X
	bool IdentifyAccount(string);
	bool IdentifyPIN(string);

	// ���o�l�B
	double getavailableBalance();
	double gettotalBalance();
	
	void subavailableBalance(double);

	// �`�l�B�[��
	void subtotalBalance(double);
	void addtotalBalance(double);

	void showBalance();

private:
	string accountNum;                     // �b��
	string PIN;                            // �K�X
	double availableBalance;               // �i�ξl�B
	double totalBalance;                   // �`�@�l�B
};

#endif