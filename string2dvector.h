// string2dvector.h
// v1.1
// PWM
// 21-feb-2006

#ifndef STRING2DVECTOR_H
#define STRING2DVECTOR

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <string>
#include <vector>
using std::string;
using std::vector;

// Project header files
#include "useful.h"

class String2DVector
{
private:
	vector <string> mString1;					// create empty string1 vector
	vector <string> mString2;					// create empty string2 vector
	vector <string>::iterator mIter1;
	vector <string>::iterator mIter2;
	
public:
	void		add( string & ps1, string & ps2 );	// add a pair of strings
	void		display();							// debugging dump of data
	unsigned	size();								// number of pairs of strings
	string		string1( );							// return the matching string in string1
	string		string2( );							// return the matching string in string2
	void		setToStart();						// point at first pair
	bool		hasData();							// check that it is pointing at a pair
	void		next();								// point to next pair
	void		clear();							// clear the dictionary map
	void		load( const string & filename );	// load from file
	void		save( const string & filename );	// save to file
};

// Function prototypes

#endif
