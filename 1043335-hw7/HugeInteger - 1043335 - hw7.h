#include "List - 1043335 - hw7.h" // include definition of class template list 
#include "Vector - 1043335 - hw7.h" // include definition of class template vector 

//#include <list> // include definition of class template list 
//#include <vector> // include definition of class template vector
using namespace std;

// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
	template< typename T >
	friend std::ostream &operator<<(std::ostream &, HugeInteger< T > &);
public:
	HugeInteger(); // default constructor; construct a HugeInteger with size 0

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger &integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=(const HugeInteger &right); // assignment operator

	bool operator==(HugeInteger &right); // less than or equal to
	bool operator!=(HugeInteger &right); // greater than or equal to
	bool operator<(HugeInteger &right);  // less than
	bool operator>(HugeInteger &right);  // greater than
	bool operator<=(HugeInteger &right); // less than or equal to
	bool operator>=(HugeInteger &right); // greater than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger &op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger &op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger &op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger &op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger &op2);

	// convert a vector of decimal digits into a HugeInteger
	void convert(vector< unsigned int > intVector);

	bool isZero(); // return true if and only if all digits are zero

private:
	T integer;

	// constructor; construct a zero HugeInteger with size n
	HugeInteger(unsigned int n);

	void divideByTen(); // divides a HugeInteger by 10
}; // end class template HugeInteger

#endif


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
: integer(n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T > &integerToCopy)
: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=(const HugeInteger< T > &right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger< T > &right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if two HugeIntegers are not equal
template< typename T >
bool HugeInteger< T >::operator!=(HugeInteger< T > &right)
{
	return (integer != right.integer);
} // end function operator!=

template< typename T >
bool HugeInteger< T >::operator<(HugeInteger< T > &right)
{
	// 用 reverse_iterator 讓 vector 、 list 都適用 ( 這是 class，非指標 )
	T::reverse_iterator n1 = integer.rbegin();                    // 令 n1 指向 n1 最高位
	T::reverse_iterator n2 = right.integer.rbegin();              // 令 n2 指向 n1 最高位

	if (integer.size() < right.integer.size())                    // 比較長度
		return true;
	else if (integer.size() == right.integer.size())
	{
		for (; n1 != integer.rend(); ++n1, ++n2)                  // ++ 會呼叫 operator++
		{
			if (*n1 > *n2)                                        // 最高位開始比較
				return false;                                     // * 會呼叫 operator* 
			if (*n1 < *n2)                                        // list 的 * 會指向 data
				return true;
		}
	}
	return false;
}

// function to test if one HugeInteger< T > is greater than another
template< typename T >
bool HugeInteger< T >::operator>(HugeInteger< T > &right)
{
	return (right < *this);
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T > &right)
{
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(HugeInteger< T > &right)
{
	return (!(*this < right));
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger< T > &op2)
{
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum(*this);
	sum.integer.resize(sumSize);

	T::iterator it2 = op2.integer.begin();
	T::iterator it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	T::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(vector< unsigned int > intVector)
{
	// intVector[ intVector.end() - 1 ] is the most significant digit ( could be 0 )
	// intVector[ 0 ] is the least significant digit

	unsigned int numDigits = intVector.size();
	vector< unsigned int >::reverse_iterator it = intVector.rbegin();
	for (; it != intVector.rend(); ++it, --numDigits)
	if (*it != 0)
		break;

	// it points to the most significant nonzero digit in intVector

	if (numDigits == 0) // all digits of intVector are 0
		return;

	integer.resize(numDigits);
	vector< unsigned int >::iterator it1 = intVector.begin();
	T::iterator it2 = integer.begin();
	for (; it2 != integer.end(); ++it1, ++it2)
		*it2 = *it1;

	// integer.begin() points to the least significant digit
	// integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	for (T::iterator it = integer.begin(); it != integer.end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	T::iterator it1 = integer.begin();
	T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;
	integer.resize(integer.size() - 1);
}

// overloaded output operator for class HugeInteger
template< typename T >
std::ostream &operator<<(std::ostream &output, HugeInteger< T > &hugeInteger)
{
	if (hugeInteger.integer.size() == 0)
		output << 0;
	else
	{
		T::reverse_iterator it = hugeInteger.integer.rbegin();
		for (; it != hugeInteger.integer.rend(); ++it)
			output << *it;
	}

	return output; // enables cout << x << y;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	HugeInteger< T > difference(*this);                   // 將 difference 放入 n1 的值
	HugeInteger< T > zero(1);
	HugeInteger< T > num2(op2);

	if (integer.size() == 0)
	{
		difference = zero;
	}

	if (num2.integer.size() < difference.integer.size())
		num2.integer.resize(difference.integer.size());

	T::iterator dif = difference.integer.begin();         // 宣告一個 iterator class ( 想像成指標 ) 
	T::iterator n2 = num2.integer.begin();                // 新的 class 的 ptr 指向 begin() 的位置
	for (; dif != difference.integer.end(); ++dif, ++n2)
	{
		/* 注意!! next = ++dif  dif會改變，要先給 next 再加 */
		T::iterator next = dif;                           // 指向正在相減的下一位
		int carry = 0;                                    // 判斷是否有借用下一位
		if (*dif < *n2)
		{
			*dif += 10;
			carry++;
		}
		*dif = *dif - *n2;
		if (carry)                                        // 有借用下一位
		{
			++next;                                       // 要用到時才真正指向下一位
			while (*next == 0)                            // 找到非 0 為止
			{
				*next += 9;
				++next;
			}
			*next -= 1;                                   // 非 0 數字減一，因為借用給前面小減大的地方
		}
	}
	T::reverse_iterator dif2 = difference.integer.rbegin();
	int difsize = difference.integer.size();
	while (*dif2 == 0 && difsize != 1)
	{
		difsize--;
		dif2++;                                           // reverse_iterator 的 ++ funtion 中會做 --
	}
	difference.integer.resize(difsize);
	return difference;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T > &op2)
{
	int productSize = (integer.size() >= op2.integer.size()) ? integer.size() * 2 : op2.integer.size() * 2;

	HugeInteger< T > product(productSize);
	T::iterator n1 = integer.begin();
	T::iterator n2 = op2.integer.begin();
	T::iterator pro;
	int i = 0;
	for (; n1 != integer.end(); ++n1, i++)
	{
		int j = 0;
		for (n2 = op2.integer.begin(); n2 != op2.integer.end(); ++n2, j++)
		{
			pro = product.integer.begin();
			int k = i + j;                              // 計算 product 中哪一格要存數字
			for (int z = 0; z < k; z++)
				++pro;                                  // 將指標移到我們要的那格
			*pro += *n1 * *n2;                          // 相乘
		}
	}

	for (pro = product.integer.begin(); pro != product.integer.end(); ++pro)
	{
		T::iterator next = pro;
		if (*pro > 9)                                   // 進位
		{
			++next;
			*next += (*pro / 10);
			*pro %= 10;
		}
	}

	T::reverse_iterator productptr = product.integer.rbegin();
	int prosize = product.integer.size();
	while (*productptr == 0 && prosize != 1)            // 刪去 0
	{
		prosize--;
		productptr++;
	}
	product.integer.resize(prosize);
	return product;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > &op2)
{
	int length = (integer.size() > op2.integer.size())           // 型態為 unsigned 不可有負的 
		? (integer.size() - op2.integer.size()) : (op2.integer.size() - integer.size());
	HugeInteger< T > quotient(length + 1);
	HugeInteger< T > remainder(*this);
	HugeInteger< T > n2(op2);
	HugeInteger< T > zero(1);

	if (integer.size() - 1 == 0 || operator<(op2))               // 被除數為 0 或是 小除大
	{
		return zero;
	}
	else if (*op2.integer.begin() == 1)                          // 除數為 1
	{
		return *this;
	}
	else
	{
		if (integer.size() > n2.integer.size())                  // n2 要跟 n1 一樣長
		{
			HugeInteger< T > MulTen(integer.size() - op2.integer.size() + 1);
			*MulTen.integer.rbegin() = 1;                        // ex : 差兩位 -> 100
			n2 = n2 * MulTen;
		}

		T::reverse_iterator Qptr = quotient.integer.rbegin();    // 從最後一位
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.integer.size() <= n2.integer.size() && quotient.integer.size() != 0)
		{
			if (remainder < n2)
			{
				n2.divideByTen();
				Qptr++;                                           // 實際上為 --
			}
			else
			{
				*Qptr += 1;
				remainder = remainder - n2;
			}
		}
		Qptr = quotient.integer.rbegin();
		int qsize = quotient.integer.size();
		while (*Qptr == 0 && qsize != 1)
		{
			qsize--;
			Qptr++;
		}
		quotient.integer.resize(qsize);
	}
	return quotient;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > &op2)
{
	return *this - ((*this / op2)*op2);         // 餘數 = 被除數 - ( 商 * 除數 )
}