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


String::String(const String &str)
{
	//get size and capacity from source string
	size = str.size;
	capacity = str.capacity;
	//allocate memory
	sPtr = new char[capacity];
	
	//copy string from source
	memcpy(sPtr, str.sPtr, size);
}

void String::resize(unsigned int n)
{
	//if n > cpapcity, call reserver to re-allocate memory
	if (n > capacity)
	{
		reserve(n);
	}

	//fill empty character
	for (unsigned int i = size; i < n; i++)
	{
		sPtr[i] = '\0';
	}
	size = n;
}

void String::reserve(unsigned int n)
{
	//if n > capacity, re-allocate memory
	if (n > capacity)
	{
		//re-allocate memory
		char *tempPtr = sPtr;
		capacity = (n / 16) * 16 + 15;
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
	//setting size and capacity
	size = last - first;
	capacity = (size / 16) * 16 + 15;
	//allocate memory
	sPtr = new char[capacity];
	//copy string from source
	memcpy(sPtr, first, size);
	return *this;
}

String& String::erase(unsigned int pos, unsigned int len)
{
	//start from pos to end	
	for (unsigned int i = pos; i + len < size; i++)
	{
		//move character to overwrite character which will be erase
		sPtr[i] = sPtr[i + len];
	}

	//cuont new size
	size = (len > size - pos) ? pos : size - len;

	return *this;
}

char* String::erase(char *first, char *last)
{
	//i is mean the offset form first, and should not grater the offset
	//from sPtr
	for (unsigned int i = 0; i < size - (first - sPtr); i++)
	{
		*(first + i) = *(last + i);
	}
	//count size
	size = (last - sPtr > size) ? first - sPtr : size - (last - first);
	return first;
}

unsigned int String::find(char c, unsigned int pos) const
{
	//const placed on tail of function is mean:
	//this function can NOT modify any memeber variable of itself
	//and const object only can call const function

	//start from pos
	for (unsigned int i = pos; i < size; i++)
	{
		//if find character return character position
		if (sPtr[i] == c)
			return i;
	}

	return npos;

}

String String::substr(unsigned int pos, unsigned int len) const
{
	//const placed on tail of function is mean:
	//this function can NOT modify any memeber variable of itself
	//and const object only can call const function
	if (len <= size - pos)
		return *(new String(sPtr + pos, len));
	else
		return *(new String(sPtr + pos, size - pos));
}