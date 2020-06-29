// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <vector> // include definition of class Vector 

class HugeInteger
{
public:
   typedef int* iterator;
   typedef int* reverse_iterator;

   HugeInteger(); // default constructor
   HugeInteger( const HugeInteger &integerToCopy ); // copy constructor
   ~HugeInteger(); // destructor

   const HugeInteger &assign( const HugeInteger &right ); // assignment operator

   bool equal( const HugeInteger &right ) const; // less than or equal to
   bool notEqual( const HugeInteger &right ) const; // greater than or equal to
   bool less( const HugeInteger &right ) const;  // less than
   bool greater( const HugeInteger &right ) const;  // greater than
   bool lessEqual( const HugeInteger &right ) const; // less than or equal to
   bool greaterEqual( const HugeInteger &right ) const; // greater than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger add( const HugeInteger &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger subtract( const HugeInteger &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger multiply( const  HugeInteger &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   HugeInteger divide( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   HugeInteger modulus( const HugeInteger &op2 ) const;

   // convert a string of decimal digits into a HugeInteger
   void convert( vector< int > intVector );

   bool isZero() const; // tests if a HugeInteger is zero
   void output() const; // output a HugeInteger
private:
   unsigned int size; // the number of elements in the vector
   int *ptr; // points to a dynamically allocated array which is used to store an integer

   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1

   // Returns a pointer pointing to the first element in the vector.
   // If the vector is empty, the returned pointer shall not be dereferenced.
   int* begin() const;

   // Returns a pointer referring to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   int* end() const;

   int* rbegin() const; // Returns a pointer pointing to the last element in the vector.

   // Returns a pointer pointing to the theoretical element preceding the first element in the vector.
   int* rend() const;

   void resize( unsigned int n );
   // Resizes the container so that it contains n elements.
   // If n is smaller than the current container size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.

}; // end class HugeInteger

#endif