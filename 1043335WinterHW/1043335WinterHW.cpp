// HugeInteger test program.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

void loadTwoHugeIntegers(HugeInteger &n1, HugeInteger &n2);
int enterChoice();
void testEqual(HugeInteger n1, HugeInteger n2);
void testNotEqual(HugeInteger n1, HugeInteger n2);
void testLess(HugeInteger n1, HugeInteger n2);
void testGreater(HugeInteger n1, HugeInteger n2);
void testLessEqual(HugeInteger n1, HugeInteger n2);
void testGreaterEqual(HugeInteger n1, HugeInteger n2);
void testAdd(HugeInteger n1, HugeInteger n2);
void testSubtract(HugeInteger n1, HugeInteger n2);
void testMultiply(HugeInteger n1, HugeInteger n2);
void testDivide(HugeInteger n1, HugeInteger n2);
void testModulus(HugeInteger n1, HugeInteger n2);
void testArithmetics(HugeInteger n1, HugeInteger n2);

int main()
{
	HugeInteger n1;
	HugeInteger n2;

	loadTwoHugeIntegers(n1, n2);

	void(*f[13])(HugeInteger, HugeInteger) =
	{ 0, testEqual, testNotEqual, testLess, testGreater, testLessEqual, testGreaterEqual,
	testAdd, testSubtract, testMultiply, testDivide, testModulus, testArithmetics };

	int choice = enterChoice();

	// invoke the function at location choice in the array f
	(*f[choice])(n1, n2);
	cout << endl << endl;

	system("pause");
}

void loadTwoHugeIntegers(HugeInteger &n1, HugeInteger &n2)
{
	// ifstream constructor opens the file
	ifstream inFile("hugeIntegers1.txt", ios::in);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	char numericString[HugeInteger::digits];
	inFile >> numericString;
	n1.convert(numericString);

	inFile >> numericString;
	n2.convert(numericString);

	inFile.close();
}

int enterChoice()
{
	cout << "Enter your choice\n"
		<< " 1 - test equal\n"
		<< " 2 - test notEqual\n"
		<< " 3 - test less\n"
		<< " 4 - test greater\n"
		<< " 5 - test lessEqual\n"
		<< " 6 - test greaterEqual\n"
		<< " 7 - test add\n"
		<< " 8 - test subtract\n"
		<< " 9 - test multiply\n"
		<< "10 - test divide\n"
		<< "11 - test modulus\n"
		<< "12 - test arithmetics\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 1) || (menuChoice > 12));
	cout << endl;

	return menuChoice;
}

void testEqual(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.equal(n2)) // tests for equality between n1 and n2
		cout << " == ";
	else
		cout << " != ";
	n2.output();
}

void testNotEqual(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.notEqual(n2)) // tests for inequality between n1 and n2
		cout << " != ";
	else
		cout << " == ";
	n2.output();
}

void testLess(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.less(n2)) // tests for smaller number between n1 and n2
		cout << " < ";
	else
		cout << " >= ";
	n2.output();
}

void testGreater(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.greater(n2)) // tests for greater number between n1 and n2
		cout << " > ";
	else
		cout << " <= ";
	n2.output();
}

void testLessEqual(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.lessEqual(n2)) // tests for smaller or equal number between n1 and n2
		cout << " <= ";
	else
		cout << " > ";
	n2.output();
}

void testGreaterEqual(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	if (n1.greaterEqual(n2)) // tests for greater or equal number between n1 and n2
		cout << " >= ";
	else
		cout << " < ";
	n2.output();
}

void testAdd(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	cout << " + ";
	n2.output();
	cout << " == ";
	n1.add(n2).output(); // outputs n1 + n2
}

void testSubtract(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	cout << " - ";
	n2.output();
	cout << " == ";

	if (n1.less(n2))
	{
		cout << '-';
		n2.subtract(n1).output(); // outputs n2 - n1
	}
	else
		n1.subtract(n2).output(); // outputs n1 - n2
}

void testMultiply(HugeInteger n1, HugeInteger n2)
{
	n1.output();
	cout << " * ";
	n2.output();
	cout << " == ";
	n1.multiply(n2).output(); // outputs n1 * n2
}

void testDivide(HugeInteger n1, HugeInteger n2)
{
	if (n2.isZero())
	{
		cout << "divide by zero!!";
		return;
	}

	n1.output();
	cout << " / ";
	n2.output();
	cout << " == ";
	n1.divide(n2).output(); // outputs n1 / n2
}

void testModulus(HugeInteger n1, HugeInteger n2)
{
	if (n2.isZero())
	{
		cout << "divide by zero!!";
		return;
	}

	n1.output();
	cout << " % ";
	n2.output();
	cout << " == ";
	n1.modulus(n2).output(); // outputs n1 % n2
}

// checks whether n1 - ( n1 % n2 ) is equal to ( n1 / n2 ) * n2
void testArithmetics(HugeInteger n1, HugeInteger n2)
{
	if (n2.isZero())
	{
		cout << "divide by zero!!";
		return;
	}

	HugeInteger n3 = n1.subtract(n1.modulus(n2)); // n3 = n1 - ( n1 % n2 )
	HugeInteger n4 = n1.divide(n2).multiply(n2);  // n4 = ( n1 / n2 ) * n2

	n1.output();
	cout << " - (";
	n1.output();
	cout << " % ";
	n2.output();
	cout << ") == ";
	n3.output();

	cout << "\n\n(";
	n1.output();
	cout << " / ";
	n2.output();
	cout << ") * ";
	n2.output();
	cout << " == ";
	n4.output();

	if (n3.equal(n4))
		cout << "\n\nBingo! They are equal.";
	else
		cout << "\n\nGee!! They are not equal.";
}
