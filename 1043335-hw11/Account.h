// Account.h
// Account class definition.
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const char foods[15][24] = { "", "小籠包（12入）", "菜肉蒸餃（8入）", "蝦肉蒸餃（8入）", "鮮魚蒸餃（8入）",
"香菇素餃（8入）", "蝦仁燒賣（12入）", "鮮肉大包（5入）", "菜肉大包（5入）",
"豆沙大包（5入）", "芝麻大包（5入）", "芋泥大包（5入）", "香菇素包（5入）",
"鮮肉粽子（5入）", "豆沙粽子（5入）" };

class Account
{
public:
	Account(string = "", string = "", string = "", string = "", string = ""); // constructor sets attributes

	bool validatePassword(string userPassword) const; // determines whether a user-specified password
	// matches password in Account

	// accessor functions for email
	void setEmail(string);
	string getEmail() const;

	// accessor functions for password
	void setPassword(string);
	string getPassword() const;

	// accessor functions for name
	void setName(string);
	string getName() const;

	// accessor functions for address
	void setAddress(string);
	string getAddress() const;

	// accessor functions for phone
	void setPhone(string);
	string getPhone() const;

	// accessor functions for cart
	void setCart(int *);
	int * getCart();

	void modifyCart(int code, int amount); // cart[ code ] is modified to amount

	void displayAccountDetails() const; // display email, name, address and phone of Account

	void displayCart() const; // Code, Item and Quantity of each foods in the shopping cart
private:
	char email[40]; // used as the account number
	char password[20];
	char name[8];
	char address[80];
	char phone[12];
	int cart[15]; // cart[ i ] is the quantity of food #i in the shopping cart
}; // end class Account

#endif // ACCOUNT_H

Account::Account(string EMAIL, string PIN, string NAME, string ADD, string PHONE)
{
	setEmail(EMAIL);
	setPassword(PIN);
	setName(NAME);
	setAddress(ADD);
	setPhone(PHONE);
	int setZero[15] = { 0 };
	setCart(setZero);
}

bool Account::validatePassword(string userPassword) const // determines whether a user-specified password
// matches password in Account
{
	cout << userPassword << endl;
	cout << password << endl;
	cout << name << endl;
	if (userPassword.compare(password) == 0)
		return true;
	else
		return false;
}

// accessor functions for email
void Account::setEmail(string EMAIL)
{
	int i;
	for (i = 0; i < EMAIL.size(); i++)
		email[i] = EMAIL[i];
	email[i] = '\0';
}

string Account::getEmail() const
{
	return email;
}

// accessor functions for password
void Account::setPassword(string PIN)
{
	int i;
	for (i = 0; i < PIN.size(); i++)
		password[i] = PIN[i];
	password[i] = '\0';
}

string Account::getPassword() const
{
	return password;
}

// accessor functions for name
void Account::setName(string NAME)
{
	int i;
	for (i = 0; i < NAME.size(); i++)
		name[i] = NAME[i];
	name[i] = '\0';
}

string Account::getName() const
{
	return name;
}

// accessor functions for address
void Account::setAddress(string ADD)
{
	int i;
	for (i = 0; i < ADD.size(); i++)
		address[i] = ADD[i];
	address[i] = '\0';
}

string Account::getAddress() const
{
	return address;
}

// accessor functions for phone
void Account::setPhone(string PHONE)
{
	int i;
	for (i = 0; i < PHONE.size(); i++)
		phone[i] = PHONE[i];
	phone[i] = '\0';
}

string Account::getPhone() const
{
	return phone;
}

// accessor functions for cart
void Account::setCart(int *CART)
{
	for (int i = 0; i < 15; i++)
		cart[i] = CART[i];
}

int * Account::getCart()
{
	return cart;
}

void Account::modifyCart(int code, int amount) // cart[ code ] is modified to amount
{
	cart[code] += amount;
}

void Account::displayAccountDetails() const   // display email, name, address and phone of Account
{
	cout << "Full Name:  " << name << endl;
	cout << "Shopping Address:  " << address << endl;
	cout << "Phone Number:  " << phone << endl;
	cout << "Bank account: 合作金庫 0062013162077139" << endl << endl;
}

void Account::displayCart() const             // Code, Item and Quantity of each foods in the shopping cart
{
	cout << endl;
	cout << "Your shopping cart:" << endl;
	cout << "Code                    Item   Quantity\n";
	for (int i = 1; i < 15; i++)
	{
		cout << setw(4) << setfill(' ') << i << setw(24) << setfill(' ') << foods[i] << setw(11) << cart[i] << endl;
	}
}