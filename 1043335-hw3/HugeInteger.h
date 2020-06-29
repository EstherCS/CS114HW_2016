#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include "Vector.h" // include definition of class Vector 

// HugeInteger class definition
class HugeInteger
{
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &assign( const HugeInteger &right ); // assignment operator
   bool equal( const HugeInteger &right ) const;          // equal to
   bool notEqual( const HugeInteger &right ) const;       // not equal to
   bool less( const HugeInteger &right ) const;           // less than
   bool greater( const HugeInteger &right ) const;        // greater than
   bool lessEqual( const HugeInteger &right ) const;      // less than or equal to
   bool greaterEqual( const HugeInteger &right ) const;   // greater than or equal to

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

   void convert( Vector vector ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
   void output();                 // output a HugeInteger
private:
   Vector integer;
   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // HugeInteger /= 10
}; // end class HugeInteger

#endif