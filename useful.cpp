// useful.cpp
// V1.0
// PWM
// 21-feb-2006

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Project header files
#include "useful.h"

void readLine( istream & in, string & s )
{// a function to replace getLine() because there was a bug in Visual Studio C++ 6 and you don't know whether
 // the patch was applied.
char c;

	s.erase();	// clear the old string

	c = in.get();		// read one character ahead
	while ( c!='\n' && in.good())
	{// not end of line
		s = s + c;		// add the string
		c = in.get();	// read the next character
	}
}


string lowercase( string & ps )
{// to force each character in the string to be lowercase
string s(ps);
unsigned i;

	for (i=0; i<s.length(); i++ )
	{
		s[i] = tolower(s[i]);	// tolower() from cctype
	}

	return s;					// return the address
}

string uppercase( string & ps )
{// to force each character in the string to be uppercase
string s(ps);
unsigned i;

	for (i=0; i<s.length(); i++ )
	{
		s[i] = toupper(s[i]);	// toupper() from cctype
	}

	return s;					// return the address
}

string trimSpace( string & ps )
{// remove leading and trailing space from a string
string str = ps;
string::size_type index;

   
   index = str.find_first_not_of(" \t\n");	// get index of first text

   if ( index!=string::npos )
   {// then we have something to process
		str.erase( 0, index );				// trim leading whitespace
 

	   // trim trailing whitespace
	   index = str.find_last_not_of(" \t\n");

	   if ( index!=string::npos )
	   {// then we have something to process
		   str.erase(index+1);
	   }
   }
   else
   {// assume the string is just white space
	   str.erase();
   }

   return str;

}


string spacePunctuation( string & strIn, char * ignore )
{// space out all the punctuation from the text apart from the characters in the ignore C-string
string strIgnore = ignore;

	return spacePunctuation( strIn, strIgnore );
}

string spacePunctuation( string & strIn )
{// space out all the punctuation from the text
string strEmpty;

	return spacePunctuation( strIn, strEmpty );
}

string spacePunctuation( string & strIn, string & ignore )
{// space out the punctuation from the text apart from the characters in the ignore string
unsigned i = 0;
string strOut;

	while ( i<strIn.length() )
	{
		if ( ispunct( strIn[i] ) && ((ignore.find(strIn[i])) == string::npos) )
		{
			strOut = strOut + ' ' + strIn[i] + ' ';
		}
		else
		{
			strOut = strOut + strIn[i];
		}
		i++;
	}
	return strOut;
}

string removePunctuation( string & strIn, char * ignore )
{// remove all the punctuation from the text apart from the characters in the ignore C-string
string strIgnore = ignore;

	return removePunctuation( strIn, strIgnore );
}

string removePunctuation( string & strIn )
{// remove  all the punctuation from the text
string strEmpty;

	return removePunctuation( strIn, strEmpty );
}

string removePunctuation( string & strIn, string & ignore )
{// remove the punctuation from the text apart from the characters in the ignore string
unsigned i = 0;
string strOut;

	while ( i<strIn.length() )
	{
		if ( !ispunct( strIn[i] ) || ((ignore.find(strIn[i])) != string::npos) )
		{// only copy non-punctuation characters or those fromtheignore set
			strOut = strOut + strIn[i];
		}
		else
		{// better put a space in
			strOut = strOut + ' ';
		}
		i++;
	}
	return strOut;
}

void tokenize(const string& str, vector<string>& tokens, const string& delimiters )
{// Create a vector of words from a string using the delimiters to separate the words. Note that
 // string::npos is a large number that indicates a string find operation has failed.

string::size_type lastPos;
string::size_type pos;

	tokens.clear();		// Make sure the vector is empty to start with

	// Find the first "word" (token)
	lastPos = str.find_first_not_of(delimiters, 0);		// Skip delimiters at beginning.
	pos     = str.find_first_of(delimiters, lastPos);	// Find first "non-delimiter".

    while ( (pos != string::npos) || (lastPos != string::npos) )
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Find the next word
        lastPos = str.find_first_not_of(delimiters, pos);		// Skip delimiters.
        pos		= str.find_first_of(delimiters, lastPos);		// Find next "non-delimiter"
    }

}

void stringTokenize(const string& str, vector<string>& tokens )
{// Create a vector of substrings from a string using quotes to separate the strings. Note that
 // string::npos is a large number that indicates a string find operation has failed.

string::size_type lastPos;
string::size_type pos;

	tokens.clear();		// Make sure the vector is empty to start with

	// Find the first "substring" (token)
	pos = str.find("\"", 0);
	while ( (pos != string::npos) )
	{// then we found a start of string

		lastPos = str.find("\"", pos+1);
		if ( lastPos!= string::npos)
		{// then we found an end of string
			// Found a token, add it to the vector.
			tokens.push_back(str.substr(pos+1, lastPos-pos-1));
		}
		// try to find the next start of string
		pos = str.find("\"", lastPos+1);
	}

}

void printTokens( vector<string>& tokens )
{// A debug function - so we can see what the program has made of the input line

	//cout << "Azile: I read this as: ";
	copy(tokens.begin(), tokens.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

}

void printTokens( vector<string>& tokens, char * separator )
{// A debug function - so we can see what the program has made of the input line

	//cout << "Azile: I read this as: ";
	copy(tokens.begin(), tokens.end(), ostream_iterator<string>(cout, separator));
	cout << endl;

}
void asciiPrintTokens( vector<string>& tokens )
{// A debug function - so we can see what the program has made of the input line
unsigned ti;

	//cout << "Azile: ascii print: ";

	for (ti = 0; ti< tokens.size(); ti++ )
	{
		cout << tokens[ti] << "[" << tokens[ti].size() << "]" << ' ';
	}
	cout << endl;

}

bool isString( string & str, const string strArray[], unsigned size )
{// A boolean function indicating whether str is in the array of strings.
 // See convertString()

unsigned i;


    for (i=0; i<size; i++)
    {
        if ( uppercase(str) == strArray[i] )
        {// we have a match - so stop searching
            break;
        }
    }
    // return TRUE or FALSE
    return ( i<size );

}

unsigned convertString( string & str, const string strArray[], unsigned size )
{// A function that returns the index of str in the array of strings. It assumes that the
 // str string is known to be in the string array - so isString() should have been called first.

unsigned i;

    for (i=0; i<size; i++)
    {
        if ( uppercase(str) == strArray[i] )
        {// we have a match - so stop searching
            break;
        }
    }

    // return the index
    return i;

}

