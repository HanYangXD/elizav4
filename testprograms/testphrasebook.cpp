// testphrasebook.cpp
// v1.1
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
#include "phrasebook.h"

// Function prototypes

int main()
{
bool required = true;
string searchWord;
string myResponse;
string filename;
Phrasebook phrases;
Phrasebook::Entry entry;
vector<string> setPhrases;

	// Test 1: Read in the phrases from a text file
	filename = "phrases.txt";
	phrases.load( filename );

	// Test 2: test the size function
	cout << "There are " << phrases.size() << " phrases" << endl;

	// Test 3: the print function
	cout << "Printing the phrases" << endl;
	phrases.display();
	cout << "End of printing the phrases" << endl;

	// Test 4: the contains() and meaning() functions
	cout << "Enter a keyword (or quit):";
	cin  >> searchWord;
	while ( lowercase(searchWord)!="quit" )
	{
		if ( phrases.contains( searchWord ) )
		{
			// Test 9: the currentData() function
			entry = phrases.currentData();
			cout << "Entry: " << entry.first << ',' << entry.second << endl;

			cout << "The keyword " << searchWord << " is matched to " << phrases.phrase() << endl;

			phrases.extract( searchWord, setPhrases );
			printTokens( setPhrases, "\n" );


		}
		else
		{
			cout << "No synonym for " << searchWord << endl;
		}
		cout << "Enter a word (or quit):";
		cin  >> searchWord;
	}

	// Test 5: save to text file
	filename = "phrases2.txt";
	phrases.save( filename );

	// Test 6: the clear function
	phrases.clear();
	cout << "There are " << phrases.size() << " phrases" << endl;
	cout << "Printing the phrases" << endl;
	phrases.display();
	cout << "End of printing the phrases" << endl;

	// Test 7: reload the map after a clear
	phrases.load( filename );

	cout << "Printing the phrases" << endl;
	phrases.display();
	cout << "End of printing the phrases" << endl;

	// Test 8: extract some phrases
	cout << "Extract the sets of phrases" << endl;
	cout << "1. blankPrompts" << endl;
	phrases.extract( "blankPrompts", setPhrases );
	printTokens( setPhrases, "\n" );
	setPhrases.clear();
	cout << "2. dontKnowPrompts" << endl;
	phrases.extract( "dontKnowPrompts", setPhrases );
	printTokens( setPhrases, "\n" );
	setPhrases.clear();
	cout << "3. questionWords" << endl;
	phrases.extract( "questionWords", setPhrases );
	printTokens( setPhrases, "\n" );
	setPhrases.clear();

	cout << "End of program: " << endl;

	return 0;
}


