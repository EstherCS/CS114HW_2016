// HugeInteger test program.
#include <iostream>
#include <fstream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

int enterChoice();

void loadTwoHugeIntegers( HugeInteger &n1, HugeInteger &n2 );

void loadOneHugeInteger( HugeInteger &n1 );

void testAssignment( HugeInteger n1, HugeInteger n2 );

void testEqual( HugeInteger n1, HugeInteger n2 );

void testNotEqual( HugeInteger n1, HugeInteger n2 );

void testLess( HugeInteger n1, HugeInteger n2 );

void testGreater( HugeInteger n1, HugeInteger n2 );

void testLessEqual( HugeInteger n1, HugeInteger n2 );

void testGreaterEqual( HugeInteger n1, HugeInteger n2 );

void testAdd( HugeInteger n1, HugeInteger n2 );

void testSubtract( HugeInteger n1, HugeInteger n2 );

void testMultiply( HugeInteger n1, HugeInteger n2 );

void testDivide( HugeInteger n1, HugeInteger n2 );

void testModulus( HugeInteger n1, HugeInteger n2 );

void testArithmetics( HugeInteger n1, HugeInteger n2 );

void testPreincrement( HugeInteger n1 );

void testPostincrement( HugeInteger n1 );

int main()
{
   HugeInteger n1;
   HugeInteger n2;

   void( *array1[ 13 ] )( HugeInteger, HugeInteger ) =
   { testAssignment, testEqual, testNotEqual, testLess, testGreater, testLessEqual, testGreaterEqual,
   testAdd, testSubtract, testMultiply, testDivide, testModulus, testArithmetics };
   void( *array2[ 15 ] )( HugeInteger ) = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, testPreincrement, testPostincrement };

   int choice = enterChoice();

   if( choice <= 12 ) // test binary operators
   {
      loadTwoHugeIntegers( n1, n2 );
      ( *array1[ choice ] )( n1, n2 ); // invoke the function at location choice in array1
   }
   else // test unary operators
   {
      loadOneHugeInteger( n1 );
      ( *array2[ choice ] )( n1 ); // invoke the function at location choice in array2
   }

   cout << endl << endl;

   system( "pause" );
} // end main

int enterChoice()
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
      << "12 - test arithmetics\n"
      << "13 - test prefix increment\n"
      << "14 - test postfix increment\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 0 ) || ( menuChoice > 14 ) );
   cout << endl;

   return menuChoice;
} // end function enterChoice

void loadTwoHugeIntegers( HugeInteger &n1, HugeInteger &n2 )
{
   // ifstream constructor opens the file
   ifstream inFile( "hugeIntegers8.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   char digit;
   Vector vector1, vector2;
   
   while( ( digit = inFile.get() ) != '\n' )
      if( digit != ' ' )
         vector1.push_back( digit - '0' );
   // the leftmost digit (i.e., the most significant digit) will be put into vector1[ 0 ]

   while( ( digit = inFile.get() ) != '\n' )
      if( digit != ' ' )
         vector2.push_back( digit - '0' );
   // the leftmost digit (i.e., the most significant digit) will be put into vector2[ 0 ]

   n1.convert( vector1 );
   n2.convert( vector2 );

   inFile.close();
}

void loadOneHugeInteger( HugeInteger &n1 )
{
   // ifstream constructor opens the file
   ifstream inFile( "hugeIntegers8.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   char digit;
   Vector vector;

   while( ( digit = inFile.get() ) != '\n' )
      if( digit != ' ' )
         vector.push_back( digit - '0' );
   // the leftmost digit (i.e., the most significant digit) will be put into numericString[ 0 ]

   n1.convert( vector );

   inFile.close();
}

void testAssignment( HugeInteger n1, HugeInteger n2 )
{
   cout << "n1                  : " << n1 << endl;
   cout << "n2 before assignment: " << n2 << endl;
   n2 = n1;
   cout << "n2  after assignment: " << n2;
}

void testEqual( HugeInteger n1, HugeInteger n2 )
{
   if( n1 == n2 )
      cout << n1 << " == " << n2;
   else
      cout << n1 << " != " << n2;
}

void testNotEqual( HugeInteger n1, HugeInteger n2 )
{
   if( n1 != n2 )
      cout << n1 << " != " << n2;
   else
      cout << n1 << " == " << n2;
}

void testLess( HugeInteger n1, HugeInteger n2 )
{
   if( n1 < n2 )
      cout << n1 << " < " << n2;
   else
      cout << n1 << " >= " << n2;
}

void testGreater( HugeInteger n1, HugeInteger n2 )
{
   if( n1 > n2 )
      cout << n1 << " > " << n2;
   else
      cout << n1 << " <= " << n2;
}

void testLessEqual( HugeInteger n1, HugeInteger n2 )
{
   if( n1 <= n2 )
      cout << n1 << " <= " << n2;
   else
      cout << n1 << " > " << n2;
}

void testGreaterEqual( HugeInteger n1, HugeInteger n2 )
{
   if( n1 >= n2 )
      cout << n1 << " >= " << n2;
   else
      cout << n1 << " < " << n2;
}

void testAdd( HugeInteger n1, HugeInteger n2 )
{
   cout << n1 << " + " << n2 << " == " << n1 + n2;
}

void testSubtract( HugeInteger n1, HugeInteger n2 )
{
   if( n1 < n2 )
      cout << n1 << " - " << n2 << " == -" << n2 - n1;
   else
      cout << n1 << " - " << n2 << " == " << n1 - n2;
}

void testMultiply( HugeInteger n1, HugeInteger n2 )
{
   cout << n1 << " * " << n2 << " == " << n1 * n2;
}

void testDivide( HugeInteger n1, HugeInteger n2 )
{
   if( !n2.isZero() )
      cout << n1 << " / " << n2 << " == " << n1 / n2;
   else
      cout << "divide by zero!!";
}

void testModulus( HugeInteger n1, HugeInteger n2 )
{
   if( !n2.isZero() )
      cout << n1 << " % " << n2 << " == " << n1 % n2;
   else
      cout << "divide by zero!!";
}

// checks whether n1 - ( n1 % n2 ) is equal to ( n1 / n2 ) * n2
void testArithmetics( HugeInteger n1, HugeInteger n2 )
{
   if( n2.isZero() )
   {
      cout << "divide by zero!!";
      return;
   }

   HugeInteger n3 = n1 - ( n1 % n2 );
   HugeInteger n4 = ( n1 / n2 ) * n2;

   cout << n1 << " - (" << n1 << " % " << n2 << ") == " << n3;
   cout << "\n\n(" << n1 << " / " << n2 << ") * " << n2 << " == " << n4;

   if( n3 == n4 ) // n1 - ( n1 % n2 ) == ( n1 / n2 ) * n2
      cout << "\n\nBingo! They are equal.";
   else
      cout << "\n\nGee!! They are not equal.";

}

void testPreincrement( HugeInteger n1 )
{
   cout << "  n1: " << n1 << endl;
   cout << "++n1: " << ++n1 << endl;
   cout << "  n1: " << n1;
}

void testPostincrement( HugeInteger n1 )
{
   cout << "  n1: " << n1 << endl;
   cout << "n1++: " << n1++ << endl;
   cout << "  n1: " << n1;
}