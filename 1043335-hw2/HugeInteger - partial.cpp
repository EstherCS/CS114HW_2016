// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor
HugeInteger::HugeInteger()
: size(0),
ptr(new int[0])
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
: size(n),
ptr(new int[n]())
{
}

// destructor
HugeInteger::~HugeInteger()
{
	delete[] ptr;
}

HugeInteger::HugeInteger(const HugeInteger &integerToCopy) // copy constructor
{
	size = integerToCopy.size;
	ptr = new int[size];

	for (int i = 0; i < size; i++)
		ptr[i] = integerToCopy.ptr[i];
}

void HugeInteger::resize(unsigned int n)  // resize
{
	iterator former = begin();
	iterator newptr = new  int[n];

	for (int i = 0; i<n; i++, former++) {
		newptr[i] = *former;
	}
	delete[] ptr;
	ptr = newptr;
	size = n;
	/*int *temp;

	temp = new int[n];

	if (size == 0)
	{
		iterator first = begin();
		for (int i = 0; i < n; i++, first++)
			temp[i] = *first;
		ptr = temp;
		size = n;
	}
	else
	{
		iterator first = begin();
		if (n > size)
		{
			for (int i = 0; i < size; i++, first++)
				temp[i] = *first;
		}
		else
		{
			for (int i = 0; i < n; i++, first++)
				temp[i] = *first;
		}
		size = n;
		ptr = temp;
	}*/
}

const HugeInteger &HugeInteger::assign(const HugeInteger &right)
{
	resize(right.size);
	for (int i = 0; right.ptr + i != right.end(); i++) {
		*(ptr + i) = *(right.ptr + i);
	}
	/*size = right.size;
	int *temp = new int[size];

	for (int i = 0; i < size; i++)
		temp[i] = right.ptr[i];

	if (ptr != NULL)
	{
		delete [] ptr;
	}
	ptr = temp;*/

	return *this;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert(vector< int > intVector)
{
	// intVector[ 0 ] is the most significant digit ( could be 0 )
	// intVector[ intVector.end() - 1 ] is the least significant digit

	iterator end = &intVector[0] + intVector.size();
	iterator msd = &intVector[0];
	for (; msd != end; ++msd) // find the position of the most significant nonzero digit
	if (*msd != 0)
		break;

	// msd points to the most significant nonzero digit in intVector

	if (msd == end) // all digits of intVector are 0
		return;

	resize(end - msd);
	iterator it1 = msd;
	reverse_iterator it2 = rbegin();
	for (; it2 != rend(); ++it1, --it2)
		*it2 = *it1;

	// begin() points to the least significant digit
	// end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
	for (iterator it = begin(); it != end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	iterator it = begin();
	iterator it2 = it;
	for (++it2; it2 != end(); ++it, ++it2)
		*it = *it2;
	resize(size - 1);
}

// overloaded output operator
void HugeInteger::output() const
{
	if (size == 0)
		cout << 0;
	else
	{
		reverse_iterator it = rbegin();
		for (; it != rend(); --it)
			cout << *it;
	}
} // end function output

int* HugeInteger::begin() const
{
	return ptr;
}

int* HugeInteger::end() const
{
	return ptr + size;
}

int* HugeInteger::rbegin() const
{
	return ptr + size - 1;
}

int* HugeInteger::rend() const
{
	return ptr - 1;
}

bool  HugeInteger::equal(const HugeInteger &right) const // n1 = n2
{
	iterator it1 = begin();                 // n1 材计
	iterator it2 = right.begin();           // n2 材计

	if (size != right.size && size != 0)
		return false;
	else
	{
		for (; it1 != end(); it1++, it2++)  // 耞琌程计
		{
			if (*it1 != *it2)               // Τぃ玥肚 false 
				return false;
		}
		return true;
	}
}

bool  HugeInteger::notEqual(const HugeInteger &right) const // greater than or equal to
{
	return !equal(right);
	/*iterator it1 = begin();                 // n1 材计
	iterator it2 = right.begin();           // n2 材计
	if (size != right.size)
		return true;
	else
	{
		for (; it1 != end(); it1++, it2++)  // 耞琌程计
		{
			if (*it1 != *it2)               // Τぃ玥肚 false 
				return true;
		}
		return false;
	}*/
}

bool  HugeInteger::less(const HugeInteger &right) const  // less than
{
	iterator it1 = end() - 1;             // n1 程计 
	iterator it2 = right.end() - 1;       // n2 程计
	if (size < right.size)
		return true;
	else if (size == right.size)
	{
		for (; it1 >= begin(); it1--, it2--)
		{
			if (*it1 < *it2)             // 眖蔼计秨﹍ゑ癸
				return true;
			if (*it1 > *it2)
				return false;
		}
	}
	return false;                        // 单穦肚 false
}

bool  HugeInteger::greater(const HugeInteger &right) const  // greater than
{
	return (right.less(*this));                                  // n2 < n1
	/*iterator it1 = end() - 1;            // n1 程计
	iterator it2 = right.end() - 1;      // n2 程计
	if (size > right.size)
		return true;
	else if (size == right.size)
	{
		for (; it1 >= begin(); it1--, it2--)
		{
			if (*it1 > *it2)             // 眖蔼计秨﹍ゑ癸
				return true;
			if (*it1 < *it2)
				return false;
		}
	}
	return false;                        // 单穦肚 false*/
}

bool  HugeInteger::lessEqual(const HugeInteger &right) const // less than or equal to
{
	if (less(right))                                             // n1 < n2
		return true;
	else
		return equal(right);                                     // n1 = n2
	/*iterator it1 = end() - 1;            // n1 程计
	iterator it2 = right.end() - 1;      // n2 程计
	if (size > right.size)
		return false;
	else if (size == right.size)
	{
		for (; it1 >= begin(); it1--, it2--)
		{
			if (*it1 < *it2)             // 眖蔼计秨﹍ゑ癸
				return true;
			if (*it1 > *it2)
				return false;
		}
	}
	return true;                         // 单穦肚 true*/
}

bool  HugeInteger::greaterEqual(const HugeInteger &right) const // greater than or equal to
{
	return (right.lessEqual(*this));                             // n2 <= n1
	/*iterator it1 = end() - 1;            // n1 程计
	iterator it2 = right.end() - 1;      // n2 程计
	if (size < right.size)
		return false;
	else if (size == right.size)
	{
		for (; it1 >= begin(); it1--, it2--)
		{
			if (*it1 < *it2)             // 眖蔼计秨﹍ゑ癸
				return false;
			if (*it1 > *it2)
				return true;
		}
	}
	return true;                         // 单穦肚 true*/
}

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(const HugeInteger &op2) const
{
	unsigned int sumSize = (size >= op2.size) ? size + 1 : op2.size + 1;

	HugeInteger sum(sumSize);

	iterator it1 = begin();
	iterator it3 = sum.begin();
	for (; it1 != end(); ++it1, ++it3)
		*it3 = *it1;

	iterator it2 = op2.begin();
	for (it3 = sum.begin(); it2 != op2.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.begin();
	iterator it4 = it3;
	for (++it4; it4 != sum.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}

	if (*it3 == 0)
		sum.resize(sumSize - 1);

	return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger provided that
// the minuend is greater than or equal to the subtrahend
HugeInteger HugeInteger::subtract(const HugeInteger &op2) const
{
	HugeInteger difference(*this);                        // 盢 difference  n1 
	HugeInteger zero(1);
	if (size == 0)
	{
		difference.assign(zero);
	}

	iterator dif = difference.begin();    // difference 夹
	iterator n2 = op2.begin();            // n2 夹

	for (; n2 != op2.end(); n2++, dif++)
		*dif -= *n2;                                      // 搭

	dif = difference.begin();
	for (; dif != difference.rbegin(); dif++)
	{
		if (*dif < 0)                                     // 秈
		{
			*dif += 10;
			*(dif + 1) -= 1;
		}
	}

	dif = difference.rbegin();
	while (*dif == 0 && difference.size != 1)
	{
		difference.resize(difference.size - 1);
		dif = difference.rbegin();
	}
	return difference;
	/*int *n1 = new int[size];
	int *n2 = new int[size];
	iterator it1 = begin();                        // n1 材计
	iterator it2 = op2.begin();                    // n2 材计

	for (int i = 0; i < size; i++)        // n1 n2 ﹍て
	{
		n1[i] = 0;
		n2[i] = 0;
	}

	for (int i = 0; it1 != end(); i++, it1++)      // n1  n1 皚
		n1[i] = *it1;

	for (int i = 0; it2 != op2.end(); i++, it2++)  // n2  n2 皚
		n2[i] = *it2;

	for (int i = 0; i < size; i++)                 // ㄢ计搭 n1 皚
		n1[i] -= n2[i];
	for (int i = 0; i < size; i++)                 // 秈
	{
		if (n1[i] < 0)
		{
			n1[i] += 10;
			n1[i + 1]--;
		}
	}

	int differenceSize = size;           // 砞﹚ difference 
	HugeInteger difference(differenceSize);
	iterator it3 = difference.begin();            // difference 材

	for (int i = 0; i < size; i++)                // n1 copy to it3 
		it3[i] = n1[i];
	it3 = difference.end() - 1;
	while (*it3 == 0 && differenceSize != 1)
	{
		difference.resize(differenceSize - 1);
		differenceSize--;
		it3 = difference.end() - 1;
	}
	return difference;*/
}

// multiplication operator; HugeInteger * HugeInteger
HugeInteger  HugeInteger::multiply(const  HugeInteger &op2) const
{
	int productSize = (size >= op2.size) ? size * 2 : op2.size * 2;

	HugeInteger product(productSize);
	iterator n1 = begin();
	iterator n2 = op2.begin();
	iterator productptr = product.begin();

	for (; n1 != end(); n1++)
	{
		for (n2 = op2.begin(); n2 != op2.end(); n2++)
		{
			productptr[(n1 - begin()) + (n2 - op2.begin())] += *n1 * *n2;  // 
		}
	}

	for (productptr = product.begin(); productptr != product.end(); productptr++)
	{
		while (*productptr > 9)                                                            // 秈
		{
			*productptr -= 10;
			*(productptr + 1) += 1;
		}
	}

	productptr = product.rbegin();
	while (*productptr == 0 && product.size != 1)                             //  0
	{
		product.resize(product.size - 1);
		productptr = product.rbegin();
	}
	return product;
	/*// 氮砞﹚ㄢ
	int productSize = (size >= op2.size) ? size * 2 : op2.size * 2;

	HugeInteger product(productSize);

	iterator it1 = begin();                // n1 材计
	iterator it2 = op2.begin();            // n2 材计
	iterator it3 = product.begin();        // product 材
	int *temp = new int[productSize];

	// ㄢ计いΤ计 0
	if ((*it1 == 0 && size == 1) || (*it2 == 0 && op2.size == 1))
	{
		product.resize(1);
		*it3 = 0;
	}
	else
	{
		for (int i = 0; i < productSize; i++)        // ﹍て temp 
			temp[i] = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < op2.size; j++)      // ㄢ计 
			{
				temp[i + j] += it1[i] * it2[j];
			}
		}
		for (int i = 0; i < productSize; i++)
		{
			while (temp[i] > 9)
			{
				temp[i] -= 10;
				temp[i + 1]++;
			}
		}
		for (int i = 0; i < productSize; i++, it3++)      // 盢 temp  product
		{
			*it3 = temp[i];
		}

		it3 = product.end() - 1;
		while (*it3 == 0 && productSize != 1)
		{
			product.resize(productSize - 1);
			productSize--;
			it3 = product.end() - 1;
		}
	}

	return product;*/
}

// division operator; HugeInteger / HugeInteger
HugeInteger  HugeInteger::divide(const HugeInteger &op2) const
{
	int length = (size > op2.size) ? (size - op2.size) : (op2.size - size);
	HugeInteger quotient(length + 1);
	HugeInteger remainder(*this);
	HugeInteger n2(op2);
	HugeInteger zero(1);

	if (size - 1 == 0 || less(op2))                      // 砆埃计 0 ┪琌 埃
	{
		return zero;
	}
	else if (*op2.begin() == 1)                          // 埃计 1
	{
		return *this;
	}
	else
	{
		if (size > n2.size)                              // n2 璶蛤 n1 妓
		{
			iterator newptr = new int[size]();
			iterator op2ptr = op2.end() - 1;
			for (int i = size - 1; op2ptr != op2.rend(); i--, op2ptr--) {
				*(newptr + i) = *op2ptr;
			}
			n2.ptr = newptr;
			n2.size = size;
		}

		iterator Qptr = quotient.end() - 1;
		// 砆埃计埃计氮皚ぃ 0
		while (op2.size <= n2.size && quotient.size != 0)
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
		Qptr = quotient.rbegin();
		while (*Qptr == 0 && quotient.size != 1)
		{
			quotient.resize(quotient.size - 1);
			Qptr = quotient.rbegin();
		}
	}
	return quotient;
	/*int length = (size > op2.size) ? (size - op2.size) : (op2.size - size);
	int buffersize = size;
	int quotientsize = length + 1;
	int tempsize = 0;
	int remaindersize = size;

	HugeInteger buffer(buffersize);
	HugeInteger quotient(quotientsize);
	HugeInteger remainder(remaindersize);

	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator it3 = quotient.begin();
	iterator it4 = remainder.begin();
	iterator it5 = buffer.begin();
	int *temp = new int[buffersize];


	if (size - 1 == 0 || size == 0)                 // Τ计 0 
	{
		quotientsize = 1;
		*it3 = 0;
		quotient.resize(1);
	}
	else if (less(op2))                            // 埃
	{
		for (; it1 != end(); it1++, it4++)
		{
			*it4 = *it1;
		}
		quotientsize = 1;
		*it3 = 0;
		quotient.resize(1);
	}
	else                                           // 埃
	{
		for (int i = 0; i < buffersize; i++)       // ﹍て temp
			temp[i] = 0;
		for (; it1 != end(); it1++, it4++)
		{
			*it4 = *it1;
		}
		// 琵埃计砆埃计计妓
		for (int i = 0; i < size; i++, it2++)
		{
			if (i < op2.size)
				temp[i + length] = *it2;
			else
				temp[i - op2.size] = 0;
		}
		for (int i = 0; i < buffersize; i++, it5++)
		{
			*it5 = temp[i];
		}
		int c = 1;
		// 砆埃计埃计氮皚ぃ 0
		while (op2.size <= remaindersize && quotientsize != 0)
		{
			if (remainder.less(buffer))
			{
				buffer.divideByTen();
				quotientsize--;
				c++;
			}
			else
			{
				it3 = quotient.end() - c;
				remainder.assign(remainder.subtract(buffer));
				*it3 += 1;
			}
		}
		// 砞 quotientSize
		quotientsize = length + 1;
		it3 = quotient.end() - 1;
		while (*it3 == 0 && quotientsize != 1)
		{
			quotient.resize(quotientsize - 1);
			quotientsize--;
			it3 = quotient.end() - 1;
		}
	}

	return quotient;*/
}

// modulus operator; HugeInteger % HugeInteger
HugeInteger HugeInteger::modulus(const HugeInteger &op2) const
{
	// 砆埃计 0 ┪琌 埃计 1 , 緇计 0
	if (size - 1 == 0 || *op2.begin() == 1)
	{
		HugeInteger zero(1);
		return zero;
	}
	else if (less(op2))                                   // 埃
	{
		return *this;
	}
	else
	{
		HugeInteger quotient(divide(op2));                // n1 / n2  坝
		HugeInteger remainder(quotient.multiply(op2));    // 埃计 * 坝
		remainder.assign(subtract(remainder));            // 砆埃计 - ( 埃计 * 坝 ) = 緇计
		return remainder;
	}
	/*int length = (size > op2.size) ? (size - op2.size) : (op2.size - size);
	int buffersize = size;
	int quotientsize = length + 1;
	int tempsize = 0;
	int remaindersize = size;

	HugeInteger buffer(buffersize);
	HugeInteger quotient(quotientsize);
	HugeInteger remainder(remaindersize);

	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator it3 = quotient.begin();
	iterator it4 = remainder.begin();
	iterator it5 = buffer.begin();
	int *temp = new int[buffersize];


	if (size - 1 == 0 || size == 0)                 // Τ计 0 
	{
		remaindersize = 1;
		*it4 = 0;
		remainder.resize(1);
	}
	else if (less(op2))                            // 埃
	{
		for (; it1 != end(); it1++, it4++)
		{
			*it4 = *it1;
		}
	}
	else                                           // 埃
	{
		for (int i = 0; i < buffersize; i++)       // ﹍て temp
			temp[i] = 0;
		for (; it1 != end(); it1++, it4++)
		{
			*it4 = *it1;
		}
		// 琵埃计砆埃计计妓
		for (int i = 0; i < size; i++, it2++)
		{
			if (i < op2.size)
				temp[i + length] = *it2;
			else
				temp[i - op2.size] = 0;
		}
		for (int i = 0; i < buffersize; i++, it5++)
		{
			*it5 = temp[i];
		}
		int c = 1;
		// 砆埃计埃计氮皚ぃ 0
		while (op2.size <= remaindersize && quotientsize != 0)
		{
			if (remainder.less(buffer))
			{
				buffer.divideByTen();
				quotientsize--;
				c++;
			}
			else
			{
				it3 = quotient.end() - c;
				remainder.assign(remainder.subtract(buffer));
				*it3 += 1;
			}
		}
	}
	return remainder;*/
}