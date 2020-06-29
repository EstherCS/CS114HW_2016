// Member-function definitions for class Vector
#include "Vector.h" // include definition of class Vector


 // constructor; constructs a zero vector with size n
Vector::Vector( unsigned int n )
   : size( n ),
     capacity( n ),
     ptr( new int[ n ]() )
{
} // end Vector constructor

// destructor; destroys the Vector
Vector::~Vector()
{
	delete[] ptr;
} // end destructor

int* Vector::begin() const
{
   return ptr;
}

int* Vector::end() const
{
   return ptr + size;
}

int* Vector::rbegin() const
{
   return ptr + size - 1;
}

int* Vector::rend() const
{
   return ptr - 1;
}

unsigned int Vector::getSize() const
{
   return size;
}

// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
Vector::Vector(const Vector &vectorToCopy)
{
	size = vectorToCopy.size;
	ptr = new int[size];

	for (int i = 0; i < size; i++)
		*(ptr + i) = *(vectorToCopy.ptr + i);
}

const Vector& Vector::assign(const Vector &right) // assignment operator
{
	size = right.size;
	capacity = size;
	iterator temp = new int[size]();

	for (int i = 0; i < size; i++)
		*(temp + i) = *(right.ptr + i);
	
	delete[] ptr;
	ptr = temp;
	return *this;
}

bool Vector::equal(const Vector &right) const     // equal to
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

bool Vector::notEqual(const Vector &right) const  // not equal to
{
	return !equal(right);
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
		assign(*this);
	}
}

void Vector::push_back(const int val)
{
	resize(size + 1);                // 重新配置記憶體
	iterator last = rbegin();        // 指向最後一格
	*last = val;                     // 將值放入
}