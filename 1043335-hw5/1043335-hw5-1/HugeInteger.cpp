// Member-function definitions for class template HugeInteger

using namespace std;
#include "HugeInteger.h" // include definition of class template HugeInteger
#include "Vector.cpp" // include member-function definitions for class template Vector 

// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
: integer( n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
: integer( integerToCopy.integer )
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
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if two HugeIntegers are not equal
template< typename T >
bool HugeInteger< T >::operator!=( const HugeInteger< T > &right ) const
{
   return ( integer != right.integer );
} // end function operator!=

// convert a string of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( Vector< T > vector )
{
   // vector[ 0 ] is the most significant digit ( could be 0 )
   // vector[ vector.end() - 1 ] is the least significant digit

   unsigned int size = vector.getSize();
   Vector< T >::iterator msd = vector.begin( );
   for( ; msd != vector.end(); ++msd, --size ) // find the position of the most significant nonzero digit
      if( *msd != 0 )
         break;

   // msd points to the most significant nonzero digit in vector

   if( size == 0 ) // all digits of vector are 0
      return;

   integer.resize( size );
   Vector< T >::iterator it1 = msd;
   Vector< T >::reverse_iterator it2 = integer.rbegin();
   for( ; it1 != vector.end(); ++it1, --it2 )
      *it2 = *it1;

   // integer.begin() points to the least significant digit
   // integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   for( Vector< T >::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   Vector< T >::iterator it = integer.begin();
   Vector< T >::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.resize( integer.getSize() - 1 );
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
   if( hugeInteger.integer.getSize() == 0 )
      output << 0;
   else
   {
      Vector< T >::reverse_iterator it = hugeInteger.integer.rbegin();
      for( ; it != hugeInteger.integer.rend(); --it )
         output << *it;
   }

   return output; // enables cout << x << y;
}

template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger &right) const  // less than
{
	Vector< T >::iterator n1 = integer.rbegin();                      // 令 n1 指向 n1 最高位
	Vector< T >::iterator n2 = right.integer.rbegin();                // 令 n2 指向 n1 最高位

	if (integer.getSize() < right.integer.getSize())                  // 比較長度
		return true;
	else if (integer.getSize() == right.integer.getSize())
	{
		for (; n1 >= integer.begin(); n1--, n2--)
		{
			if (*n1 > *n2)                                            // 最高位開始比較
				return false;
			if (*n1 < *n2)
				return true;
		}
	}
	return false;
}

template< typename T >
bool HugeInteger< T >::operator>(const HugeInteger &right) const  // greater than
{
	return (right < *this);                                       // n2 < n1
}

template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger &right) const // less than or equal to
{
	if (*this < right)                                       // n1 < n2
		return true;
	else
		return *this == right;                               // n1 = n2
}

template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger &right) const // greater than or equal to
{
	return (right <= *this);                                 // n2 <= n1
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size >= op2Size) ? size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);

	Vector< T >::iterator it1 = integer.begin();
	Vector< T >::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	Vector< T >::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	Vector< T >::iterator it4 = it3;
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
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(const HugeInteger &op2) const
{
	HugeInteger< T > difference(*this);                   // 將 difference 放入 n1 的值
	HugeInteger< T > zero(1);
	HugeInteger< T > num2(op2);

	if (integer.getSize() == 0)
	{
		difference = zero;
	}

	if (num2.integer.getSize() < difference.integer.getSize())
		num2.integer.resize(difference.integer.getSize());

	Vector< T >::iterator dif = difference.integer.begin();         // difference 的指標
	Vector< T >::iterator n2 = num2.integer.begin();                // n2 的指標
	for (; n2 != num2.integer.end(); n2++, dif++)
	{
		int carry = 0;
		if (*dif < *n2)                                   // 小減大
		{
			*dif = 10 - (*n2 - *dif);
			carry++;                                      // 有借用下一位
		}
		else
			*dif -= *n2;
		if (carry)
		{
			if (*(dif + 1) > 0)
				*(dif + 1) -= carry;                          // 下一位的被減數減一
			else
				*(n2 + 1) += carry;                           // 下一位的減數加一
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

template< typename T >
// multiplication operator; HugeInteger * HugeInteger
HugeInteger< T > HugeInteger< T >::operator*(const  HugeInteger &op2) const
{
	int productSize = (integer.getSize() >= op2.integer.getSize()) ? integer.getSize() * 2 : op2.integer.getSize() * 2;

	HugeInteger< T > product(productSize);
	Vector< T >::iterator n1 = integer.begin();
	Vector< T >::iterator n2 = op2.integer.begin();
	Vector< T >::iterator productptr = product.integer.begin();

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

template< typename T >
// division operator; HugeInteger / HugeInteger
// provided that the divisor is not equal to 0
HugeInteger< T > HugeInteger< T >::operator/(const HugeInteger &op2) const
{
	int length = (integer.getSize() > op2.integer.getSize()) // 型態為 unsigned int 
		? (integer.getSize() - op2.integer.getSize()) : (op2.integer.getSize() - integer.getSize());
	HugeInteger< T > quotient(length + 1);
	HugeInteger< T > remainder(*this);
	HugeInteger< T > n2(op2);
	HugeInteger< T > zero(1);

	if (integer.getSize() - 1 == 0 || operator<(op2))                 // 被除數為 0 或是 小除大
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
			HugeInteger< T > MulTen(integer.getSize() - op2.integer.getSize());
			MulTen.integer.push_back(1);                              // ex : 差兩位 -> 100
			n2 = n2 * MulTen;
		}
		
		Vector< T >::iterator Qptr = quotient.integer.end() - 1;
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.integer.getSize() <= n2.integer.getSize() && quotient.integer.getSize() != 0)
		{
			if (remainder < n2)
			{
				n2.divideByTen();
				Qptr--;
			}
			else
			{
				*Qptr += 1;
				remainder = remainder - n2;
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

template< typename T >
// modulus operator; HugeInteger % HugeInteger
// provided that the divisor is not equal to 0
HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger &op2) const
{
	// 被除數為 0 或是 除數為 1 時, 餘數為 0
	if (integer.getSize() - 1 == 0 || *op2.integer.begin() == 1)
	{
		HugeInteger< T > zero(1);
		return zero;
	}
	else if (*this < op2)                                       // 小除大
	{
		return *this;
	}
	else
	{
		HugeInteger< T > quotient(*this / op2);                 // n1 / n2 的 商
		HugeInteger< T > remainder(quotient * op2);             // 除數 * 商
		remainder = (*this - remainder);                        // 被除數 - ( 除數 * 商 ) = 餘數
		return remainder;
	}
}

template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++() // prefix increment operator
{
	helpIncrement();
	return *this;
}

template< typename T >
HugeInteger< T >  HugeInteger< T >::operator++(int) // postfix increment operator
{
	HugeInteger< T > temp = *this;
	helpIncrement();
	return temp;
}

template< typename T >
void HugeInteger< T >::helpIncrement() // increments a HugeInteger by 1
{
	HugeInteger< T > one;
	one.integer.push_back(1);
	*this = *this + one;
	
}