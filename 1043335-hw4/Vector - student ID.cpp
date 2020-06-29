// Member-function definitions for class Vector
#include <iostream>
using namespace std;
#include "Vector.h" // include definition of class Vector

 // Constructs a vector with n elements. Each element is a copy of val
Vector::Vector( unsigned int n )
   : size( n ),
     capacity( n ),
     ptr( new unsigned int[ n ]() )
{
} // end Vector default constructor

// destructor
Vector::~Vector()
{
   delete [] ptr;
} // end destructor

unsigned int* Vector::begin() const
{
   return ptr;
}

unsigned int* Vector::end() const
{
   return ptr + size;
}

unsigned int* Vector::rbegin() const
{
   return ptr + size - 1;
}

unsigned int* Vector::rend() const
{
   return ptr - 1;
}

unsigned int Vector::getSize() const
{
   return size;
}

// Constructs a vector with a copy of each of the elements in x, in the same order.
Vector::Vector(const Vector &vectorToCopy)
{
	size = vectorToCopy.size;
	ptr = new unsigned int[size];

	for (unsigned int i = 0; i < size; i++)
		*(ptr + i) = *(vectorToCopy.ptr + i);
}

const Vector &Vector::operator=(const Vector &right) // assignment operator
{
	size = right.size;
	capacity = size;
	iterator temp = new unsigned int[size]();

	for (unsigned int i = 0; i < size; i++)
		*(temp + i) = *(right.ptr + i);

	delete[] ptr;
	ptr = temp;
	return *this;
}

bool Vector::operator==(const Vector &right) const // equality operator
{
	if (size != right.size)
		return false;
	else
	{
		iterator it1 = begin();
		iterator it2 = right.begin();
		for (; it1 != end(); it1++, it2++)
		{
			if (*it1 != *it2)
				return false;
		}
	}
	return true;
}

// inequality operator; returns opposite of == operator
bool Vector::operator!=(const Vector &right) const
{
	return !operator==(right);
}

// subscript operator for non-const objects returns modifiable lvalue
unsigned int &Vector::operator[](unsigned int subscript)
{
	return ptr[subscript];
}

// subscript operator for const objects returns rvalue
unsigned int Vector::operator[](unsigned int subscript) const
{
	return ptr[subscript];
}

void Vector::resize(unsigned int n)
{
	if (n == size)                    // 大小相等時跳出
	{
		return;
	}
	else                              // 小變大
	{
		size = n;
		operator=(*this);
	}
}

void Vector::push_back(const unsigned int val)
{
	resize(size + 1);                // 重新配置記憶體
	iterator last = rbegin();        // 指向最後一格
	*last = val;                     // 將值放入
}