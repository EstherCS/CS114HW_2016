#ifndef VECTOR_H
#define VECTOR_H

// Vector class template definition
template< typename T >
class Vector
{
public:
   typedef T* iterator;
   typedef T* reverse_iterator;

   Vector( unsigned int n = 0 ); // Constructor; Constructs a vector with n elements.

   // Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
   Vector( const Vector< T > &vectorToCopy );

   ~Vector(); // Destructor; Destroys the vector.

   const Vector< T > &operator=( const Vector< T > &right ); // assignment operator

   bool operator==( const Vector &right ) const; // equal to

   bool operator!=( const Vector &right ) const; // not equal to

   iterator begin() const; // Returns a pointer pointing to the first element in the vector.
                           // If the vector is empty, the returned pointer shall not be dereferenced.

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   reverse_iterator rbegin() const; // Returns a pointer pointing to the last element in the vector.

   // Returns a pointer pointing to the theoretical element preceding the first element in the vector.
   reverse_iterator rend() const;

   unsigned int getSize() const; // Returns the number of elements in the vector.

   // Resizes the vector so that it contains n elements.
   // If n is smaller than the current vector size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( unsigned int n );
   
   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const T val );

private:
   unsigned int size; // the number of elements in the vector
                      // This is the number of actual objects held in the vector,
                      // which is not necessarily equal to its storage capacity.
   unsigned int capacity; // the size of the storage space currently allocated for the vector,
                          // expressed in terms of elements.
                          // This capacity is not necessarily equal to the vector size.
                          // It can be equal or greater, with the extra space allowing to accommodate for growth
                          // without the need to reallocate on each insertion.
   T *ptr; // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class template Vector

#endif