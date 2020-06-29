// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor
HugeInteger::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
: integer( n )
{
}

// copy constructor
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
: integer( integerToCopy.integer )
{
}

// destructor
HugeInteger::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::operator=( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if two HugeIntegers are not equal
bool HugeInteger::operator!=( const HugeInteger &right ) const
{
   return ( integer != right.integer );
} // end function operator!=

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( const HugeInteger &op2 ) const
{
   unsigned int size = integer.getSize();
   unsigned int op2Size = op2.integer.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   for( unsigned int i = 0; i < size; i++ )
      sum.integer[ i ] = integer[ i ];

   for( unsigned int i = 0; i < op2Size; i++ )
      sum.integer[ i ] += op2.integer[ i ];

   for( unsigned int i = 0; i < sumSize - 1; i++ )
      if( sum.integer[ i ] > 9 )
      {
         sum.integer[ i ] -= 10;
         sum.integer[ i + 1 ]++;
      }

   if( sum.integer[ sumSize - 1 ] == 0 )
      sum.integer.resize( sumSize - 1 );

   return sum;
} // end function operator+

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
   for( unsigned int i = 0; i < integer.getSize(); i++ )
      if( integer[ i ] != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   unsigned int size = integer.getSize( );
   if( size > 0 )
   {
      for( unsigned int i = 1; i < size; i++ )
         integer[ i - 1 ] = integer[ i ];
      integer.resize( size - 1 );
   }
}

// overloaded output operator for class HugeInteger
ostream &operator<<( ostream &output, HugeInteger &hugeInteger )
{
   unsigned int size = hugeInteger.integer.getSize();
   if( size == 0 )
      output << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         output << hugeInteger.integer[ i ];

   return output; // enables cout << x << y;
}

bool HugeInteger:: operator<(const HugeInteger &right) const  // less than
{
	if (integer.getSize() < right.integer.getSize())
		return true;
	else if (integer.getSize() == right.integer.getSize())
	{
		for (int i = integer.getSize() - 1; i >= 0; i--)
		{
			if (integer[i] < right.integer[i])               // �q����ƶ}�l���
				return true;
			if (integer[i] > right.integer[i])
				return false;
		}
	}
	return false;                                            // �۵��|�^�� false
}

bool HugeInteger::operator>(const HugeInteger &right) const  // greater than
{
	return (right < *this);                         // n2 < n1
}

bool HugeInteger::operator<=(const HugeInteger &right) const // less than or equal to
{
	if (*this < right)                                       // n1 < n2
		return true;
	else
		return *this == right;                               // n1 = n2
}

bool HugeInteger::operator>=(const HugeInteger &right) const // greater than or equal to
{
	return (right <= *this);                                 // n2 <= n1
}

HugeInteger HugeInteger::operator-(const HugeInteger &op2) const
{
	HugeInteger difference(*this);                        // �N difference ��J n1 ����
	HugeInteger n2(op2);
	HugeInteger zero(1);
	int size = difference.integer.getSize();

	for (int i = 0; i < op2.integer.getSize(); i++)
	{
		int carry = 0;
		if (difference.integer[i] < n2.integer[i])        // �p��j 
		{
			difference.integer[i] = 10 - ( n2.integer[i] - difference.integer[i] );
			carry++;                                      // ���ɥΤU�@��
		}
		else
			difference.integer[i] -= n2.integer[i];
		if (carry > 0)
		{
			if (difference.integer[i + 1] > 0)
				difference.integer[i + 1] -= carry;           // �U�@�쪺�Q��ƴ�@
			else
				n2.integer[i + 1] += carry;                   // �U�@�쪺��ƥ[�@
		}
	}

	while (difference.integer[size - 1] == 0 && size != 1)
	{
		difference.integer.resize(size - 1);              // �R�h�Ʀr�e�� 0
		size--;
	}

	return difference;
}

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*(const  HugeInteger &op2) const
{
	// ���ת��׳]�w���⭿
	int productSize = (integer.getSize() >= op2.integer.getSize()) ? integer.getSize() * 2 : op2.integer.getSize() * 2;
	
	HugeInteger product(productSize);
    // �ۭ���Ʀ��@�Ƭ� 0
	if ((integer[0] == 0 && integer.getSize() == 1) || (op2.integer[0] == 0 && op2.integer.getSize() == 1)) 
	{
		productSize = 1;
		product.integer[0] = 0;                                   // ���׬� 0
	}
	else
	{
		for (int i = 0; i < integer.getSize(); i++)
		{
			for (int j = 0; j < op2.integer.getSize(); j++)       // ��Ƭۭ� 
			{
				product.integer[i + j] += integer[i] * op2.integer[j];
			}
		}
		for (int i = 0; i < productSize; i++)                     // �i��
		{
			while (product.integer[i] > 9)
			{
				product.integer[i] -= 10;
				product.integer[i + 1]++;
			}
		}
	}
	while (product.integer[productSize - 1] == 0 && productSize != 1)
		productSize--;                                            // �R�h�Ʀr�e�� 0
	product.integer.resize(productSize);                          // ���]�j�p

	return product;
}

// division operator; HugeInteger / HugeInteger
HugeInteger HugeInteger::operator/(const HugeInteger &op2) const
{
	int length = (integer.getSize() > op2.integer.getSize()) // ���A�� unsigned int 
		? (integer.getSize() - op2.integer.getSize()) : (op2.integer.getSize() - integer.getSize());
	HugeInteger quotient(length + 1);
	HugeInteger remainder(*this);
	HugeInteger n2(op2);
	HugeInteger zero(1);

	if (integer.getSize() - 1 == 0 || operator<(op2))                // �Q���Ƭ� 0 �άO �p���j
	{
		return zero;
	}
	else if (*op2.integer.begin() == 1)                               // ���Ƭ� 1
	{
		return *this;
	}
	else
	{
		if (integer.getSize() > n2.integer.getSize())                 // n2 �n�� n1 �@�˪�
		{
			HugeInteger MulTen(integer.getSize() - op2.integer.getSize());
			MulTen.integer.push_back(1);                              // ex : �t��� -> 100
			n2 = n2 * MulTen;
		}
		int quotientSize = quotient.integer.getSize();
		// �Q���ƪ��פp�󰣼ƪ��סB���װ}�C���פ��� 0
		while (op2.integer.getSize() <= n2.integer.getSize() && quotient.integer.getSize() != 0)
		{
			if (remainder < n2)
			{
				n2.divideByTen();
				quotientSize--;
			}
			else
			{
				quotient.integer[quotientSize - 1]++;
				remainder = remainder - n2;
			}
		}
		quotientSize = length + 1;
		while (quotient.integer[quotientSize - 1] == 0 && quotientSize != 1)
			quotientSize--;
		quotient.integer.resize(quotientSize);
	}
	return quotient;
}

// modulus operator; HugeInteger % HugeInteger
HugeInteger HugeInteger::operator%(const HugeInteger &op2) const
{
	// �Q���Ƭ� 0 �άO ���Ƭ� 1 ��, �l�Ƭ� 0
	if (integer.getSize() - 1 == 0 || *op2.integer.begin() == 1)
	{
		HugeInteger zero(1);
		return zero;
	}
	else if (*this < op2)                                  // �p���j
	{
		return *this;
	}
	else
	{
		HugeInteger quotient(*this / op2);                 // n1 / n2 �� ��
		HugeInteger remainder(quotient * op2);             // ���� * ��
		remainder =(*this - remainder);                    // �Q���� - ( ���� * �� ) = �l��
		return remainder;
	}
}

// prefix increment operator
HugeInteger &HugeInteger::operator++()
{
	helpIncrement();
	return *this;
}

// postfix increment operator
HugeInteger HugeInteger::operator++(int)
{
	HugeInteger temp = *this;
	helpIncrement();
	return temp;
}

void HugeInteger::helpIncrement()          // increments a HugeInteger by 1
{
	HugeInteger one(1);
	one.integer[0] = 1;
	*this = *this + one;
}