#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H

// VecIterator class template definition
template< typename T >
class VecIterator
{
public:
   VecIterator( T *p = 0 ) // default constructor
      : ptr( p )
   {
   }

   VecIterator( const VecIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~VecIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const VecIterator &operator=( const VecIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   T& operator*() const // dereferencing operator
   {
      return *ptr;
   }

   VecIterator& operator++() // prefix increment operator
   {
      ++ptr;
      return *this;
   }

   VecIterator& operator--() // predecrement an iterator
   {
      --ptr;
      return *this;
   }

   bool operator==( const VecIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VecIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

private:
   T *ptr; // keep a pointer to vector
}; // end class template VecIterator

#endif


#ifndef REVERSE_VEC_ITERATOR_H
#define REVERSE_VEC_ITERATOR_H

// ReverseVecIterator class template definition
template< typename T >
class ReverseVecIterator
{
public:
   ReverseVecIterator( T *p = 0 ) // default constructor
      : ptr( p )
   {
   }

   ReverseVecIterator( const ReverseVecIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~ReverseVecIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const ReverseVecIterator &operator=( const ReverseVecIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   T& operator*() const // dereferencing operator
   {
      return *ptr;
   }

   ReverseVecIterator& operator++() // prefix increment operator
   {
      --ptr;
      return *this;
   }

   ReverseVecIterator& operator--() // predecrement an iterator
   {
      ++ptr;
      return *this;
   }

   bool operator==( const ReverseVecIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ReverseVecIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

private:
   T *ptr; // keep a pointer to vector
}; // end class template ReverseVecIterator

#endif


#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector
{
public:
   typedef VecIterator< T > iterator;
   typedef ReverseVecIterator< T > reverse_iterator;

   vector( unsigned int n = 0 ); // Constructor; Constructs a vector with n elements.

   // Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
   vector( const vector &vectorToCopy );

   ~vector(); // Destructor; Destroys the vector.

   const vector &operator=( const vector &right ); // assignment operator

   bool operator==( const vector &right ) const; // equal to

   bool operator!=( const vector &right ) const; // not equal to

   iterator begin() const; // Returns a iterator pointing to the first element in the vector.
                           // If the vector is empty, the returned pointer shall not be dereferenced.

   // Returns an iterator pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   reverse_iterator rbegin() const; // Returns a iterator pointing to the last element in the vector.

   // Returns a iterator pointing to the theoretical element preceding the first element in the vector.
   reverse_iterator rend() const;

   unsigned int size() const; // Returns the number of elements in the vector.

   // Resizes the vector so that it contains n elements.
   // If n is smaller than the current vector size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( unsigned int n );

   // The vector is extended by inserting a new element before the element at position,   
   // effectively increasing the container size by one.   
   // This causes an automatic reallocation of the allocated storage space.   
   // Relocates all the elements that were after position to their new positions.
   void insert( iterator position, const T val );

private:
   unsigned int mySize; // the number of elements in the vector
                        // This is the number of actual objects held in the vector,
                        // which is not necessarily equal to its storage capacity.
   T *ptr; // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class template vector

#endif


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector( unsigned int n )
   : mySize( n ),
     ptr( n == 0 ? nullptr : new T[ n ]() )
{
} // end vector constructor

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( ptr != nullptr )
      delete[] ptr;
} // end destructor

// inequality operator; returns opposite of == operator
template< typename T >
bool vector< T >::operator!=( const vector< T > &right ) const
{
   return !( *this == right ); // invokes vector::operator==
}

template< typename T >
VecIterator< T > vector< T >::begin() const
{
   return iterator( ptr );
}

template< typename T >
VecIterator< T > vector< T >::end() const
{
   return iterator( ptr + mySize );
}

template< typename T >
ReverseVecIterator< T > vector< T >::rbegin() const
{
   return reverse_iterator( ptr + mySize - 1 );
}

template< typename T >
ReverseVecIterator< T > vector< T >::rend() const
{
   return reverse_iterator( ptr - 1 );
}

template< typename T >
unsigned int vector< T >::size() const
{
   return mySize;
}

// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
template< typename T >
vector< T >::vector(const vector &vectorToCopy)
{
	mySize = vectorToCopy.mySize;
	ptr = new T[mySize];

	for (unsigned int i = 0; i < mySize; i++)
		*(ptr + i) = *(vectorToCopy.ptr + i);
}

template< typename T >
const vector< T > &vector< T >::operator=(const vector &right) // assignment operator
{
	mySize = right.mySize;
	T *temp = new T[mySize]();

	for (unsigned int i = 0; i < mySize; i++)
		*(temp + i) = *(right.ptr + i);

	delete[] ptr;
	ptr = temp;
	return *this;
}

template< typename T >
bool vector< T >::operator==(const vector &right) const // equal to
{
	if (mySize != right.mySize)
		return false;
	else
	{
		VecIterator< T > it1 = begin();
		VecIterator< T > it2 = right.begin();
		for (; it1 != end(); it1++, it2++)
		{
			if (*it1 != *it2)
				return false;
		}
	}
	return true;
}

template< typename T >
void vector< T >::resize(unsigned int n)
{
	if (n == mySize)                  // 大小相等時跳出
	{
		return;
	}
	else if (n < mySize)              // 大變小
	{
		mySize = n;
		operator=(*this);             // 放入新的陣列
	}
	else                              // 小變大
	{
		VecIterator< T > former = begin();
		T *newptr = new T[n]();

		for (int i = 0; i < mySize; i++, former++)
		{
			newptr[i] = *former;
		}
		delete[] ptr;
		ptr = newptr;
		mySize = n;
	}
}

template< typename T >
void vector< T >::insert(iterator position, const T val)
{
	if (mySize == 0)
	{
		mySize = 1;
		ptr = new T[mySize]();
		*ptr = val;
		return;
	}
	T *temp = new T[mySize + 1]();
	VecIterator< T > now = begin();
	VecIterator< T > Tptr = temp;
	for (; now != position; now++, Tptr++)  // position 前的複製到 temp
	{
		*Tptr = *now;
	}
	*Tptr = val;
	Tptr++;
	for (; now != end(); now++, Tptr++)    // position 後
	{
		*Tptr = *now;
	}
	mySize += 1;
	delete[]ptr;
	ptr = temp;
}
