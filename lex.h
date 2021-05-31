// lex.h
// v1.0
// PWM
// 31-Oct-2006
// NOTE:
// The LEX dictionary was compiled by Dave Keiras, of the University of
// Michigan, who has graciously made it available in the public domain.
// 1980
//                           Format  of  LEX:
//                     -------------------------------
//                    Col       Data................
//                     1        part of speech
//                     2        past participle flag
//                     3        negative flag
//                     4        to be flag
//                     5        verb + ing flag
//                     6        aux flag
//                     7-26     word
//
//                          Parts of Speech Key
//                         --------------------
//(J)  adjective           (j)  adjective/verb           (A)  adverb
//(a)  adverb/verb         (B)  article                  (C)  conjunction
//(I)  interjection        (N)  noun                     (d)  noun/adjective
//(n)  noun/verb           (P)  preposition              (O)  pronoun
//(V)  verb                (q)  possessive pronoun/pronoun (e.g. "his")
//(o)  adjective/pronoun (e.g. this, that)
//(Q)  possessive pronoun (e.g. my, her, your, our, their, its)
//(X)  don't care category
//     --added X category for "not" so it will not be an adverb
//(p)  preposition/adverb (e.g. aboard, above, around, as, before, below)

#ifndef LEX_H
#define LEX_H

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <string>
#include <vector>
#include <map>

// Project header files
#include "useful.h"

class Lex
{
private:
	map <string,string> mLex;				// create empty dictionary mapping
	map<string,string>::iterator mIter;
	enum { PARTOFSPEECH, PAST, NEGATIVE, TOBE, ING, AUX };
	
public:
	typedef		pair<string,string> Entry;			// entry holds the lex pair
	void		add( Entry & pEntry );				// add a lex pair of strings
	void		display();							// debugging dump of data
	unsigned	size();								// number of lex items
	bool		contains( string & pSearchString );	// check for entry
	string		meaning();							// return current meaning
	string		word();								// return current word
	void		setToStart();						// point at first pair
	bool		hasData();							// check that it is pointing at a pair
	void		next();								// point to next pair
	Entry		currentData();						// return current pair of strings
	void		clear();							// clear the lex map
	void		load( const string & filename );	// load from disk file
	string		partOfSpeech( string pMeaning );	// return string part of speech id
};

#endif
