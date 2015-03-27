// Identifier class member-function definitions.
#include <iostream>
using namespace std;
#include "Identifier.h" // Identifier class definition

char keywords[61][20] = { "auto", "break", "case", "char", "const", "continue", "default",
								  "do", "double", "else", "enum", "extern", "float", "for",
								  "goto", "if", "int", "long", "register", "return", "short",
								  "signed", "sizeof", "static", "struct", "switch", "typedef",
								  "union", "unsigned", "void", "volatile", "while", "bool",
								  "catch", "class", "const_cast", "delete", "dynamic_cast",
								  "explicit", "false", "friend", "inline", "mutable", "namespace",
								  "new", "operator", "private", "protected", "public",
								  "reinterpret_cast", "static_cast", "template", "this", "throw",
								  "true", "try", "typeid", "typename", "using", "virtual", "include" };

// default/conversion constructor
Identifier::Identifier( const char *s ) : String( s )
{
}

/* Assigment 5 - implement Identifier*/

const Identifier & Identifier::operator = (const String &right)
{
	// assignment operator
	String::operator=(right);

	return *this;
}

bool Identifier::keyword()
{
	// check if the current identifier is a C++ keyword

	for (size_t i = 0; i < 61; i++)
	{
		if (!strcmp(this->begin(), keywords[i]))
			return true;
	}

	return false;
}