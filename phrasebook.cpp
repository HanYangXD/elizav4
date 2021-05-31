// phrasebook.cpp
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
#include "phrasebook.h"

void Phrasebook::add( Entry & pEntry )
{
	mPhrasebook.insert( pEntry );	
}

void Phrasebook::display()
{
unsigned counter=0;

	for ( mIter=mPhrasebook.begin(); mIter!=mPhrasebook.end(); mIter++ )
	{
		cout << ++counter << ':';
		cout << '[' << (*mIter).first << ']' << ',' << '[' << (*mIter).second << ']' << endl;
	}
}

unsigned Phrasebook::size()
{
	return (unsigned)mPhrasebook.size();
}

bool Phrasebook::contains( string & pSearchString )
{
	mIter=mPhrasebook.find( pSearchString );
	return mIter!=mPhrasebook.end();
}

void Phrasebook::setToStart()
{// point at first pair
	mIter = mPhrasebook.begin();
}

void Phrasebook::setToStart( string & pKeyword)
{// point at first pair
	mIter = mPhrasebook.lower_bound( pKeyword);
}

bool Phrasebook::hasData()
{// check that it is pointing at a pair
	return mIter!=mPhrasebook.end();
}

bool Phrasebook::hasData( string & pKeyword )
{// check that it is pointing at a pair
	return ((mIter!= mPhrasebook.end()) && (mIter!=mPhrasebook.upper_bound( pKeyword )) );
}

Phrasebook::Entry Phrasebook::currentData()
{// return current pair of strings
	return (*mIter);
}

void Phrasebook::clear()
{// empty the mPhrasebook
	mPhrasebook.clear();
}

string Phrasebook::phrase()
{// return current phrase
	return mIter->second;
}

string Phrasebook::keyword()
{// return current keyword
	return mIter->first;
}

void Phrasebook::next()
{// point to next pair
	if ( hasData() )
	{// then try to point at the next data pair
		mIter++;
	}
}

void Phrasebook::next( string & pKeyword )
{// point to next pair
	if ( hasData() && (mIter!=mPhrasebook.upper_bound( pKeyword )) )
	{// then try to point at the next data pair
		mIter++;
	}
}

void Phrasebook::extract( string pKeyword, vector <string> & pPhrases )
{

	for (mIter = mPhrasebook.lower_bound(pKeyword); mIter != mPhrasebook.upper_bound(pKeyword); mIter++) 
	{
		pPhrases.push_back( phrase() );
    }

}



void Phrasebook::load( const string & filename )
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
				stringTokenize(inputLineCopy, tokens);						// break into the two components
				if ( tokens.size()==2 )
				{// then we have something sensible
					add(Phrasebook::Entry( trimSpace(tokens[0]), trimSpace(tokens[1])) );// store without leading and trailing space
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

void Phrasebook::save( const string & filename )
{
ofstream fOut;

	fOut.open(filename.c_str());
	if ( fOut.good() )
	{// then use it

		setToStart();
		while ( hasData() )
		{
			fOut << '\"' << keyword() << "\",\t\t\"" << phrase() << '\"' << endl;
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
