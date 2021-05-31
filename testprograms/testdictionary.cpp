// testdictionary.cpp
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

int main()
{
bool required = true;
string searchWord;
string myResponse;
string filename;
Dictionary synonyms;
Dictionary::Entry entry;

	// Test 1: Read in the synonyms from a text file
	filename = "synonyms.txt";
	synonyms.load( filename );

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
			cout << "The synonym of " << searchWord << " is " << synonyms.meaning() << endl;

			// Test 8: the currentData() function
			entry = synonyms.currentData();
			cout << "Entry: " << entry.first << ',' << entry.second << endl;

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
	synonyms.save( filename );

	// Test 6: the clear function
	synonyms.clear();
	cout << "There are " << synonyms.size() << " synonyms" << endl;
	cout << "Printing the synonyms" << endl;
	synonyms.display();
	cout << "End of printing the synonyms" << endl;

	// Test 7: reload the map after a clear
	synonyms.load( filename );

	cout << "Printing the synonyms" << endl;
	synonyms.display();
	cout << "End of printing the synonyms" << endl;

	cout << "End of program: " << endl;

	return 0;
}


