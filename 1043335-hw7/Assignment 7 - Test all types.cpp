// HugeInteger test program.
#include <fstream>
using std::ifstream;
using std::ios;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "HugeInteger - 1043335 - hw7.h" // include member-function definitions for class template HugeInteger 

int enterChoice1();

int enterChoice2();

void loadTwoHugeIntegers( char fileName[], vector< unsigned int > &intVector1, vector< unsigned int > &intVector2 );

void testAllBinaryOperator( unsigned int operatorCode, vector< unsigned int > &intVector1, vector< unsigned int > &intVector2 );

template< typename T >
void testBinaryOperator( unsigned int operatorCode, HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testAssignment( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testEqual( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testNotEqual( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testLess( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testGreater( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testLessEqual( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testGreaterEqual( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testAdd( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testSubtract( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testMultiply( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testDivide( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testModulus( HugeInteger< T > n1, HugeInteger< T > n2 );

template< typename T >
void testArithmetics( HugeInteger< T > n1, HugeInteger< T > n2 );

int main()
{
   char fileName[ 13 ][ 20 ] = { "0", "hugeIntegers1.txt", "hugeIntegers2.txt",
                                      "hugeIntegers3.txt", "hugeIntegers4.txt",
                                      "hugeIntegers5.txt", "hugeIntegers6.txt",
                                      "hugeIntegers7.txt", "hugeIntegers8.txt",
                                      "hugeIntegers9.txt", "hugeIntegers10.txt",
                                      "hugeIntegers11.txt", "hugeIntegers12.txt" };

   vector< unsigned int > intVector1;
   vector< unsigned int > intVector2;
   int operatorCode = enterChoice1();
   int fileCode = enterChoice2();

   loadTwoHugeIntegers( fileName[ fileCode ], intVector1, intVector2 );

   testAllBinaryOperator( operatorCode, intVector1, intVector2 );

   system( "pause" );

} // end main

int enterChoice1()
{
   cout << "Enter your choice\n"
      << " 0 - test assignment\n"
      << " 1 - test equal\n"
      << " 2 - test notEqual\n"
      << " 3 - test less\n"
      << " 4 - test greater\n"
      << " 5 - test lessEqual\n"
      << " 6 - test greaterEqual\n"
      << " 7 - test add\n"
      << " 8 - test subtract\n"
      << " 9 - test multiply\n"
      << "10 - test divide\n"
      << "11 - test modulus\n"
      << "12 - test arithmetics\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 0 ) || ( menuChoice > 12 ) );

   return menuChoice;
} // end function enterChoice1

int enterChoice2()
{
   cout << "\nEnter your choice\n"
      << " 1 - hugeIntegers1.txt\n"
      << " 2 - hugeIntegers2.txt\n"
      << " 3 - hugeIntegers3.txt\n"
      << " 4 - hugeIntegers4.txt\n"
      << " 5 - hugeIntegers5.txt\n"
      << " 6 - hugeIntegers6.txt\n"
      << " 7 - hugeIntegers7.txt\n"
      << " 8 - hugeIntegers8.txt\n"
      << " 9 - hugeIntegers9.txt\n"
      << "10 - hugeIntegers10.txt\n"
      << "11 - hugeIntegers11.txt\n"
      << "12 - hugeIntegers12.txt\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 1 ) || ( menuChoice > 12 ) );

   return menuChoice;
} // end function enterChoice2

void loadTwoHugeIntegers( char fileName[], vector< unsigned int > &intVector1, vector< unsigned int > &intVector2 )
{
      ifstream inFile( fileName, ios::in );

      if( !inFile )
      {
         cout << "File could not be opened" << endl;
         system( "pause" );
         exit( 1 );
      }

      char digit;
      intVector1.resize( 0 );
      while( ( digit = inFile.get() ) != '\n' )
         if( digit != ' ' )
            intVector1.insert( intVector1.begin(), digit - '0' );
      // the rightmost digit (i.e., the least significant digit) will be put into intVector1[ 0 ]

      intVector2.resize( 0 );
      while( ( digit = inFile.get() ) != '\n' )
         if( digit != ' ' )
            intVector2.insert( intVector2.begin(), digit - '0' );
      // the rightmost digit (i.e., the least significant digit) will be put into intVector2[ 0 ]

      inFile.close();
}

void testAllBinaryOperator( unsigned int operatorCode, vector< unsigned int > &intVector1, vector< unsigned int > &intVector2 )
{
   HugeInteger< vector< int > > n1;
   HugeInteger< vector< int > > n2;
   n1.convert( intVector1 );
   n2.convert( intVector2 );
   testBinaryOperator( operatorCode, n1, n2 );

   HugeInteger< vector< unsigned int > > n3;
   HugeInteger< vector< unsigned int > > n4;
   n3.convert( intVector1 );
   n4.convert( intVector2 );
   testBinaryOperator( operatorCode, n3, n4 );

   HugeInteger< vector< short int > > n5;
   HugeInteger< vector< short int > > n6;
   n5.convert( intVector1 );
   n6.convert( intVector2 );
   testBinaryOperator( operatorCode, n5, n6 );

   HugeInteger< vector< unsigned short int > > n7;
   HugeInteger< vector< unsigned short int > > n8;
   n7.convert( intVector1 );
   n8.convert( intVector2 );
   testBinaryOperator( operatorCode, n7, n8 );

   HugeInteger< list< int > > n9;
   HugeInteger< list< int > > n10;
   n9.convert( intVector1 );
   n10.convert( intVector2 );
   testBinaryOperator( operatorCode, n9, n10 );

   HugeInteger< list< unsigned int > > n11;
   HugeInteger< list< unsigned int > > n12;
   n11.convert( intVector1 );
   n12.convert( intVector2 );
   testBinaryOperator( operatorCode, n11, n12 );

   HugeInteger< list< short int > > n13;
   HugeInteger< list< short int > > n14;
   n13.convert( intVector1 );
   n14.convert( intVector2 );
   testBinaryOperator( operatorCode, n13, n14 );

   HugeInteger< list< unsigned short int > > n15;
   HugeInteger< list< unsigned short int > > n16;
   n15.convert( intVector1 );
   n16.convert( intVector2 );
   testBinaryOperator( operatorCode, n15, n16 );

   cout << endl << endl;
}

template< typename T >
void testBinaryOperator( unsigned int operatorCode, HugeInteger< T > n1, HugeInteger< T > n2 )
{
   void( *array[ 13 ] )( HugeInteger< T >, HugeInteger< T > ) =
   { testAssignment, testEqual, testNotEqual, testLess, testGreater, testLessEqual, testGreaterEqual,
   testAdd, testSubtract, testMultiply, testDivide, testModulus, testArithmetics };

   cout << endl;

   ( *array[ operatorCode ] )( n1, n2 ); // invoke the function at location choice in array1
}

template< typename T >
void testAssignment( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   cout << "n1                  : " << n1 << endl;
   cout << "n2 before assignment: " << n2 << endl;
   n2 = n1;
   cout << "n2  after assignment: " << n2 << endl;
}

template< typename T >
void testEqual( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 == n2 )
      cout << n1 << " == " << n2;
   else
      cout << n1 << " != " << n2;
}

template< typename T >
void testNotEqual( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 != n2 )
      cout << n1 << " != " << n2;
   else
      cout << n1 << " == " << n2;
}

template< typename T >
void testLess( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 < n2 )
      cout << n1 << " < " << n2;
   else
      cout << n1 << " >= " << n2;
}

template< typename T >
void testGreater( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 > n2 )
      cout << n1 << " > " << n2;
   else
      cout << n1 << " <= " << n2;
}

template< typename T >
void testLessEqual( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 <= n2 )
      cout << n1 << " <= " << n2;
   else
      cout << n1 << " > " << n2;
}

template< typename T >
void testGreaterEqual( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 >= n2 )
      cout << n1 << " >= " << n2;
   else
      cout << n1 << " < " << n2;
}

template< typename T >
void testAdd( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   cout << n1 << " + " << n2 << " == " << n1 + n2;
}

template< typename T >
void testSubtract( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n1 < n2 )
      cout << n1 << " - " << n2 << " == -" << n2 - n1;
   else
      cout << n1 << " - " << n2 << " == " << n1 - n2;
}

template< typename T >
void testMultiply( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   cout << n1 << " * " << n2 << " == " << n1 * n2;
}

template< typename T >
void testDivide( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( !n2.isZero() )
      cout << n1 << " / " << n2 << " == " << n1 / n2;
   else
      cout << "divide by zero!!";
}

template< typename T >
void testModulus( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( !n2.isZero() )
      cout << n1 << " % " << n2 << " == " << n1 % n2;
   else
      cout << "divide by zero!!";
}

// checks whether n1 - ( n1 % n2 ) is equal to ( n1 / n2 ) * n2
template< typename T >
void testArithmetics( HugeInteger< T > n1, HugeInteger< T > n2 )
{
   if( n2.isZero() )
   {
      cout << "divide by zero!!";
      return;
   }

   HugeInteger< T > n3 = n1 - ( n1 % n2 );
   HugeInteger< T > n4 = ( n1 / n2 ) * n2;

   cout << n1 << " - (" << n1 << " % " << n2 << ") == " << n3;
   cout << "\n(" << n1 << " / " << n2 << ") * " << n2 << " == " << n4;

   if( n3 == n4 ) // n1 - ( n1 % n2 ) == ( n1 / n2 ) * n2
      cout << "\nBingo! They are equal.";
   else
      cout << "\nGee!! They are not equal.";
   cout << endl;
}