// Member-function definitions for class HugeInteger.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 

// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger()
{
	size = 0;
} // end HugeInteger default constructor

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(int n)
{
	size = (n >= 0 && n <= digits) ? n : digits;
	for (int i = 0; i < size; i++)
		integer[i] = 0;
} // end HugeInteger constructor

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert(char numericString[])
{
	size = strlen(numericString);
	for (int i = 0; i < size; i++)
		integer[i] = numericString[size - i - 1] - '0';

	for (; size > 0; size--)
	if (integer[size - 1] != 0)
		break;
	if (size == 0)
		size++;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (int i = 0; i < size; i++)
	if (integer[i] != 0)
		return false;
	return true;
} // end function isZero

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(HugeInteger op2)
{
	int sumSize = (size >= op2.size) ? size + 1 : op2.size + 1;
	HugeInteger sum(sumSize);

	for (int i = 0; i < size; i++)
		sum.integer[i] = integer[i];

	for (int i = 0; i < op2.size; i++)
		sum.integer[i] += op2.integer[i];

	for (int i = 0; i < sum.size - 1; i++)
	if (sum.integer[i] > 9) // determine whether to carry a 1
	{
		sum.integer[i] -= 10; // reduce to 0-9
		sum.integer[i + 1]++;
	}

	if (sum.integer[sum.size - 1] == 0)
		sum.size--;

	return sum;
} // end function add

// overloaded output operator
void HugeInteger::output()
{
	if (size == 0)
		cout << 0;
	else
	for (int i = size - 1; i >= 0; i--)
		cout << integer[i];
} // end function output

void HugeInteger::divideByTen()
{
	if (size > 0)
	{
		for (int i = 1; i < size; i++)
			integer[i - 1] = integer[i];
		integer[size - 1] = 0;
		size--;
	}
} // end function divideByTen

bool HugeInteger::equal(HugeInteger n2)        // equal to
{
	if (size != n2.size)                       // 長度不同
		return false;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (integer[i] != n2.integer[i])   // 有不同的則回傳 false 
				return false;
		}
		return true;
	}
}

bool HugeInteger::notEqual(HugeInteger n2)     // not equal to
{
	return !equal(n2);
	/*if (size != n2.size)
		return true;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (integer[i] != n2.integer[i])   // 有不同的則回傳 true 
				return true;
		}
		return false;
	}*/
}

bool HugeInteger::less(HugeInteger n2)         // less than  n1 < n2
{
	if (size < n2.size)
		return true;
	else if (size == n2.size)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (integer[i] < n2.integer[i])    // 從高位數開始比對
				return true;
			if (integer[i] > n2.integer[i])
				return false;
		}
	}
	return false;                              // 相等會回傳 false
}

bool HugeInteger::greater(HugeInteger n2)      // greater than  n1 > n2
{
	return n2.less(*this);
	/*if (size > n2.size)
		return true;
	else if (size == n2.size)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (integer[i] > n2.integer[i])    // 從高位數開始比對
				return true;
			if (integer[i] < n2.integer[i])
				return false;
		}
	}
	return false;                              // 相等會回傳 false*/
}

bool HugeInteger::lessEqual(HugeInteger n2)    // less than or equal  n1 <= n2
{
	if (less(n2))
		return true;
	else
		return equal(n2);
	/*if (size > n2.size)
		return false;
	else if (size == n2.size)
	{
		for (int i = size - 1; i >= 0; i--)    // 從高位數開始比對
		{
			if (integer[i] < n2.integer[i])
				return true;
			if (integer[i] > n2.integer[i])
				return false;
		}
	}
	return true;                              // 相等會回傳 true*/
}

bool HugeInteger::greaterEqual(HugeInteger n2) // greater than or equal to  n1 >= n2
{
	return n2.lessEqual(*this);
	/*if (size < n2.size)
		return false;
	else if (size == n2.size)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (integer[i] > n2.integer[i])
				return true;
			if (integer[i] < n2.integer[i])
				return false;
		}
	}
	return true;                              // 相等會回傳 true*/
}

HugeInteger HugeInteger::subtract(HugeInteger op2) // subtraction operator; HugeInteger - HugeInteger provided that
                                                   // the minuend is greater than or equal to the subtrahend
{
	HugeInteger difference(*this);
	for (int i = op2.size; i <= size; i++)         // 使兩數的長度一樣方便相減 
	{
		op2.integer[i] = 0;
	}
	for (int i = 0; i < difference.size; i++)
	{
		difference.integer[i] -= op2.integer[i];
	}
	for (int i = 0; i < difference.size; i++)      // 處理進位
	{
		if (difference.integer[i] < 0)
		{
			difference.integer[i] += 10;
			difference.integer[i + 1]--;
		}
	}
	while (difference.integer[difference.size - 1] == 0 && difference.size != 1)
		difference.size--;                         // 刪去數字前的 0

	return difference;
	/*int differenceSize = size;                     // 前面會設定為大減小

	HugeInteger difference(differenceSize);

	for (int i = 0; i < size; i++)
	{
		difference.integer[i] = integer[i];
	}
	for (int i = op2.size; i <= size; i++)         // 使兩數的長度一樣方便相減 
	{
		op2.integer[i] = 0;
	}
	for (int i = 0; i < difference.size; i++)
	{
		difference.integer[i] -= op2.integer[i];
	}
	for (int i = 0; i < difference.size; i++)      // 處理進位
	{
		if (difference.integer[i] < 0)
		{
			difference.integer[i] += 10;
			difference.integer[i + 1]--;
		}
	}
	while (difference.integer[difference.size - 1] == 0 && difference.size != 1)
		difference.size--;                         // 刪去數字前的 0

	return difference;*/
}


HugeInteger HugeInteger::multiply(HugeInteger op2) // multiplication operator; HugeInteger * HugeInteger
{
	int productSize = (size >= op2.size) ? size * 2 : op2.size * 2;

	HugeInteger product(productSize);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < op2.size; j++)      // 兩數相乘 
		{
			product.integer[i + j] += integer[i] * op2.integer[j];
		}
	}
	for (int i = 0; i < product.size; i++)      // 進位
	{
		while (product.integer[i] > 9)
		{
			product.integer[i] -= 10;
			product.integer[i + 1]++;
		}
	}
	while (product.integer[product.size - 1] == 0 && product.size != 1)
		product.size--;                             // 刪去數字前的 0             

	return product;
	/*int productsize = (size >= op2.size) ? size * 2 : op2.size * 2;               // 答案長度設定為兩倍

	HugeInteger product(productsize);

	if ((integer[0] == 0 && size == 1) || (op2.integer[0] == 0 && op2.size == 1)) // 相乘兩數有一數為 0
	{
		product.size = 1;
		product.integer[0] = 0;                     // 答案為 0
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < op2.size; j++)      // 兩數相乘 
			{
				product.integer[i + j] += integer[i] * op2.integer[j];
			}
		}
		for (int i = 0; i < product.size; i++)      // 進位
		{
			while (product.integer[i] > 9)
			{
				product.integer[i] -= 10;
				product.integer[i + 1]++;
			}
		}
	}
	

	while (product.integer[product.size - 1] == 0 && product.size != 1)
		product.size--;                             // 刪去數字前的 0             

	return product;*/
}

HugeInteger HugeInteger::divide(HugeInteger op2)   // division operator; HugeInteger / HugeInteger
{
	int length = (size > op2.size) ? (size - op2.size) : (op2.size - size);
	HugeInteger quotient(length + 1);
	HugeInteger remainder(*this);
	HugeInteger n2(size);
	HugeInteger zero(1);

	if (size - 1 == 0 || less(op2))                      // 被除數為 0 或是 小除大
	{
		return zero;
	}
	else if (op2.integer[0] == 1)                        // 除數為 1
	{
		return *this;
	}
	else
	{
		// 讓除數、被除數位數一樣
		for (int i = 0; i < size; i++)
		{
			if (i < op2.size)
				n2.integer[i + length] = op2.integer[i];
			else
				n2.integer[i - op2.size] = 0;
		}
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.size <= n2.size && quotient.size != 0)
		{
			if (remainder.less(n2))
			{
				n2.divideByTen();
				quotient.size--;
			}
			else
			{
				remainder = remainder.subtract(n2);
				quotient.integer[quotient.size - 1]++;
			}
		}
		// 重設 quotientSize
		quotient.size = length + 1;

		while (quotient.integer[quotient.size - 1] == 0 && quotient.size != 1)
			quotient.size--;
	}
	return quotient;
	/*int length = size - op2.size;
	int buffersize = size;
	int quotientsize = length + 1;
	int tempsize = 0;
	int remaindersize = size;

	HugeInteger buffer(buffersize);
	HugeInteger quotient(quotientsize);
	HugeInteger temp(tempsize);
	HugeInteger remainder(remaindersize);

	if (integer[size - 1] == 0)                    // 0 為被除數
	{
		if (integer[0] == 0)
		{
			quotient.size = 1;
			quotient.integer[0] = 0;
			remainder.size = 1;
			remainder.integer[0] = 0;
		}
	}
	else if (less(op2))                            // 小除大
	{
		for (int i = 0; i < size; i++)
		{
			remainder.integer[i] = integer[i];
		}
		quotient.size = 1;
		quotient.integer[0] = 0;
	}
	else                                           // 大除小
	{
		for (int i = 0; i < size; i++)
		{
			remainder.integer[i] = integer[i];
		}                          
		// 讓除數、被除數位數一樣
		for (int i = 0; i < size; i++)             
		{
			if (i < op2.size)
				buffer.integer[i + length] = op2.integer[i];
			else
				buffer.integer[i - op2.size] = 0;
		}
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.size <= remainder.size && quotient.size != 0)
		{
			if (remainder.less(buffer))
			{
				buffer.divideByTen();
				quotient.size--;
			}
			else
			{
				remainder = remainder.subtract(buffer);
				quotient.integer[quotient.size - 1]++;
			}
		}
		// 重設 quotientSize
		quotient.size = length + 1;

		while (quotient.integer[quotient.size - 1] == 0 && quotient.size != 1)
			quotient.size--;
	}

	return quotient;*/
}

HugeInteger HugeInteger::modulus(HugeInteger op2)  // modulus operator; HugeInteger % HugeInteger
{
	// 被除數為 0 或是 除數為 1 時, 餘數為 0
	if (size - 1 == 0 || op2.integer[0] == 1)
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
		remainder = subtract(remainder);                  // 被除數 - ( 除數 * 商 ) = 餘數
		return remainder;
	}
	/*int length = size - op2.size;
	int buffersize = size;
	int quotientsize = length + 1;
	int tempsize = 0;
	int remaindersize = size;

	HugeInteger buffer(buffersize);
	HugeInteger quotient(quotientsize);
	HugeInteger temp(tempsize);
	HugeInteger remainder(remaindersize);

	if (integer[size - 1] == 0)                    // 0 為被除數
	{
		if (integer[0] == 0)
		{
			quotient.size = 1;
			quotient.integer[0] = 0;
			remainder.size = 1;
			remainder.integer[0] = 0;
		}
	}
	else if (less(op2))                            // 小除大
	{
		for (int i = 0; i < size; i++)
		{
			remainder.integer[i] = integer[i];
		}
		quotient.size = 1;
		quotient.integer[0] = 0;
	}
	else                                           // 大除小
	{
		for (int i = 0; i < size; i++)
		{
			remainder.integer[i] = integer[i];
		}
		// 讓除數、被除數位數一樣
		for (int i = 0; i < size; i++)
		{
			if (i < op2.size)
				buffer.integer[i + length] = op2.integer[i];
			else
				buffer.integer[i - op2.size] = 0;
		}
		// 被除數長度小於除數長度、答案陣列長度不為 0
		while (op2.size <= remainder.size && quotient.size != 0)
		{
			if (remainder.less(buffer))
			{
				buffer.divideByTen();
				quotient.size--;
			}
			else
			{
				remainder = remainder.subtract(buffer);
				quotient.integer[quotient.size - 1]++;
			}
		}
	}

	return remainder;*/
}