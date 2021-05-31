// lex.cpp
// v1.0
// PWM
// 31-10-2006

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
#include "lex.h"

static string PartOfSpeechNames[] =
{
	"adjective", 
	"adjective/verb", 
	"adverb", 
	"adverb/verb", 
	"article", 
	"conjunction",
	"interjection", 
	"noun", 
	"noun/adjective", 
	"noun/verb", 
	"preposition", 
	"pronoun",
	"verb", 
	"possessive pronoun/pronoun",	// (e.g. "his")
	"adjective/pronoun",			// (e.g. this, that)
	"possessive pronoun",			// (e.g. my, her, your, our, their, its)
	"X category",					// don't care category --added X category for "not" so it will not be an adverb",
	"preposition/adverb"			// (e.g. aboard, above, around, as, before, below)
};

static string PartOfSpeechIndex="JjAaBCINdnPOVqoQXp";

string Lex::partOfSpeech( string pMeaning )
{
size_t index;
string search;
string reply;

	search = pMeaning[PARTOFSPEECH];

	index = PartOfSpeechIndex.find( search );
	if ( (index!=string::npos) && ( index<18 ) )
	{// then we found a match
		reply = PartOfSpeechNames[index];
		if ( pMeaning[PAST]=='1' )
		{
			reply = reply + " past tense";
		}
		if ( pMeaning[NEGATIVE]=='1' )
		{
			reply = reply + " negative";
		}
		if ( pMeaning[TOBE]=='1' )
		{
			reply = reply + " \"to be\"";
		}
		if ( pMeaning[ING]=='1' )
		{
			reply = reply + " gerund";
		}
		if ( pMeaning[AUX]=='1' )
		{
			reply = reply + " auxilliary";
		}
	}
	else
	{
		reply = "unknown";
	}
	return reply;
		
}


void Lex::add( Entry & pEntry )
{
	mLex.insert( pEntry );	
}

void Lex::display()
{
unsigned counter=0;

	for ( mIter=mLex.begin(); mIter!=mLex.end(); mIter++ )
	{
		cout << ++counter << ':';
		cout << '[' << (*mIter).first << ']' << ',' << '[' << (*mIter).second << ']' << endl;
	}
}

unsigned Lex::size()
{
	return (unsigned)mLex.size();
}

bool Lex::contains( string & pSearchString )
{
	mIter=mLex.find( pSearchString );
	return mIter!=mLex.end();
}

void Lex::setToStart()
{// point at first pair
	mIter = mLex.begin();
}

bool Lex::hasData()
{// check that it is pointing at a pair
	return mIter!=mLex.end();
}

Lex::Entry Lex::currentData()
{// return current pair of strings
	return (*mIter);
}

void Lex::clear()
{// empty the mLex
	mLex.clear();
}

string Lex::meaning()
{// return current meaning
	return mIter->second;
}

string Lex::word()
{// return current word
	return mIter->first;
}

void Lex::next()
{// point to next pair
	if ( hasData() )
	{// then try to point at the next data pair
		mIter++;
	}
}


void Lex::load( const string & filename )
{
ifstream fIn;
string inputLine;
string inputLineCopy;
string word;
string meaning;

	fIn.open( filename.c_str() );
	if ( fIn.good() )
	{// use it
		readLine( fIn, inputLine );		// read ahead one line
		while ( fIn.good() )
		{
			inputLineCopy = trimSpace(inputLine);
			if ( (inputLineCopy.size()>0) && (inputLineCopy.substr(0,2)!="//" ) )
			{// then use the line

				if ( inputLineCopy.size()>6 )
				{// then we have something sensible
					word = inputLineCopy.substr( 6 );
					meaning = inputLineCopy.substr( 0, 6 );
					add(Lex::Entry( word, meaning) );	// store without leading and trailing space
				}
				else
				{// moan! we don't have just two strings 
					cout << "WARNING: ignoring the following line that does not make sense" << endl;
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


