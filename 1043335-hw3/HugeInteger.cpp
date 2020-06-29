// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
: integer( n )
{
} // end HugeInteger constructor

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
: integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{
   return ( integer.equal( right.integer ) );
} // end function equal

// function that tests if two HugeIntegers are not equal
bool HugeInteger::notEqual( const HugeInteger &right ) const
{
   return ( integer.notEqual( right.integer ) );
} // end function notEqual

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( Vector vector )
{
   // vector[ 0 ] is the most significant digit ( could be 0 )
   // vector[ vector.end() - 1 ] is the least significant digit

   Vector::iterator msd = vector.begin();
   for( ; msd != vector.end(); ++msd ) // find the position of the most significant nonzero digit
      if( *msd != 0 )
         break;

   // msd points to the most significant nonzero digit in vector

   if( msd == vector.end() ) // all digits of vector are 0
      return;

   integer.resize( vector.end() - msd );
   Vector::iterator it1 = msd;
   Vector::reverse_iterator it2 = integer.rbegin();
   for( ; it1 != vector.end(); ++it1, --it2 )
      *it2 = *it1;

   // integer.begin() points to the least significant digit
   // integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
   for( Vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   Vector::iterator it = integer.begin();
   Vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.resize( integer.getSize() - 1 );
}

// overloaded output operator
void HugeInteger::output()
{
   if( integer.getSize() == 0 )
      cout << 0;
   else
   {
      Vector::reverse_iterator it = integer.rbegin();
      for( ; it != integer.rend(); --it )
         cout << *it;
   }
} // end function output

bool HugeInteger::less(const HugeInteger &right) const           // less than  n1 < n2
{
	Vector::iterator n1 = integer.rbegin();                      // 令 n1 指向 n1 最高位
	Vector::iterator n2 = right.integer.rbegin();                // 令 n2 指向 n1 最高位

	if (integer.getSize() < right.integer.getSize())             // 比較長度
		return true;
	else if (integer.getSize() == right.integer.getSize())
	{
		for (; n1 >= integer.begin(); n1--, n2--)
		{
			if (*n1 > *n2)                                       // 最高位開始比較
				return false;
			if (*n1 < *n2)
				return true;
		}
	}
	return false;
}

bool HugeInteger::greater(const HugeInteger &right) const        // greater than  n1 > n2
{
	return (right.less(*this));                                  // n2 < n1
}

bool HugeInteger::lessEqual(const HugeInteger &right) const      // less than or equal to  n1 <= n2
{
	if (less(right))                                             // n1 < n2
		return true;
	else
		return equal(right);                                     // n1 = n2
}

bool HugeInteger::greaterEqual(const HugeInteger &right) const   // greater than or equal to   n1 >= n2
{
	return (right.lessEqual(*this));                             // n2 <= n1
}

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(const HugeInteger &op2) const
{
	unsigned int sumSize = (integer.getSize() >= op2.integer.getSize()) ? integer.getSize() + 1 : op2.integer.getSize() + 1;

	HugeInteger sum(sumSize);

	Vector::iterator it1 = integer.begin();
	Vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	Vector::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	Vector::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
}

// subtraction operator; HugeInteger - HugeInteger provided that
// the minuend is greater than or equal to the subtrahend
HugeInteger HugeInteger::subtract(const HugeInteger &op2) const
{
	HugeInteger difference(*this);                        // 將 difference 放入 n1 的值
    HugeInteger zero(1);
	if (integer.getSize() == 0)
	{
		difference.assign(zero);
	}

	Vector::iterator dif = difference.integer.begin();    // difference 的指標
	Vector::iterator n2 = op2.integer.begin();            // n2 的指標

	for (; n2 != op2.integer.end(); n2++, dif++)
		*dif -= *n2;                                      // 相減

	dif = difference.integer.begin();
	for (; dif != difference.integer.rbegin(); dif++)
	{
		if (*dif < 0)                                     // 進位
		{
			*dif += 10;
			*(dif + 1) -= 1;
		}
	}

	dif = difference.integer.rbegin();
	while (*dif == 0 && difference.integer.getSize() != 1)
	{
		difference.integer.resize(difference.integer.getSize() - 1);
		dif = difference.integer.rbegin();
	}
	return difference;
}

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply(const  HugeInteger &op2) const
{
	int productSize = (integer.getSize() >= op2.integer.getSize()) ? integer.getSize() * 2 : op2.integer.getSize() * 2;

	HugeInteger product(productSize);
	Vector::iterator n1 = integer.begin();
	Vector::iterator n2 = op2.integer.begin();
	Vector::iterator productptr = product.integer.begin();

	for (; n1 != integer.end(); n1++)
	{
		for (n2 = op2.integer.begin(); n2 != op2.integer.end(); n2++)
		{
			productptr[(n1 - integer.begin()) + (n2 - op2.integer.begin())] += *n1 * *n2;  // 相乘
		}
	}

	for (productptr = product.integer.begin(); productptr != product.integer.end(); productptr++)
	{
		while (*productptr > 9)                                                            // 進位
		{
			*productptr -= 10;
			*(productptr + 1) += 1;
		}
	}

	productptr = product.integer.rbegin();
	while (*productptr == 0 && product.integer.getSize() != 1)                             // 刪去 0
	{
		product.integer.resize(product.integer.getSize() - 1);
		productptr = product.integer.rbegin();
	}
	return product;
}

// division operator; HugeInteger / HugeInteger
HugeInteger HugeInteger::divide(const HugeInteger &op2) const
{
	int length = (integer.getSize() > op2.integer.getSize()) // 型態為 unsigned int 
		? (integer.getSize() - op2.integer.getSize()) : (op2.integer.getSize() - integer.getSize());
	HugeInteger quotient(length + 1);
	HugeInteger remainder(*this);
	HugeInteger n2(op2);
	HugeInteger zero(1);

	if (integer.getSize() - 1 == 0 || less(op2))                      // 被除數為 0 或是 小除大
	{
		return zero;
	}
	else if (*op2.integer.begin() == 1)                               // 除數為 1
	{
		return *this;
	}
	else
	{
		if (integer.getSize() > n2.integer.getSize())                 // n2 要跟 n1 一樣長
		{
			HugeInteger MulTen(integer.getSize() - op2.integer.getSize());
			MulTen.integer.push_back(1);                              // ex : 差兩位 -> 100
			n2.assign(n2.multiply(MulTen));                           
		}
		//cout << n2.integer.getSize();
		Vector::iterator Qptr = quotient.integer.end() - 1;
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.integer.getSize() <= n2.integer.getSize() && quotient.integer.getSize() != 0)
		{
			if (remainder.less(n2))
			{
				n2.divideByTen();
				Qptr--;
			}
			else
			{
				*Qptr += 1;
				remainder.assign(remainder.subtract(n2));
			}
		}
		Qptr = quotient.integer.rbegin();
		while (*Qptr == 0 && quotient.integer.getSize() != 1)
		{
			quotient.integer.resize(quotient.integer.getSize() - 1);
			Qptr = quotient.integer.rbegin();
		}
	}
	return quotient;
}

// modulus operator; HugeInteger % HugeInteger
HugeInteger HugeInteger::modulus(const HugeInteger &op2) const
{
	// 被除數為 0 或是 除數為 1 時, 餘數為 0
	if (integer.getSize() - 1 == 0 || *op2.integer.begin() == 1)
	{
		HugeInteger zero(1);
		return zero;
	}
	else if (less(op2))                                   // 小除大
	{
		return *this;
	}
	else
	{
		HugeInteger quotient(divide(op2));                // n1 / n2 的 商
		HugeInteger remainder(quotient.multiply(op2));    // 除數 * 商
		remainder.assign(subtract(remainder));            // 被除數 - ( 除數 * 商 ) = 餘數
		return remainder;
	}
}