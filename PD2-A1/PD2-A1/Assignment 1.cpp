// HugeInteger test program.
#include <iostream>
#include "HugeInteger.h" // include definition of class HugeInteger

void loadTwoHugeIntegers( HugeInteger &n1, HugeInteger &n2 );
int enterChoice();
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

int main()
{
   HugeInteger n1;
   HugeInteger n2;

   loadTwoHugeIntegers( n1, n2 );

   void (*f[ 12 ])( HugeInteger, HugeInteger ) =
        { testEqual, testNotEqual, testLess, testGreater, testLessEqual, testGreaterEqual,
          testAdd, testSubtract, testMultiply, testDivide, testModulus, testArithmetics };

   int choice = enterChoice();

   ( *f[ choice ] )( n1, n2 ); // invoke the function at location choice in the array f

   system("pause");
} // end main

void loadTwoHugeIntegers( HugeInteger &n1, HugeInteger &n2 )
{
   // ifstream constructor opens the file
   ifstream inFile( "hugeIntegers.txt", ios::in );

   // exit program if ifstream could not open file
   if ( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   n1.load( inFile );
   n2.load( inFile );

   inFile.close();
}

int enterChoice()
{
   cout << "Enter your choice\n"
      << " 0 - test equal\n"
      << " 1 - test notEqual\n"
      << " 2 - test less\n"
      << " 3 - test greater\n"
      << " 4 - test lessEqual\n"
      << " 5 - test greaterEqual\n"
      << " 6 - test add\n"
      << " 7 - test subtract\n"
      << " 8 - test multiply\n"
      << " 9 - test divide\n"
      << "10 - test modulus\n"
      << "11 - test arithmetics\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while ( ( menuChoice < 0 ) || ( menuChoice >= 12 ) );
   cout << endl;

   return menuChoice;
} // end function displayMenu

void testEqual( HugeInteger n1, HugeInteger n2 )
{
   // tests for equality between n1 and n2 
   if ( n1.equal( n2 ) )
   { 
      n1.output();
      cout << " == ";
      n2.output();
      cout << "\n\n";
   }      
}

void testNotEqual( HugeInteger n1, HugeInteger n2 )
{
   // tests for inequality between n1 and n2 
   if ( n1.notEqual( n2 ) )
   { 
      n1.output();
      cout << " != ";
      n2.output();
      cout << "\n\n";
   }      
}

void testLess( HugeInteger n1, HugeInteger n2 )
{
   // tests for smaller number between n1 and n2
   if ( n1.less( n2 ) )
   {
      n1.output();
      cout << " < ";
      n2.output();
      cout << "\n\n";
   }
}

void testGreater( HugeInteger n1, HugeInteger n2 )
{
   // tests for greater number between n1 and n2 
   if ( n1.greater( n2 ) )
   {
      n1.output();
      cout << " > ";
      n2.output();
      cout << "\n\n";
   }
}

void testLessEqual( HugeInteger n1, HugeInteger n2 )
{
   // tests for smaller or equal number between n1 and n2
   if ( n1.lessEqual( n2 ) )
   {
      n1.output();
      cout << " <= ";
      n2.output();
      cout << "\n\n";
   }
}

void testGreaterEqual( HugeInteger n1, HugeInteger n2 )
{
   // tests for greater or equal number between n1 and n2
   if ( n1.greaterEqual( n2 ) )
   {
      n1.output();
      cout << " >= ";
      n2.output();
      cout << "\n\n";
   }
}

void testAdd( HugeInteger n1, HugeInteger n2 )
{
   n1.output();
   cout<< " + ";
   n2.output();
   cout << " == ";
   n1.add( n2 ).output(); // outputs n1 + n2
   cout << "\n\n";
}

void testSubtract( HugeInteger n1, HugeInteger n2 )
{
   if( n1.greaterEqual( n2 ) )
   {
      n1.output();
      cout<< " - ";
      n2.output();
      cout << " == ";
      n1.subtract( n2 ).output(); // outputs n1 - n2
      cout << "\n\n";
   }
}

void testMultiply( HugeInteger n1, HugeInteger n2 )
{
   n1.output();
   cout<< " * ";
   n2.output();
   cout << " == ";
   n1.multiply( n2 ).output(); // outputs n1 * n2
   cout << "\n\n";
}

void testDivide( HugeInteger n1, HugeInteger n2 )
{
   n1.output();
   cout<< " / ";
   n2.output();
   cout << " == ";
   n1.divide( n2 ).output(); // outputs n1 / n2
   cout << "\n\n";
}

void testModulus( HugeInteger n1, HugeInteger n2 )
{
   n1.output();
   cout<< " % ";
   n2.output();
   cout << " == ";
   n1.modulus( n2 ).output(); // outputs n1 % n2
   cout << "\n\n";
}

// checks whether n1 - ( n1 % n2 ) is equal to ( n1 / n2 ) * n2
void testArithmetics( HugeInteger n1, HugeInteger n2 )
{
   n1.output();
   cout << " - (";
   n1.output();
   cout << " % ";
   n2.output();
   cout << ") == ";
   n1.subtract( n1.modulus( n2 ) ).output(); // outputs n1 - ( n1 % n2 )
   
   cout << "\n\n(";
   n1.output();
   cout<< " / ";
   n2.output();
   cout << ") * ";
   n2.output();
   cout << " == ";
   n1.divide( n2 ).multiply( n2 ).output(); // outputs ( n1 / n2 ) * n2
   cout << "\n\n";

   // Note that n1 - ( n1 % n2 ) must be equal to ( n1 / n2 ) * n2
}
