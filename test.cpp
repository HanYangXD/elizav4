// test.cpp
// v1.0
// 22-feb-2006
// test harness for the Eliza program routines.

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>			// for random number generation

using namespace std;

// Project header files
#include "useful.h"
#include "dictionary.h"

// Function prototypes
void loadDictionary( const string & filename, Dictionary & synonyms );
void saveDictionary( const string & filename, Dictionary & synonyms );

int main()
{
bool required = true;
string searchWord;
string myResponse;
string filename;
Dictionary synonyms;

	// Test 1: Read in the synonyms from a text file
	filename = "synonyms.txt";
	loadDictionary( filename, synonyms );

	// Test 2: test the size function
	cout << "There are " << synonyms.size() << " synonyms" << endl;

	// Test 3: the print function
	cout << "Printing the synonyms" << endl;
	synonyms.display();
	cout << "End of printing the synonyms" << endl;

	// Test 4: the contains() and meaning() functions
	cout << "Enter a word (or quit):";
	cin  >> searchWord;
	while ( lowercase(searchWord)!="quit" )
	{
		if ( synonyms.contains( searchWord ) )
		{
			cout << "The synonym of " << searchWord << " is " << synonyms.meaning( searchWord ) << endl;
		}
		else
		{
			cout << "No synonym for " << searchWord << endl;
		}
		cout << "Enter a word (or quit):";
		cin  >> searchWord;
	}

	// Test 5: save to text file
	filename = "synonyms2.txt";
	saveDictionary( filename, synonyms );

	// Test 6: the clear function
	synonyms.clear();
	cout << "There are " << synonyms.size() << " synonyms" << endl;
	cout << "Printing the synonyms" << endl;
	synonyms.display();
	cout << "End of printing the synonyms" << endl;

	// Test 7: reload the map after a clear
	loadDictionary( filename, synonyms );

	cout << "Printing the synonyms" << endl;
	synonyms.display();
	cout << "End of printing the synonyms" << endl;

	cout << "End of program: " << endl;

	return 0;
}


void loadDictionary( const string & filename, Dictionary & synonyms )
{
ifstream fIn;
string inputLine;
string inputLineCopy;
vector <string> tokens;

	fIn.open( filename.c_str() );
	if ( fIn.good() )
	{// use it
		cout << "File opened ok" << endl;
		readLine( fIn, inputLine );		// read ahead one line
		while ( fIn.good() )
		{
			cout << "Input: " << inputLine << endl;
			inputLine = trimSpace(inputLine);
			if ( inputLine.size()>0 )
			{// then use the line
				inputLineCopy = removePunctuation( inputLine, ",'" );		// remove string quotes
				tokenize(inputLineCopy, tokens, "," );						// break into the two components
				if ( tokens.size()==2 )
				{// then we have something sensible
					synonyms.add(Dictionary::Entry( trimSpace(tokens[0]), trimSpace(tokens[1])) );// store without leading and trailing space
					cout << "Output:" << inputLineCopy << endl;
				}
				else
				{// moan! we don't have just two strings separated by a comma
					cout << "WARNING: ignoring the following line that does not have two comma separated strings" << endl;
					cout << "Output:" << inputLineCopy << endl;
				}
			}
			else
			{// ignoring a blank line
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

void saveDictionary( const string & filename, Dictionary & synonyms )
{
ofstream fOut;

	fOut.open(filename.c_str());
	if ( fOut.good() )
	{// then use it

		synonyms.setToStart();
		while ( synonyms.hasData() )
		{
			fOut << '\"' << synonyms.word() << "\",\t\t\"" << synonyms.meaning() << '\"' << endl;
			synonyms.next();
		}
		fOut.close();
	}
	else
	{// moan!
		cout << "ERROR: unable to open file " << filename << endl;
	}
	fOut.clear(0);	// reset error flag after processing
}
