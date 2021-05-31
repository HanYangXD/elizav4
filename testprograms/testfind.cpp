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
string textLine;
ifstream fin;
string filename;
vector<string> tokens;

	filename = "patterns.txt";
	fin.open( filename.c_str() );
	if ( fin.good() )
	{// then process the patterns file


		readLine( fin, textLine);
		while ( fin.good() )
		{
			//cout << "INPUT: " << textLine << endl;
			stringTokenize( textLine, tokens );
			printTokens( tokens );

			readLine( fin, textLine);
		}
		fin.close();
	}
	else
	{// moan!
		cout << "ERROR: unable to open text file" << endl;
	}

	cout << "End of program: " << endl;

	return 0;
}

