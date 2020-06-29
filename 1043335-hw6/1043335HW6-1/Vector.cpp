// Member-function definitions for class template Vector

#include "Vector.h" // include definition of class template Vector

// constructor; constructs a zero vector with size n
template< typename T >
Vector< T >::Vector(unsigned int n)
: size(n),
capacity(n),
ptr(new T[n]())
{
} // end Vector constructor

// destructor; destroys the Vector
template< typename T >
Vector< T >::~Vector()
{
	delete[] ptr;
} // end destructor

// inequality operator; returns opposite of == operator
template< typename T >
bool Vector< T >::operator!=(const Vector< T > &right) const
{
	return !(*this == right); // invokes Vector::operator==
}

template< typename T >
T* Vector< T >::begin() const
{
	return ptr;
}

template< typename T >
T* Vector< T >::end() const
{
	return ptr + size;
}

template< typename T >
T* Vector< T >::rbegin() const
{
	return ptr + size - 1;
}

template< typename T >
T* Vector< T >::rend() const
{
	return ptr - 1;
}

template< typename T >
unsigned int Vector< T >::getSize() const
{
	return size;
}

template< typename T >
const Vector< T > &Vector< T >::operator=(const Vector< T > &right) // assignment operator
{
	size = right.size;
	capacity = size;
	iterator temp = new T[size]();

	for (unsigned int i = 0; i < size; i++)
		*(temp + i) = *(right.ptr + i);

	delete[] ptr;
	ptr = temp;
	return *this;
}

template< typename T >
bool Vector< T >::operator==(const Vector< T > &right) const // equal to
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

template< typename T >
void Vector< T >::resize(unsigned int n)
{
	if (n == size)                    // �j�p�۵��ɸ��X
	{
		return;
	}
	else if (n < capacity)            // �j�ܤp
	{
		size = n;
		operator=(*this);
	}
	else                              // �p�ܤj
	{
		iterator former = begin();
		iterator newptr = new T[n]();

		for (int i = 0; i < size; i++, former++)
		{
			newptr[i] = *former;
		}
		delete[] ptr;
		ptr = newptr;
		size = n;
	}
}

template< typename T >
void Vector< T >::push_back(const T val)
{
	resize(size + 1);                // ���s�t�m�O����
	iterator last = rbegin();        // ���V�̫�@��
	*last = val;                     // �N�ȩ�J
}

template< typename T >
Vector< T >::Vector(const Vector< T > &vectorToCopy)
{
	size = vectorToCopy.size;
	ptr = new T[size];

	for (unsigned int i = 0; i < size; i++)
		*(ptr + i) = *(vectorToCopy.ptr + i);
}