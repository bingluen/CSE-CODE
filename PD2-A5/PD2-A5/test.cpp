#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <ctime>

void random( int hugeInt[], int hugeIntSize );

bool equal( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

bool notEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

bool less( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

bool greater( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

bool lessEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

bool greaterEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size );

void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize );

void subtraction( int minuend[], int subtrahend[], int difference[],
                  int &minuendSize, int subtrahendSize, int &differenceSize );

void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize );

void printOperation( int hugeInt1[], int hugeInt2[], int hugeInt3[], char op,
                     int hugeInt1Size, int hugeInt2Size, int hugeInt3Size );

void print( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size, char string[] );

int main()
{
   unsigned int seed;
   cin >> seed;
   cout << endl;
   srand( seed );

   const int arraySize = 80;
   int hugeInt1[ arraySize ] = {0};
   int hugeInt1Size = 30 + rand() % 10;
   random( hugeInt1, hugeInt1Size );

   int hugeInt2[ arraySize ] = {0};
   int hugeInt2Size = ( hugeInt1Size / 2 ) + rand() % ( hugeInt1Size / 2 );
   random( hugeInt2, hugeInt2Size );

   if ( equal( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, "==" );

   if ( equal( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, "==" );

   if ( equal( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, "==" );

   if ( notEqual( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, "!=" );

   if ( notEqual( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, "!=" );

   if ( notEqual( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, "!=" );

   if ( less( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, "<" );

   if ( less( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, "<" );

   if ( less( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, "<" );

   if ( greater( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, ">" );

   if ( greater( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, ">" );

   if ( greater( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, ">" );
    
   if ( lessEqual( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, "<=" );

   if ( lessEqual( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, "<=" );
    
   if ( lessEqual( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, "<=" );
    
   if ( greaterEqual( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size ) )
      print( hugeInt1, hugeInt1, hugeInt1Size, hugeInt1Size, ">=" );
    
   if ( greaterEqual( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size ) )
      print( hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size, ">=" );

   if ( greaterEqual( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size ) )
      print( hugeInt2, hugeInt1, hugeInt2Size, hugeInt1Size, ">=" );

   int hugeInt3[ arraySize ] = {0};
   int hugeInt3Size;

   multiplication( hugeInt1, hugeInt2, hugeInt3, hugeInt1Size, hugeInt2Size, hugeInt3Size );

   printOperation( hugeInt1, hugeInt2, hugeInt3, '*', hugeInt1Size, hugeInt2Size, hugeInt3Size );

   addition( hugeInt1, hugeInt2, hugeInt3, hugeInt1Size, hugeInt2Size, hugeInt3Size );

   printOperation( hugeInt1, hugeInt2, hugeInt3, '+', hugeInt1Size, hugeInt2Size, hugeInt3Size );

   int hugeInt4[ arraySize ] = {0};
   int hugeInt4Size;

   subtraction( hugeInt3, hugeInt1, hugeInt4, hugeInt3Size, hugeInt1Size, hugeInt4Size );

   printOperation( hugeInt3, hugeInt1, hugeInt4, '-', hugeInt3Size, hugeInt1Size, hugeInt4Size );

   if( equal( hugeInt2, hugeInt4, hugeInt2Size, hugeInt4Size ) )
      print( hugeInt2, hugeInt4, hugeInt2Size, hugeInt4Size, "==" );
}

void random( int hugeInt[], int hugeIntSize )
{
   for( int i = 0; i < hugeIntSize - 1; i++ )
      hugeInt[i] = rand() % 10;
   hugeInt[ hugeIntSize - 1 ] = 1 + rand() % 9;
}

bool equal( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size != hugeInt2Size )
      return false;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
      if( hugeInt1[i] != hugeInt2[i] )
         return false;

   return true;
}

bool notEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size != hugeInt2Size )
      return true;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
      if( hugeInt1[i] != hugeInt2[i] )
         return true;

   return false;
}

bool less( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size < hugeInt2Size )
      return true;
   if( hugeInt1Size > hugeInt2Size )
      return false;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
   {
      if( hugeInt1[i] < hugeInt2[i] )
         return true;
      if( hugeInt1[i] > hugeInt2[i] )
         return false;
   }

   return false;
}

bool greater( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size > hugeInt2Size )
      return true;
   if( hugeInt1Size < hugeInt2Size )
      return false;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
   {
      if( hugeInt1[i] > hugeInt2[i] )
         return true;
      if( hugeInt1[i] < hugeInt2[i] )
         return false;
   }

   return false;
}

bool lessEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size < hugeInt2Size )
      return true;
   if( hugeInt1Size > hugeInt2Size )
      return false;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
   {
      if( hugeInt1[i] < hugeInt2[i] )
         return true;
      if( hugeInt1[i] > hugeInt2[i] )
         return false;
   }

   return true;
}

bool greaterEqual( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size )
{
   if( hugeInt1Size > hugeInt2Size )
      return true;
   if( hugeInt1Size < hugeInt2Size )
      return false;

   for( int i = hugeInt1Size - 1; i >= 0 ; i-- )
   {
      if( hugeInt1[i] > hugeInt2[i] )
         return true;
      if( hugeInt1[i] < hugeInt2[i] )
         return false;
   }

   return true;
}

void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize )
{
   sumSize = ( addendSize >= adderSize ) ? addendSize + 1 : adderSize + 1;

   for( int i = 0; i < addendSize; i++ )
      sum[ i ] = addend[ i ];

   for( int i = addendSize; i < sumSize; i++ )
      sum[i] = 0;

   for( int i = 0; i < adderSize; i++ )
      sum[ i ] += adder[ i ];

   for( int i = 0; i < sumSize - 1; i++ )
      if( sum[i] > 9 )
      {
         sum[i] -= 10;
         sum[i+1]++;
      }

   if( sum[ sumSize - 1 ] == 0 )
      sumSize--;
}

void subtraction( int minuend[], int subtrahend[], int difference[],
                  int &minuendSize, int subtrahendSize, int &differenceSize )
{
   for( int i = 0; i < subtrahendSize; i++ ) 
      difference[ i ] = minuend[ i ] - subtrahend[ i ];

   for( int i = subtrahendSize; i < minuendSize; i++ ) 
      difference[ i ] = minuend[ i ];

   differenceSize = minuendSize;
   for( int i = 0; i < differenceSize - 1; i++ )
      if( difference[i] < 0 )
      {
         difference[i] += 10;
         difference[i+1]--;
      }

   while( difference[ differenceSize - 1 ] == 0 && differenceSize > 0 )
      differenceSize--;
}

void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize )
{
   productSize = multiplicandSize + multiplierSize;
   for( int i = 0; i < productSize; i++ )
      product[i] = 0;

   for( int i = 0; i < multiplierSize; i++ )
      for( int j = 0; j < multiplicandSize; j++ )
         product[i+j] += ( multiplier[i] * multiplicand[j] );

   for( int i = 0; i < productSize - 1; i++ )
      if( product[ i ] >= 10 )
      {
         product[i+1] += ( product[i] / 10 );
         product[i] %= 10;
      }

   if( product[ productSize - 1 ] == 0 )
      productSize--;
}

void printOperation( int hugeInt1[], int hugeInt2[], int hugeInt3[], char op,
                     int hugeInt1Size, int hugeInt2Size, int hugeInt3Size )
{
   for( int i = hugeInt1Size - 1; i >= 0; i-- )
      cout << hugeInt1[i];

   cout << " " << op << " ";
   for( int i = hugeInt2Size - 1; i >= 0; i-- )
      cout << hugeInt2[i];

   cout << " == ";
   for( int i = hugeInt3Size - 1; i >= 0; i-- )
      cout << hugeInt3[i];
   cout << endl << endl;
}

void print( int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size, char string[] )
{
   for( int i = hugeInt1Size - 1; i >= 0; i-- )
      cout << hugeInt1[i];

   cout << " " << string << " ";

   for( int i = hugeInt2Size - 1; i >= 0; i-- )
      cout << hugeInt2[i];
   cout << endl << endl;
}