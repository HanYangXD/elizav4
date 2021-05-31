// testfind.cpp
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

// Function prototypes

int main()
{
bool required = true;
string token;
string myResponse;
string::size_type lastPos;
string::size_type pos;

	cout << "Enter a string (or quit):";
	readLine( cin, myResponse);
	while ( lowercase(myResponse)!="quit" )
	{
		pos = myResponse.find("\"", 0);
		lastPos = myResponse.find("\"", pos+1);
		while ( (pos != string::npos) && (lastPos != string::npos) )
		{
 			cout << "Start: " << pos << " End: " << lastPos << endl;
			pos = myResponse.find("\"", lastPos+1);
			lastPos = myResponse.find("\"", pos+1);


		}

		cout << "Enter a string (or quit):";
		readLine( cin, myResponse);
	}

	cout << "End of program: " << endl;

	return 0;
}

/*
void stringTokenize(const string& str, vector<string>& tokens )
{// Create a vector of substrings from a string using quotes to separate the strings. Note that
 // string::npos is a large number that indicates a string find operation has failed.

string::size_type lastPos;
string::size_type pos;

	tokens.clear();		// Make sure the vector is empty to start with

	// Find the first "substring" (token)
	pos = str.find("\"");
	lastPos = str.find("\"", pos+1);

    while ( (pos != string::npos) || (lastPos != string::npos) )
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(pos, lastPos-pos));
		pos = lastPos+1;

        // Find the next word
		pos = str.find("\"", pos);
		lastPos = str.find("\"", pos+1);
    }

}

  */