// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include "Vector.h" // include definition of class Vector 

class HugeInteger
{
   friend ostream &operator<<( ostream &, HugeInteger & );
public:
   HugeInteger(); // default constructor
   HugeInteger( const HugeInteger &integerToCopy ); // copy constructor
   ~HugeInteger(); // destructor

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
   HugeInteger operator/( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   HugeInteger operator%( const HugeInteger &op2 ) const;

   // prefix increment operator
   HugeInteger &operator++();

   // postfix increment operator
   HugeInteger operator++( int );

   void convert( Vector vector ); // convert a string of decimal digits into a HugeInteger
   bool isZero() const;           // tests if a HugeInteger is zero
private:
   Vector integer;
   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();           // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
}; // end class HugeInteger

#endif