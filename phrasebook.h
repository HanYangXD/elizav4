// phrasebook.h
// v1.1
// PWM
// 21-feb-2006

#ifndef PHRASEBOOK_H
#define PHRASEBOOK_H

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <string>
#include <vector>
#include <map>

// Project header files
#include "useful.h"

class Phrasebook
{
private:
	multimap <string,string> mPhrasebook;			// create empty phrasebook mapping
	multimap<string,string>::iterator mIter;
	
public:
	typedef pair<string,string> Entry;				// entry holds the phrasebook pair
	void		add( Entry & pEntry );				// add a phrasebook pair of strings
	void		display();							// debugging dump of data
	unsigned	size();								// number of phrasebook items
	bool		contains( string & pSearchString );	// check for entry
	string		phrase();							// return current phrase
	string		keyword();							// return current keyword
	void		setToStart();						// point at first pair
	void		setToStart( string & pKeyword );	// point at first pair the matches the keyword
	bool		hasData();							// check that it is pointing at a pair
	bool		hasData(string & pKeyword );		// check that it is pointing at a pair that match the keyword
	void		next();								// point to next pair
	void		next( string & pKeyword );			// point to next pair that match the keyword
	Entry		currentData();						// return current pair of strings
	void		clear();							// clear the phrasebook multimap
	void		extract( string pKeyword, vector <string> & pPhrases );	// load matching phrase into a string vector
	void		load( const string & filename );	// load from file
	void		save( const string & filename );	// save to file
};

#endif
