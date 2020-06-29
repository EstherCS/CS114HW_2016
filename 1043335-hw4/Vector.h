#ifndef VECTOR_H
#define VECTOR_H

// Vector class definition
class Vector
{
public:
   typedef unsigned int* iterator;
   typedef unsigned int* reverse_iterator;

   Vector( unsigned int n = 0 ); // Constructs a vector with n elements. Each element is a copy of val.

   // Constructs a vector with a copy of each of the elements in x, in the same order.
   Vector( const Vector &vectorToCopy );

   ~Vector(); // Destroys the vector.

   const Vector &operator=( const Vector &right ); // assignment operator

   bool operator==( const Vector &right ) const; // equality operator

   bool operator!=( const Vector &right ) const;
   // inequality operator; returns opposite of == operator

   // subscript operator for non-const objects returns modifiable lvalue
   unsigned int &operator[]( unsigned int subscript );

   // subscript operator for const objects returns rvalue
   unsigned int operator[]( unsigned int subscript ) const;

   unsigned int* begin() const; // Returns a pointer pointing to the first element in the vector.
                                 // If the vector is empty, the returned pointer shall not be dereferenced.

   unsigned int* end() const; // Returns an pointer referring to the past-the-end element in the vector.
               // The past-the-end element is the theoretical element that would follow the last element in the vector.
               // It does not point to any element, and thus shall not be dereferenced.

   unsigned int* rbegin() const; // Returns a pointer pointing to the first element in the vector.
                                 // If the vector is empty, the returned pointer shall not be dereferenced.

   unsigned int* rend() const; // Returns an pointer referring to the past-the-end element in the vector.
               // The past-the-end element is the theoretical element that would follow the last element in the vector.
               // It does not point to any element, and thus shall not be dereferenced.

   unsigned int getSize() const; // Returns the number of elements in the vector.

   void resize( unsigned int n );
   // Resizes the container so that it contains n elements.
   // If n is smaller than the current container size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.
   
   void push_back( const unsigned int val ); // Adds a new element at the end of the vector, after its current last element.
                                  // The content of val is copied to the new element.
                                  // This effectively increases the container size by one,
                                  // which causes an automatic reallocation of the allocated storage space
                                  // if -and only if- the new vector size surpasses the current vector capacity.
private:
   unsigned int size; // the number of elements in the vector
                      // This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
   unsigned int capacity; // the size of the storage space currently allocated for the vector, expressed in terms of elements.
                          // This capacity is not necessarily equal to the vector size. It can be equal or greater,
                          // with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
   unsigned int *ptr; // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class template Vector

#endif