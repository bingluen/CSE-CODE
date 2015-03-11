// String class definition.
#ifndef STRING_H
#define STRING_H

class String 
{
public:
   static const unsigned int npos = -1; // the maximum unsigned int value that is equal to 4294967295

   String( const char *s = "", unsigned int n = npos );
   // Copies the first n characters from the array of characters pointed by s.

   String( const String &str ); // Constructs a copy of str.

   ~String(); // Destroys the string object.

   char* begin(); // Returns an pointer pointing to the first character in the string.
                  // If the string is empty, the returned pointer shall not be dereferenced.

   char* end(); // Returns an pointer pointing to the past-the-end character of the string.
                // The past-the-end character is a theoretical character that
                // would follow the last character in the string. It shall not be dereferenced.

   unsigned int getSize() const; // Returns the number of characters in the string.

   void resize( unsigned int n );
   // Resizes the string to a length of n characters.
   // If n is smaller than the current string length,
   // the current value is shortened to its first n character, removing the characters beyond the nth.
   // If n is greater than the current string length,
   // the current content is extended by inserting at the end as many characters as needed to reach a size of n.
   // The new elements are initialized as copies of null characters.

   unsigned int getCapacity() const;
   // Returns the size of the storage space currently allocated for the string, expressed in terms of bytes.

   void reserve( unsigned int n = 0 );
   // Requests that the string capacity be enough to contain n characters.
   // If n is greater than the current string capacity,
   // the function causes the container to increase its capacity to n characters (or greater).
   // In all other cases, the function call does not cause a reallocation and
   // the string capacity is not affected.

   void clear(); // Erases the contents of the string, which becomes an empty string
                 // (with a length of 0 characters).

   char& back(); // Returns a reference to the last character of the string.
                 // This function shall not be called on empty strings.

   char& front(); // Returns a reference to the first character of the string.
                  // This function shall not be called on empty strings.

   String& assign( char *first, char *last );
   // Copies the sequence of characters in the range [first,last), in the same order. Returns *this

   String& erase( unsigned int pos = 0, unsigned int len = npos );
   // Erases the portion of the string value that begins at the character position pos and spans len characters
   // (or until the end of the string, if either the content is too short or if len is string::npos).
   // Returns *this

   char* erase( char *first, char *last ); 
   // Erases the sequence of characters in the range [first,last).
   // This effectively reduces the container size by the number of elements removed.
   // Relocates all the characters after the segment erased to their new positions.
   // Returns a pointer referring to the character that now occupies the position of the first character erased,
   // or string::end if no such character exists.

   unsigned int find( char c, unsigned int pos = 0 ) const;
   // Searches the string for the first occurrence of the character specified by its arguments.
   // When pos is specified, the search only includes characters at or after position pos.
   // Returns the position of the first match. If no matches were found, the function returns string::npos.

   String substr( unsigned int pos = 0, unsigned int len = npos ) const;
   // Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
   // The substring is the portion of the object that starts at character position pos and spans len characters
   // (or until the end of the string, whichever comes first).

   void display(); // Displays all characters in the string.
private:
   unsigned int size; // the number of characters in the string
                      // This is the number of actual objects held in the string,
                      // which is not necessarily equal to its storage capacity.

   unsigned int capacity;
   // the size of the storage space currently allocated for the string, expressed in terms of elements.
   // This capacity is not necessarily equal to the string size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.

   char *sPtr;
   // points to a dynamically allocated array which is used to store the characters in the string
}; // end class String

#endif