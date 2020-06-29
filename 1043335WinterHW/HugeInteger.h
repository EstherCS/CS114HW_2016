// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <fstream>

class HugeInteger
{
public:
   static const int digits = 1000;   // maximum digits in a HugeInteger

   HugeInteger();                    // default constructor; construct a HugeInteger with size 0

   bool equal( HugeInteger );        // equal to
   bool notEqual( HugeInteger );     // not equal to
   bool less( HugeInteger );         // less than
   bool greater( HugeInteger );      // greater than
   bool lessEqual( HugeInteger );    // less than or equal
   bool greaterEqual( HugeInteger ); // greater than or equal to

   HugeInteger add( HugeInteger op2 );      // addition operator; HugeInteger + HugeInteger
   HugeInteger subtract( HugeInteger op2 ); // subtraction operator; HugeInteger - HugeInteger provided that
                                            // the minuend is greater than or equal to the subtrahend
   HugeInteger multiply( HugeInteger op2 ); // multiplication operator; HugeInteger * HugeInteger
   HugeInteger divide( HugeInteger op2 );   // division operator; HugeInteger / HugeInteger
	HugeInteger modulus( HugeInteger op2 );  // modulus operator; HugeInteger % HugeInteger

   void convert( char numericString[] );    // convert a string of decimal digits into a HugeInteger
   bool isZero(); // return true if and only if all digits are zero
   void output(); // output a HugeInteger
private:
   int size;                // the number of digits of the integer
   short integer[ digits ]; // used to store a nonnegative integer, one digit per element

   HugeInteger( int n );    // constructor; construct a zero HugeInteger with size n
   void divideByTen();      // HugeInteger /= 10
}; // end class HugeInteger

#endif