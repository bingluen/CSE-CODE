// Member-function definitions for class String.
#include <iostream>
using namespace std;
#include "String.h" // include definition of class String 

// default constructor
String::String( const char *s, unsigned int n )
   : size( strlen( s ) )
{
   if( n < size )
      size = n;
   capacity = ( size / 16 ) * 16 + 15;

   sPtr = new char[ capacity ];

   if( size > 0 )
      for( unsigned int i = 0; i < size; i++ )
         sPtr[ i ] = s[ i ];
}

// destructor
String::~String()
{
   delete [] sPtr;
} // end destructor

char* String::begin()
{
   return sPtr;
}

char* String::end()
{
   return sPtr + size;
}

unsigned int String::getSize() const
{
   return size;
}

unsigned int String::getCapacity() const
{
   return capacity;
}

void String::clear()
{
   size = 0;
}

char& String::back()
{
   return sPtr[ size - 1 ];
}

char& String::front()
{
   return sPtr[0];
}

void String::display()
{
   for( unsigned int i = 0; i < size; i++ )
      cout << sPtr[i];
   cout << endl << endl;
}

void String::resize(unsigned int n)
{
	//if n > cpapcity, call reserver to re-allocate memory
	if (n > capacity)
	{
		reserve(n);
	}
	size = n;
}

void String::reserve(unsigned int n = 0)
{
	//if n > capacity, re-allocate memory
	if (n > capacity)
	{
		//re-allocate memory
		char *tempPtr = sPtr;
		capacity = (size / 16) * 16 + 15;
		sPtr = new char[capacity];

		//copy data to new allocate memory from source
		for (unsigned int i = 0; i < size; i++)
		{
			sPtr[i] = tempPtr[i];
		}

		//free memory
		delete[] tempPtr;
	}
}

String& String::assign(char *first, char *last)
{
	size = last - first;
}

String& String::erase(unsigned int pos = 0, unsigned int len = npos)
{

}

char* String::erase(char *first, char *last)
{

}

unsigned int String::find(char c, unsigned int pos = 0) const
{
	//const placed on tail of function is mean:
	//this function can NOT modify any memeber variable of itself
	//only call by const object

}

String String::substr(unsigned int pos = 0, unsigned int len = npos) const
{
	//const placed on tail of function is mean:
	//this function can NOT modify any memeber variable of itself
	//only call by const object
}