#ifndef VECTOR_H
#define VECTOR_H

// Vector class definition
class Vector
{
public:
   typedef int* iterator;
   typedef int* reverse_iterator;

   Vector( unsigned int n = 0 ); // Constructor; Constructs a zero vector with size n

   // Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
   Vector( const Vector &vectorToCopy );

   ~Vector(); // Destructor; Destroys the vector.

   const Vector &assign( const Vector &right ); // assignment operator

   bool equal( const Vector &right ) const;     // equal to

   bool notEqual( const Vector &right ) const;  // not equal to

   int* begin() const; // Returns a pointer pointing to the first element in the vector.
                       // If the vector is empty, the returned pointer shall not be dereferenced.

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   int* end() const;

   int* rbegin() const; // Returns a pointer pointing to the last element in the vector.

   // Returns a pointer pointing to the theoretical element preceding the first element in the vector.
   int* rend() const;

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
   // This effectively increases the container size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const int val );

private:
   unsigned int size; // the number of elements in the vector
                      // This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
   unsigned int capacity; // the size of the storage space currently allocated for the vector, expressed in terms of elements.
                          // This capacity is not necessarily equal to the vector size. It can be equal or greater,
                          // with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
   int *ptr; // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class template Vector

#endif