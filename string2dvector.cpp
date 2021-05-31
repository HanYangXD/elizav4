// string2dvector.cpp
// v1.2
// PWM
// 21-feb-2006

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Project header files
#include "string2dvector.h"

void String2DVector::add( string & ps1, string & ps2)
{
	mString1.push_back( ps1 );	
	mString2.push_back( ps2 );	
}

void String2DVector::display()
{
unsigned counter=0;

	for ( mIter1=mString1.begin(), mIter2=mString2.begin(); mIter1!=mString1.end(); mIter1++, mIter2++ )
	{
		cout << ++counter << ':';
		cout << '[' << (*mIter1) << ']' << ',' << '[' << (*mIter2) << ']' << endl;
	}
}

unsigned String2DVector::size()
{
	return (unsigned)mString2.size();
}

string String2DVector::string1( )
{
	if ( hasData() )
	{
		return (*mIter1);
	}
	else
	{
		return "";
	}
}

string String2DVector::string2( )
{
	if ( hasData() )
	{
		return (*mIter2);
	}
	else
	{
		return "";
	}
}

void String2DVector::setToStart()
{// point at first pair
	mIter1 = mString1.begin();
	mIter2 = mString2.begin();
}

bool String2DVector::hasData()
{// check that it is pointing at a pair
	return mIter1!=mString1.end();
}

void String2DVector::clear()
{// empty the dictionary
	mString1.clear();
	mString2.clear();
	mIter1 = mString1.end();
	mIter2 = mString2.end();
}

void String2DVector::next()
{// point to next pair
	if ( hasData() )
	{// then try to point at the next data pair
		mIter1++;
		mIter2++;
	}
}


void String2DVector::load( const string & filename )
{// this is assuming that it is reading a pair of strings each enclosed in quote characters
ifstream fIn;
string inputLine;
string inputLineCopy;
vector <string> tokens;

	fIn.open( filename.c_str() );
	if ( fIn.good() )
	{// use it
		readLine( fIn, inputLine );		// read ahead one line
		while ( fIn.good() )
		{
			inputLineCopy = trimSpace(inputLine);
			if ( (inputLineCopy.size()>0) && (inputLineCopy.substr(0,2)!="//" ) )
			{// then use the line
				stringTokenize(inputLineCopy, tokens);						// break into the two components
				if ( tokens.size()==2 )
				{// then we have something sensible
					add( trimSpace(tokens[0]), trimSpace(tokens[1]) );// store without leading and trailing space
				}
				else
				{// moan! we don't have just two strings separated by a comma
					cout << "WARNING: ignoring the following line that does not have two comma separated strings" << endl;
					cout << "Output:" << inputLineCopy << endl;
				}
			}
			else
			{// ignoring a blank or comment line
			}

			readLine( fIn, inputLine );	// read next line
		}
		fIn.close();

	}
	else
	{// moan!
		cout << "ERROR: unable to open file: " << filename << endl;
	}
	fIn.clear(0);	// reset error flag after processing

}

void String2DVector::save( const string & filename )
{
ofstream fOut;

	fOut.open(filename.c_str());
	if ( fOut.good() )
	{// then use it

		setToStart();
		while ( hasData() )
		{
			fOut << '\"' << string1() << "\",\t\t\"" << string2() << '\"' << endl;
			next();
		}
		fOut.close();
	}
	else
	{// moan!
		cout << "ERROR: unable to open file " << filename << endl;
	}
	fOut.clear(0);	// reset error flag after processing
}
