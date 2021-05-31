// dictionary.cpp
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
#include "dictionary.h"

void Dictionary::add( Entry & pEntry )
{
	mDictionary.insert( pEntry );	
}

void Dictionary::display()
{
unsigned counter=0;

	for ( mIter=mDictionary.begin(); mIter!=mDictionary.end(); mIter++ )
	{
		cout << ++counter << ':';
		cout << '[' << (*mIter).first << ']' << ',' << '[' << (*mIter).second << ']' << endl;
	}
}

unsigned Dictionary::size()
{
	return (unsigned)mDictionary.size();
}

bool Dictionary::contains( string & pSearchString )
{
	mIter=mDictionary.find( pSearchString );
	return mIter!=mDictionary.end();
}

void Dictionary::setToStart()
{// point at first pair
	mIter = mDictionary.begin();
}

bool Dictionary::hasData()
{// check that it is pointing at a pair
	return mIter!=mDictionary.end();
}

Dictionary::Entry Dictionary::currentData()
{// return current pair of strings
	return (*mIter);
}

void Dictionary::clear()
{// empty the mDictionary
	mDictionary.clear();
}

string Dictionary::meaning()
{// return current meaning
	return mIter->second;
}

string Dictionary::word()
{// return current word
	return mIter->first;
}

void Dictionary::next()
{// point to next pair
	if ( hasData() )
	{// then try to point at the next data pair
		mIter++;
	}
}


string Dictionary::string1()
{
	if (hasData())
	{
		return (*mIter1);
	}
	else
	{
		return "";
	}
}

string Dictionary::string2()
{
	if (hasData())
	{
		return (*mIter2);
	}
	else
	{
		return "";
	}
}



void Dictionary::load( const string & filename )
{
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
				inputLineCopy = removePunctuation( inputLineCopy, ",'" );		// remove string quotes
				tokenize(inputLineCopy, tokens, "," );						// break into the two components
				if ( tokens.size()==2 )
				{// then we have something sensible
					add(Dictionary::Entry( trimSpace(tokens[0]), trimSpace(tokens[1])) );// store without leading and trailing space
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

void Dictionary::save( const string & filename )
{
ofstream fOut;

	fOut.open(filename.c_str());
	if ( fOut.good() )
	{// then use it

		setToStart();
		while ( hasData() )
		{
			fOut << '\"' << word() << "\",\t\t\"" << meaning() << '\"' << endl;
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
