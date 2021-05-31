// dictionary.h
// v1.2
// PWM
// 21-feb-2006

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <string>
#include <vector>
#include <map>

// Project header files
#include "useful.h"

class Dictionary
{
private:
	map <string,string> mDictionary;				// create empty dictionary mapping
	map<string,string>::iterator mIter;
	vector <string>::iterator mIter1;
	vector <string>::iterator mIter2;
	
public:
	typedef		pair<string,string> Entry;			// entry holds the dictionary pair
	void		add( Entry & pEntry );				// add a dictionary pair of strings
	void		display();							// debugging dump of data
	unsigned	size();								// number of dictionary items
	bool		contains( string & pSearchString );	// check for entry
	string		string1();							// return the matching string in string1
	string		string2();							// return the matching string in string2
	string		meaning();							// return current meaning
	string		word();								// return current word
	void		setToStart();						// point at first pair
	bool		hasData();							// check that it is pointing at a pair
	void		next();								// point to next pair
	Entry		currentData();						// return current pair of strings
	void		clear();							// clear the dictionary map
	void		load( const string & filename );	// load from disk file
	void		save( const string & filename );	// save to disk file

};

#endif
