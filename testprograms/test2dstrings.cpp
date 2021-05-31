// test2dstrings.cpp
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
#include "string2dvector.h"

// Function prototypes

int main()
{
bool required = true;
string searchWord;
string myResponse;
string filename;
String2DVector s2dVector;

	// Test 1: Read in the s2dVector from a text file
	filename = "patterns.txt";
	s2dVector.load( filename );

	// Test 2: test the size function
	cout << "There are " << s2dVector.size() << " s2dVector" << endl;

	// Test 3: the print function
	cout << "Printing the s2dVector" << endl;
	s2dVector.display();
	cout << "End of printing the s2dVector" << endl;

	// Test 5: save to text file
	filename = "patterns2.txt";
	s2dVector.save( filename );

	// Test 6: the clear function
	s2dVector.clear();
	cout << "There are " << s2dVector.size() << " s2dVector" << endl;
	cout << "Printing the s2dVector" << endl;
	s2dVector.display();
	cout << "End of printing the s2dVector" << endl;

	// Test 7: reload the map after a clear
	s2dVector.load( filename );

	cout << "Printing the s2dVector" << endl;
	s2dVector.display();
	cout << "End of printing the s2dVector" << endl;

	cout << "End of program: " << endl;

	return 0;
}


