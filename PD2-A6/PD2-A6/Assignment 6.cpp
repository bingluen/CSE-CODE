// HugeInteger test program.
#include <iostream>
#include "HugeInteger.cpp" // include definition of class HugeInteger 
#include "Vector.cpp" // include definition of class Vector 
#include "ProductTable.h" // include definition of class ProductTable< T >

template< typename T >
void loadTwoHugeIntegers( HugeInteger< T > &n1, HugeInteger< T > &n2 );

int enterChoice();

int main()
{
   HugeInteger< unsigned int > n1;
   HugeInteger< unsigned int > n2;

   loadTwoHugeIntegers( n1, n2 );

   int choice = enterChoice();

   switch ( choice )
   {
   case 0:
      cout << "n1                  : " << n1 << endl;
      cout << "n2 before assignment: " << n2 << endl;
      n2 = n1;
      cout << "n2  after assignment: " << n2 << endl << endl;
      break;
   case 1:
      if ( n1 == n2 )
         cout << n1 << " == " << n2 << endl << endl;
      break;
   case 2:
      if ( n1 != n2 )
         cout << n1 << " != " << n2 << endl << endl;
      break;
   case 3:
      if ( n1 < n2 )
         cout << n1 << " < " << n2 << endl << endl;
      break;
   case 4:
      if ( n1 > n2 )
         cout << n1 << " > " << n2 << endl << endl;
      break;
   case 5:
      if ( n1 <= n2 )
         cout << n1 << " <= " << n2 << endl << endl;
      break;
   case 6:
      if ( n1 >= n2 )
         cout << n1 << " >= " << n2 << endl << endl;
      break;
   case 7:
      cout << n1 << " + " << n2 << " == " << n1 + n2 << endl << endl;
      break;
   case 8:
      if ( n1 >= n2 )
         cout << n1 << " - " << n2 << " == " << n1 - n2 << endl << endl;
      break;
   case 9:
      cout << n1 << " * " << n2 << " == " << n1 * n2 << endl << endl;
      break;
   case 10:
      if ( !n2.zero() )
         cout << n1 << " / " << n2 << " == " << n1 / n2 << endl << endl;
      break;
   case 11:
      if ( !n2.zero() )
         cout << n1 << " % " << n2 << " == " << n1 % n2 << endl << endl;
      break;
   case 12:
      if ( !n2.zero() ) // Note that n1 - ( n1 % n2 ) must be equal to ( n1 / n2 ) * n2
      {
         cout << n1 << " - ( " << n1 << " % " << n2 << " ) == " << n1 - (n1 % n2) << endl << endl;
         cout << "( " << n1 << " / " << n2 << " ) * " << n2 << " == " << (n1 / n2) * n2 << endl << endl;
      }
      break;
   case 13:
      cout << "  n1: " << n1 << endl;
      cout << "++n1: " << ++n1 << endl;
      cout << "  n1: " << n1 << endl << endl;
      break;
   case 14:
      cout << "  n1: " << n1 << endl;
      cout << "n1++: " << n1++ << endl;
      cout << "  n1: " << n1 << endl << endl;
   } // end switch

   system( "pause" );
} // end main

template< typename T >
void loadTwoHugeIntegers( HugeInteger< T > &n1, HugeInteger< T > &n2 )
{
   // ifstream constructor opens the file
   ifstream inFile( "hugeIntegers.txt", ios::in );

   // exit program if ifstream could not open file
   if ( !inFile )
   {
      cout << "File could not be opened" << endl;
      system("pause");
      exit(1);
   }

   n1.load( inFile );
   n2.load( inFile );

   inFile.close();
}

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
   } while ((menuChoice < 0) || (menuChoice >= 15));
   cout << endl;

   return menuChoice;
} // end function enterChoice