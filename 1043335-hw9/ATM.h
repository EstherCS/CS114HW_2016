#ifndef ATM_H
#define ATM_H

#include "Account.h"

class ATM
{
public:
	ATM();
	void start();
private:
	int counter;

	void menu(Account &);
	void Withdraw(Account &);
	void Deposit(Account &);
};

#endif