// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "List.h" // include definition of class template List 
#include "Vector.h" // include definition of class template Vector 

template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream &operator<<( ostream &, HugeInteger< U > & );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to
   bool operator!=( const HugeInteger &right ) const; // greater than or equal to
   bool operator<( const HugeInteger &right ) const;  // less than
   bool operator>( const HugeInteger &right ) const;  // greater than
   bool operator<=( const HugeInteger &right ) const; // less than or equal to
   bool operator>=( const HugeInteger &right ) const; // greater than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( const HugeInteger &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( const  HugeInteger &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( const HugeInteger &op2 ) const;
     
   HugeInteger &operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   void convert( Vector< unsigned int > intVector ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const; // return true if and only if all digits are zero

private:
   T integer;

   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
}; // end class template HugeInteger

#endif