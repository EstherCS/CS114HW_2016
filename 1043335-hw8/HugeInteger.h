//#include "list.h" // include definition of class template list 
//#include "vector.h" // include definition of class template vector 

#include <list> // include definition of class template list 
#include <vector> // include definition of class template vector
using namespace std;

// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger : public list< T >
{
   template< typename T >
   friend std::ostream &operator<<( std::ostream &, HugeInteger< T > & );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

   bool operator<( HugeInteger &right );  // less than
   bool operator>( HugeInteger &right );  // greater than
   bool operator<=( HugeInteger &right ); // less than or equal to
   bool operator>=( HugeInteger &right ); // greater than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*(  HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger &op2 );

   // convert a vector of decimal digits into a HugeInteger
   void convert( vector< unsigned int > intVector );

   bool isZero(); // return true if and only if all digits are zero

private:
   // constructor; construct a zero HugeInteger with size n
   HugeInteger( unsigned int n );

   void divideByTen(); // divides a HugeInteger by 10
}; // end class template HugeInteger

#endif


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
   : list()
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : list( n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : list( integerToCopy )
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
   list< T >::operator=( right );

   return *this; // enables x = y = z, for example
}

// function to test if one HugeInteger< T > is greater than another
template< typename T >
bool HugeInteger< T >::operator>( HugeInteger< T > &right )
{
   return ( right < *this );
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger< T > &right )
{
   return ( *this == right || *this < right );
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=( HugeInteger< T > &right )
{
   return ( !( *this < right ) );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int op1Size = size();
   unsigned int op2Size = op2.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( *this );
   sum.resize( sumSize );

   iterator it2 = op2.begin();
   iterator it3 = sum.begin();
   for( ; it2 != op2.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.begin();
   iterator it4 = it3;
   for( ++it4; it4 != sum.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.resize( sumSize - 1 );

   return sum;
} // end function operator+

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( vector< unsigned int > intVector )
{
   // intVector[ intVector.end() - 1 ] is the most significant digit ( could be 0 )
   // intVector[ 0 ] is the least significant digit

   unsigned int numDigits = intVector.size();
   vector< unsigned int >::reverse_iterator it = intVector.rbegin();
   for( ; it != intVector.rend(); ++it, --numDigits )
      if( *it != 0 )
         break;
   
   // it points to the most significant nonzero digit in intVector

   if( numDigits == 0 ) // all digits of intVector are 0
      return;

   resize( numDigits );
   vector< unsigned int >::iterator it1 = intVector.begin();
   iterator it2 = begin();
   for( ; it2 != end(); ++it1, ++it2 )
      *it2 = *it1;

   // begin() points to the least significant digit
   // end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   for( iterator it = begin(); it != end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   iterator it1 = begin();
   iterator it2 = it1;
   for( ++it2; it2 != end(); ++it1, ++it2 )
      *it1 = *it2;
   resize( size() - 1 );
}

// overloaded output operator for class HugeInteger
template< typename T >
std::ostream &operator<<( std::ostream &output, HugeInteger< T > &hugeInteger )
{
   if( hugeInteger.size() == 0 )
      output << 0;
   else
   {
      list< T >::reverse_iterator it = hugeInteger.rbegin( );
      for( ; it != hugeInteger.rend(); ++it )
         output << *it;
   }

   return output; // enables cout << x << y;
}

template< typename T >
bool HugeInteger< T >::operator<(HugeInteger< T > &right)  // less than
{
	reverse_iterator n1 = rbegin();                        // 令 n1 指向 n1 最高位
	reverse_iterator n2 = right.rbegin();                  // 令 n2 指向 n1 最高位

	if (size() < right.size())                             // 比較長度
		return true;
	else if (size() == right.size())
	{
		for (; n1 != rend(); ++n1, ++n2)                   // ++ 會呼叫 operator++
		{
			if (*n1 > *n2)                                 // 最高位開始比較
				return false;                              // * 會呼叫 operator*  ( 繼承 ListIterator 裡的 )
			if (*n1 < *n2)                                 // list 的 * 會指向 data
				return true;
		}
	}
	return false;
}

// subtraction operator; HugeInteger - HugeInteger provided that
// the minuend is greater than or equal to the subtrahend
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	HugeInteger< T > difference(*this);                   // 將 difference 放入 n1 的值
	HugeInteger< T > zero(1);
	HugeInteger< T > num2(op2);

	if (size() == 0)
	{
		difference = zero;
	}

	if (num2.size() < difference.size())
		num2.resize(difference.size());

	iterator dif = difference.begin();                    
	iterator n2 = num2.begin();                           // 新的 class 的 ptr 指向 begin() 的位置
	for (; dif != difference.end(); ++dif, ++n2)
	{
		/* 注意!! next = ++dif  dif會改變，要先給 next 再加 */
		iterator next = dif;                              // 指向正在相減的下一位
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
	reverse_iterator dif2 = difference.rbegin();
	int difsize = difference.size();
	while (*dif2 == 0 && difsize != 1)
	{
		difsize--;
		dif2++;                                           // reverse_iterator 的 ++ funtion 中會做 --
	}                                                     // 為了跟 str 裡面一樣所以這樣設計，其實可以直接繼承 ListIterator 中的
	difference.resize(difsize);
	return difference;
}

// multiplication operator; HugeInteger * HugeInteger
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T > &op2)
{
	int productSize = (size() >= op2.size()) ? size() * 2 : op2.size() * 2;

	HugeInteger< T > product(productSize);
	iterator n1 = begin();
	iterator n2 = op2.begin();
	iterator pro;
	int i = 0;
	for (; n1 != end(); ++n1, i++)
	{
		int j = 0;
		for (n2 = op2.begin(); n2 != op2.end(); ++n2, j++)
		{
			pro = product.begin();
			int k = i + j;                              // 計算 product 中哪一格要存數字
			for (int z = 0; z < k; z++)
				++pro;                                  // 將指標移到我們要的那格
			*pro += *n1 * *n2;                          // 相乘
		}
	}

	for (pro = product.begin(); pro != product.end(); ++pro)
	{
		iterator next = pro;
		if (*pro > 9)                                   // 進位
		{
			++next;
			*next += (*pro / 10);
			*pro %= 10;
		}
	}

	reverse_iterator productptr = product.rbegin();
	int prosize = product.size();
	while (*productptr == 0 && prosize != 1)            // 刪去 0
	{
		prosize--;
		productptr++;
	}
	product.resize(prosize);
	return product;
}

// division operator; HugeInteger / HugeInteger
// provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > &op2)
{
    // 型態為 unsigned 不可有負的 
	int length = (size() > op2.size()) ? (size() - op2.size()) : (op2.size() - size()); 
	HugeInteger< T > quotient(length + 1);
	HugeInteger< T > remainder(*this);
	HugeInteger< T > n2(op2);
	HugeInteger< T > zero(1);

	if (size() - 1 == 0 || operator<(op2))               // 被除數為 0 或是 小除大
	{
		return zero;
	}
	else if (*op2.begin() == 1)                          // 除數為 1
	{
		return *this;
	}
	else
	{
		if (size() > n2.size())                          // n2 要跟 n1 一樣長
		{
			HugeInteger< T > MulTen(size() - op2.size() + 1);
			*MulTen.rbegin() = 1;                        // ex : 差兩位 -> 100
			n2 = n2 * MulTen;
		}

		reverse_iterator Qptr = quotient.rbegin();       // 從最後一位
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.size() <= n2.size() && quotient.size() != 0)
		{
			if (remainder < n2)
			{
				n2.divideByTen();
				Qptr++;                                  // 實際上為 --
			}
			else
			{
				*Qptr += 1;
				remainder = remainder - n2;
			}
		}
		Qptr = quotient.rbegin();
		int qsize = quotient.size();
		while (*Qptr == 0 && qsize != 1)
		{
			qsize--;
			Qptr++;
		}
		quotient.resize(qsize);
	}
	return quotient;
}

// modulus operator; HugeInteger % HugeInteger
// provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > &op2)
{
	return *this - ((*this / op2)*op2);         // 餘數 = 被除數 - ( 商 * 除數 )
}