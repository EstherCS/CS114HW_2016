// HugeInteger test program.
#include <fstream>
using namespace std;
#include "HugeInteger .cpp" // include member-function definitions for class template HugeInteger 

int enterChoice1();

template< typename T >
void testHugeIntegerOperators(HugeInteger< T > n1, HugeInteger< T > n2);

int enterChoice2();

template< typename T >
void loadTwoHugeIntegers(HugeInteger< T > &n1, HugeInteger< T > &n2);

template< typename T >
void loadOneHugeInteger(HugeInteger< T > &n1);

template< typename T >
void testAssignment(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testEqual(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testNotEqual(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testLess(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testGreater(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testLessEqual(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testGreaterEqual(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testAdd(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testSubtract(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testMultiply(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testDivide(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testModulus(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testArithmetics(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testPreincrement(HugeInteger< T > n1);

template< typename T >
void testPostincrement(HugeInteger< T > n1);

int main()
{
	HugeInteger< List< int > > n1;
	HugeInteger< List< int > > n2;
	HugeInteger< List< unsigned int > > n3;
	HugeInteger< List< unsigned int > > n4;
	HugeInteger< List< short int > > n5;
	HugeInteger< List< short int > > n6;
	HugeInteger< List< unsigned short int > > n7;
	HugeInteger< List< unsigned short int > > n8;

	int choice = enterChoice1();

	switch (choice)
	{
	case 1:
		testHugeIntegerOperators(n1, n2);
		break;
	case 2:
		testHugeIntegerOperators(n3, n4);
		break;
	case 3:
		testHugeIntegerOperators(n5, n6);
		break;
	case 4:
		testHugeIntegerOperators(n7, n8);
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
} // end main

int enterChoice1()
{
	cout << "Enter your choice\n"
		<< " 1 - test HugeInteger< List< int > >\n"
		<< " 2 - test HugeInteger< List< unsigned int > >\n"
		<< " 3 - test HugeInteger< List< short int > >\n"
		<< " 4 - test HugeInteger< List< unsigned short int > >\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 1) || (menuChoice > 4));
	cout << endl;

	return menuChoice;
} // end function enterChoice1

template< typename T >
void testHugeIntegerOperators(HugeInteger< T > n1, HugeInteger< T > n2)
{
	void(*array1[13])(HugeInteger< T >, HugeInteger< T >) =
	{ testAssignment, testEqual, testNotEqual, testLess, testGreater, testLessEqual, testGreaterEqual,
	testAdd, testSubtract, testMultiply, testDivide, testModulus, testArithmetics };
	void(*array2[15])(HugeInteger< T >) = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, testPreincrement, testPostincrement };

	int choice = enterChoice2();

	if (choice <= 12) // test binary operators
	{
		loadTwoHugeIntegers(n1, n2);
		(*array1[choice])(n1, n2); // invoke the function at location choice in array1
	}
	else // test unary operators
	{
		loadOneHugeInteger(n1);
		(*array2[choice])(n1); // invoke the function at location choice in array2
	}

	cout << endl << endl;
}

template< typename T >
void loadTwoHugeIntegers(HugeInteger< T > &n1, HugeInteger< T > &n2)
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

	char digit;
	Vector< unsigned int > intVector1, intVector2;

	while ((digit = inFile.get()) != '\n')
	if (digit != ' ')
		intVector1.push_back(digit - '0');
	// the leftmost digit (i.e., the most significant digit) will be put into intVector1[ 0 ]

	while ((digit = inFile.get()) != '\n')
	if (digit != ' ')
		intVector2.push_back(digit - '0');
	// the leftmost digit (i.e., the most significant digit) will be put into intVector2[ 0 ]

	n1.convert(intVector1);
	n2.convert(intVector2);

	inFile.close();
}

template< typename T >
void loadOneHugeInteger(HugeInteger< T > &n1)
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

	char digit;
	Vector< unsigned int > intVector;

	while ((digit = inFile.get()) != '\n')
	if (digit != ' ')
		intVector.push_back(digit - '0');
	// the leftmost digit (i.e., the most significant digit) will be put into numericString[ 0 ]

	n1.convert(intVector);

	inFile.close();
}

int enterChoice2()
{
	cout << "Enter your choice\n"
		<< " 0 - test assignment\n"
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
		<< "12 - test arithmetics\n"
		<< "13 - test prefix increment\n"
		<< "14 - test postfix increment\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 0) || (menuChoice > 14));
	cout << endl;

	return menuChoice;
} // end function enterChoice2

template< typename T >
void testAssignment(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << "n1                  : " << n1 << endl;
	cout << "n2 before assignment: " << n2 << endl;
	n2 = n1;
	cout << "n2  after assignment: " << n2;
}

template< typename T >
void testEqual(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 == n2)
		cout << n1 << " == " << n2;
	else
		cout << n1 << " != " << n2;
}

template< typename T >
void testNotEqual(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 != n2)
		cout << n1 << " != " << n2;
	else
		cout << n1 << " == " << n2;
}

template< typename T >
void testLess(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 < n2)
		cout << n1 << " < " << n2;
	else
		cout << n1 << " >= " << n2;
}

template< typename T >
void testGreater(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 > n2)
		cout << n1 << " > " << n2;
	else
		cout << n1 << " <= " << n2;
}

template< typename T >
void testLessEqual(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 <= n2)
		cout << n1 << " <= " << n2;
	else
		cout << n1 << " > " << n2;
}

template< typename T >
void testGreaterEqual(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 >= n2)
		cout << n1 << " >= " << n2;
	else
		cout << n1 << " < " << n2;
}

template< typename T >
void testAdd(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << n1 << " + " << n2 << " == " << n1 + n2;
}

template< typename T >
void testSubtract(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n1 < n2)
		cout << n1 << " - " << n2 << " == -" << n2 - n1;
	else
		cout << n1 << " - " << n2 << " == " << n1 - n2;
}

template< typename T >
void testMultiply(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << n1 << " * " << n2 << " == " << n1 * n2;
}

template< typename T >
void testDivide(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (!n2.isZero())
		cout << n1 << " / " << n2 << " == " << n1 / n2;
	else
		cout << "divide by zero!!";
}

template< typename T >
void testModulus(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (!n2.isZero())
		cout << n1 << " % " << n2 << " == " << n1 % n2;
	else
		cout << "divide by zero!!";
}

// checks whether n1 - ( n1 % n2 ) is equal to ( n1 / n2 ) * n2
template< typename T >
void testArithmetics(HugeInteger< T > n1, HugeInteger< T > n2)
{
	if (n2.isZero())
	{
		cout << "divide by zero!!";
		return;
	}

	HugeInteger< T > n3 = n1 - (n1 % n2);
	HugeInteger< T > n4 = (n1 / n2) * n2;

	cout << n1 << " - (" << n1 << " % " << n2 << ") == " << n3;
	cout << "\n\n(" << n1 << " / " << n2 << ") * " << n2 << " == " << n4;

	if (n3 == n4) // n1 - ( n1 % n2 ) == ( n1 / n2 ) * n2
		cout << "\n\nBingo! They are equal.";
	else
		cout << "\n\nGee!! They are not equal.";

}

template< typename T >
void testPreincrement(HugeInteger< T > n1)
{
	cout << "  n1: " << n1 << endl;
	cout << "++n1: " << ++n1 << endl;
	cout << "  n1: " << n1;
}

template< typename T >
void testPostincrement(HugeInteger< T > n1)
{
	cout << "  n1: " << n1 << endl;
	cout << "n1++: " << n1++ << endl;
	cout << "  n1: " << n1;
}