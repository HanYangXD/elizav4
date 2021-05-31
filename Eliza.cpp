// azile.cpp
// v5.0
// There are comments preceded by NOTE: in the text of the program. This is a general program and would have to be
// restructured to do different sorts of interactions. What sorts of interactions are possible?

// How about an azile that knows typical C++ compiler errors and solutions and can help novice programmers solve
// errors? For C++ read any sort of fixed body of information.
// How about an azile that has low self-esteem and always misinterprets what you write as in someway its fault?
// How about an azile that could learn facts about a subject in response to your input and uses this knowledge in 
// future interaction?

// What sort of things are missing?

// 1.	There is a You object but it has little functionality.
// 2.	There is no history kept. It would be good if azile could refer to previous statements to direct its responses
// 3.	There is no context - can you get Azile to work within the current context?
// 4.	There are no ways of getting azile to learn new rules.

// V5.0
// Added the LEX dictionary that was compiled by Dave Keiras, of the University of
// Michigan, who made it available in the public domain in 1980.

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>			// for random number generation
#include <fstream>

using namespace std;

// Project header files
#include "useful.h"			// a collection of useful functions
#include "dictionary.h"		// this uses STL to map one word to another word or string of words: 1-1
#include "string2dvector.h"	// this behaves like a 2D array of strings held as STL vectors: 1-1
#include "phrasebook.h"		// this uses STL multimap to group strings: 1-many
#include "you.h"			// shell of a class to hold user information
#include "lex.h"			// LEX dictionary from Dave Keiras

// Constants

// Project functions
void instructions();

void replaceSynonyms( vector<string>& tokens, Dictionary & synonyms );
bool canRespond( vector<string>& tokens, String2DVector & patterns, string & myResponse );
void showLexValues( vector<string>& tokens );

// The global objects
You you;
String2DVector	patterns;
Dictionary		synonyms;
Dictionary		switchables;
String2DVector		users;
Phrasebook		phrases;
Lex				lexWords;

time_t now = time(0);
char* dt = ctime(&now);
//cout << dt << endl; //display current datetime

ofstream logFile("Logs.txt", ios::app);

using namespace std;
int main()
{
bool required = true;
bool didRespond = false;
string inputLine;
string inputLineCopy;

vector <string> tokens;
vector <string> blankPrompts;
vector <string> dontKnowPrompts;
vector <string> questionWords;
string searchWord;
string myResponse;

logFile << "\n" << dt << endl;




	// *** 1. Introduction
	// *** Set up the various data structures
	cout << "Waking up and loading my brain ..." << endl;
	// Load the synonyms from file
	synonyms.load( "synonyms.txt" );
	// Load the switchables from file
	switchables.load( "switchables.txt" );
	// Load the dialogue patterns from file
	/*patterns.load( "patterns.txt"  );*/
	// Load the LEX dictionary from file
	lexWords.load( "lex.txt"  );
	// Load the phrases from file
	users.load( "users.txt" );
	phrases.load( "phrases.txt" );
	phrases.extract("blankPrompts", blankPrompts );
	if (blankPrompts.size()==0)
	{// moan!
		cout << "WARNING: no blank prompts loaded" << endl;
	}
	phrases.extract("dontKnowPrompts", dontKnowPrompts );
	if (dontKnowPrompts.size()==0)
	{// moan!
		cout << "WARNING: no \"dontknow\" prompts loaded" << endl;
	}
	phrases.extract("questionWords", questionWords );
	if (questionWords.size()==0)
	{// moan!
		cout << "WARNING: no questionWords loaded" << endl;
	}

	// Seed the random-number generator with current time so that
    // the numbers will be different every time we run.
	srand( (unsigned)time( NULL ) );

	cout << "Max patterns = " << patterns.size() << endl;

	// *** 2. Main body of the program
	// *** Keep going until they type bye
	instructions();
	while (required)
	{
		patterns.load("patterns.txt");
		cout << "You: ";
		readLine( cin, inputLine );
		logFile << "You: " << inputLine << endl;

		if ( inputLine.length() == 0 )
		{// then they haven't written anything so give them some sort of prompt

			if (you.youBlank() >= you.MAXBLANKS)
			{// give up on them and end the program
				cout << "Azile: you are an unresponsive human" << endl;
				logFile << "Azile: you are an unresponsive human" << endl;
				required = false;
				continue;
			}

			if ( blankPrompts.size()>0 )
			{// output a relevant response
				cout << "Azile: " << blankPrompts[rand()%blankPrompts.size()] << endl;
				logFile << "Azile: " << blankPrompts[rand()%blankPrompts.size()] << endl;
			}

			you.noteYouBlank();	// count the blank responses
		}
		else
		{// process their input

			// count it
			you.noteYouSpoke();
			// what else would you like to do with their input?

			string searchStr = "my name is";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputname = inputLine;
				inputname.erase(0, 11);
				you.name(inputname);

			}
			
			searchStr = "what is my name";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				cout << "Azile: Your name is " << you.name() << endl;
				logFile << "Azile: Your name is " << you.name() << endl;
				continue;
			}


			//update age
			searchStr = "my age is";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputage = inputLine;
				inputage.erase(0, 10);
				you.age(inputage);
			}

			searchStr = "what is my age";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				cout << "Azile: Your age is " << you.age() << endl;
				logFile << "Azile: Your age is " << you.age() << endl;
				continue;
			}

			//update height
			searchStr = "my height is";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputheight = inputLine;
				inputheight.erase(0, 13);
				you.height(inputheight);
			}

			searchStr = "what is my height";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				cout << "Azile: Your height is " << you.height() << endl;
				logFile << "Azile: Your height is " << you.height() << endl;
				continue;
			}

			//update weight
			searchStr = "my weight is";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputheight = inputLine;
				inputheight.erase(0, 13);
				you.weight(inputheight);
			}

			searchStr = "what is my weight";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				cout << "Azile: Your weight is " << you.weight() << endl;
				logFile << "Azile: Your weight is " << you.weight() << endl;
				continue;
			}


			//update love
			if (lowercase(inputLine).find("what i love") != std::string::npos) {
				cout << "Azile: You love " << you.like() << endl;
				logFile << "Azile: You love " << you.like() << endl;
				continue;
			}

			searchStr = "i love";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputlike = inputLine;
				inputlike.erase(0, 7);
				you.like(inputlike);
			}

			//update dislike
			searchStr = "i don't like";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputheight = inputLine;
				inputheight.erase(0, 13);
				you.dislike(inputheight);
			}

			searchStr = "what i dislike";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				cout << "Azile: You dislike " << you.dislike() << endl;
				logFile << "Azile: Your dislike " << you.dislike() << endl;
				continue;
			}

			//update hate
			if (lowercase(inputLine).find("what i hate") != std::string::npos) {
				cout << "Azile: You hate " << you.hate() << endl;
				logFile << "Azile: You hate" << you.hate() << endl;
				continue;
			}

			searchStr = "i hate";
			if (lowercase(inputLine).find(searchStr) != std::string::npos) {
				string inputlike = inputLine;
				inputlike.erase(0, 7);
				you.hate(inputlike);
			}

			




			/*cout << "ur name :3 " << you.name() << endl;
			cout << inputLine << endl;
			string searchstr = "name";*/
			
			/*if (users.contains(searchstr)) {
				cout << "your name is " << endl;
			}*/
			

			// get the individual words as an array (vector) of word
			inputLineCopy = removePunctuation( inputLine, "\'" );		// remove punctuation apart from '
			tokenize( inputLineCopy, tokens, " \t" );					// break up into words
			replaceSynonyms( tokens, synonyms );						// replace synonyms
			//showLexValues( tokens );									// show parts of speech

			// Process them
			if ( didRespond = canRespond( tokens, patterns, myResponse ) )
			{// then it matches one of the patterns exactly
				cout << myResponse << endl;
			}

			// special cases			
			if (uppercase(tokens[0]) == "BYE" )
			{// they are wanting to stop
				users.load("users.txt");
				users.clear();
				users.save("users.txt");
				required = false;
				continue;
			}

			


			
			if (didRespond==false)
			{// I can't cope with it
			 // This is really bad. There must be something you can do with it!!!
			 //	cout << "Azile could say ...." << endl;
				cout << myResponse << endl;
			//	cout << "Does that make sense????" << endl << endl;
			//	cout << "Azile: i'm sorry i don't understand that" << endl;
				you.noteTooDifficult();
				if ( you.youTooDifficult() > you.MAXDONTKNOWS )
				{
					if ( dontKnowPrompts.size()>0 )
					{// then use them
						cout << "Azile: " << dontKnowPrompts[rand()%dontKnowPrompts.size()] << endl;
						logFile << "Azile: " << dontKnowPrompts[rand()%dontKnowPrompts.size()] << endl;
					}
					you.clearTooDifficult();
				}
			}

		}

	}

	// *** 3. The End
	// *** What needs to be done here?
	// Anything that Azile needs to remember should be written to disk at this point
	if ( you.youSpoke() > 0 )
	{
		cout << "Azile: I enjoyed your " << you.youSpoke() << " interactions." << endl;
	}

	return 0;
}

// Project functions
void instructions()
{
	cout << "Azile: You can call me Azile, as I'll be trying to interact with you." << endl;
	cout << "Azile: Enter your statements at the prompt. When you have had enough type bye." << endl;
	cout << endl;
}

// NOTE:
// There are a whole number of string processing functions given below which may be of value to you. 

void replaceSynonyms( vector<string>& tokens, Dictionary & synonyms )
{// Replaces any word in tokens that has a synonym
 // Break multiple word strings into separate vector elements

vector<string> temp;
vector<string> substring;
bool needsExpanding = false;
vector<string>::iterator vi;
vector<string>::iterator stri;
string str;


	for ( vi=tokens.begin(); vi!=tokens.end(); vi++ )
	{// check each token

		if ( synonyms.contains( *vi ) )
		{// there is one so get the synonym

			needsExpanding = true;							// remember there was at least one synonym
			str = synonyms.meaning();						// expand it
			tokenize( str, substring, " \t" );				// break it into its tokens

			for ( stri=substring.begin(); stri != substring.end(); stri++ )
			{// insert the tokens into the temporary copy of the vector
				temp.push_back(*stri);
			}

		}
		else
		{// just put the unexpanded token on to the temporary copy of the vector
			temp.push_back(*vi);
		}
	}

	if (needsExpanding)
	{// replace tokens with temp
		tokens.clear();
		tokens = temp;
	}

}

bool canRespond( vector<string>& userInput, String2DVector & patterns, string & myResponse )
{// This function compares the user input (stored as an array (vector) of strings with each of the patterns
 // stored in the array of patterns. If a match is found it constructs a response string and returns the value
 // TRUE; if there is no match, it returns the value FALSE. The 2D array of patterns has element [0] containing
 // the pattern that is being matched and element [1] holding the pattern for the response. The words from the
 // userInput that match the @ parameters are stored in an array(vector) called components. These are inserted
 // into the matching pattern for the response.

vector <string> inTemplate;				// used to hold the individual words of the string in pattern[0]
vector <string> outTemplate;			// used to hold the individual words of the string in pattern[1]
vector <string> components;				// the @ components of the userInput
string aComponent;						// used to construct one component
unsigned templateIndex   = 0;
unsigned userInputIndex  = 0;
unsigned componentsIndex = 0;			// to index each component set of words (1-n)
bool unMatched			 = true;		// flag to control the main loop working through the patterns
bool isMatching			 = true;		// flag to control the loop trying to match one pattern
unsigned count = 0;

	patterns.setToStart();
	while ( unMatched && patterns.hasData() )
	{// work through the known patterns looking for a pattern match. Stop looking if we run out of
	 // patterns or we find a match.

		// tokenise the next pattern
		tokenize( patterns.string1(), inTemplate, " \t" );

		components.clear();		// clear the @ components list
		userInputIndex  = 0;	// point at the start of the user input
		isMatching      = true;	// start trying to match this template

		templateIndex=0;		// start at the begining of the template string

		while ( (templateIndex<inTemplate.size() ) && ( userInputIndex < userInput.size() ) &&  isMatching )
		{// process each component in turn on the template

			if ( (templateIndex<inTemplate.size())&& (inTemplate[templateIndex].compare( 0, 2, "@w") == 0) )
			{// then we have an @w command - just store the next word in the userInput as a component

				if ( userInputIndex < userInput.size() )
				{// then there is a word we can use ... actually this is implied from the test in the while
				 // loop ... but it is a bit of defensive programming in case the code is changed.

					components.push_back( userInput[userInputIndex] );
					userInputIndex++;	// look at next user input word
			}
				else
				{// no word so no match ... try the next template
					isMatching = false;
				}
				templateIndex++;	// we processed that template word

			}
			else if ( (templateIndex<inTemplate.size())&& (inTemplate[templateIndex].compare( 0, 2, "@r") == 0) )
			{// then we have an @r command - just move the rest of the user input onto the next component
			 // Q: What about the last space we added?

				aComponent.erase();
				while ( userInputIndex < userInput.size() )
				{// create the component from the individual remaining tokens separated by spaces

					// switch I to you, etc. This is to reflect the changes we make, e.g.
					// user: i am not happy with you
					// azile: you are not happy with me?
					// NOTE: this is really simplistic and does not work very well. Sometimes "you" should become
					//       "me", but also it could be replaced by "i", e.g.
					// user: you are stupid
					// azile: why am i am stupid?
					if ( switchables.contains( userInput[userInputIndex]) )
					{
						userInput[userInputIndex] = switchables.meaning();
					}
					// now write the word or swapped word into the component string
					aComponent = aComponent + userInput[userInputIndex] + ' ';
					userInputIndex++;
				}

				if ( aComponent.size() > 0 )
				{// then we had at least one word in the component so get rid of that last space

					aComponent.erase( aComponent.size()-1 );
					components.push_back( aComponent );	// put the entire string in the component

					// we seem to have completed ok so log that and leave
					unMatched = false;
					isMatching = false;
				}
				else
				{// there were no words so let's be pedantic and say we need to keep looking at patterns
					isMatching = false;
				}

				templateIndex++;	// we processed that template word

			}
			else if ( inTemplate[templateIndex].compare( 0, 2, "@n") == 0 )
			{// then we have an @n command - just move the rest of the user input onto the next component
			 // until we find a token in the input string matching the next template word

				templateIndex++;			// look at next word

				if (templateIndex<inTemplate.size())
				{// then the template is ok and there is a next word to try to match

					aComponent.erase();			// create an empty component
					while ( (userInputIndex < userInput.size()) && (inTemplate[templateIndex]!=lowercase(userInput[userInputIndex])))
					{// push the rest of the words into the component until we find the matching word

						aComponent = aComponent + userInput[userInputIndex] + ' ';
						userInputIndex++;
					}

					if (userInputIndex < userInput.size())
					{// then we did find a matching word so package the component and move on
						if ( aComponent.size() > 0 )
						{// then we had at least one word in the component so get rid of that last space

							aComponent.erase( aComponent.size()-1 );
						}

						components.push_back( aComponent );	// put the entire string in the component
						userInputIndex++;	// move over the word we have matched
						templateIndex++;	// look at the next part of the input template
					}
					else
					{// no match so that template word was never matched
						isMatching = false;
					}
				}
				else
				{// error in the template file ... what should we do with errors like this?
					cout << "Azile: Oh dear! One of the patterns in my patterns.txt file is faulty ..." << endl;
					cout << "Azile: " << patterns.string1() << " is missing a word after one of the @n parameters" << endl;
					cout << "Azile: Could you be a dear and edit it for me? ... thanks ..." << endl;
					// get the next pattern
					isMatching = false;;
				}
			}
			else
			{// we are just matching the word

				if ( (userInputIndex < userInput.size()) && (templateIndex<inTemplate.size()) && (inTemplate[templateIndex]==lowercase(userInput[userInputIndex]) ) )
				{// then we have a match so move on to the next word
					userInputIndex++;
					templateIndex++;
				}
				else
				{// no match so try the next template
					isMatching = false;
				}
			}

		}// end of processing one template

		
		if ( (userInputIndex<userInput.size()) || (templateIndex<inTemplate.size() ) )
		{// then we didn't match - so check the next pattern
			patterns.next();
		}
		else
		{// we did - so get out
			unMatched = false;
		}

	}// end of processing all templates
	
	if ( patterns.hasData() )
	{// then there was a match

		// create the response
		myResponse="Azile:";
		tokenize( patterns.string2(), outTemplate, " \t" );

		for ( templateIndex=0; templateIndex<outTemplate.size(); templateIndex++ )
		{
			if ( outTemplate[templateIndex][0] == '@' )
			{// find out what component to move into myResponse

				componentsIndex = atoi( outTemplate[templateIndex].substr(1).c_str() ) - 1;
				// this is where it dies because componentsIndex is not valid
				if ( componentsIndex<(unsigned)components.size() )
				{// then access the component
					myResponse = myResponse + " " + components[componentsIndex];
				}
				else
				{// moan
					cout << "canRespond(): Error generating: \"" << myResponse << "\" accessing a component out of range" << endl;
				}

			}
			else
			{// just move this word into the response
				myResponse = myResponse + " " + outTemplate[templateIndex];
				
			}
			
		}
		logFile << myResponse << endl;
		return true;

	}
	else
	{// no matching template so just do your best with their input
		myResponse = "Azile:";

		for ( userInputIndex  = 0; userInputIndex<userInput.size(); userInputIndex++ )
		{// just copy the modified input to the output string

			// I think you needs to go to "we" because it can't distinguish between me and I
			if ( switchables.contains( lowercase(userInput[userInputIndex])) )
			{// switch I to you etc.
			 // NOTE: this is really simplistic and does not work very well.
				userInput[userInputIndex] = switchables.meaning();
			}
			myResponse = myResponse + " " + userInput[userInputIndex];
		}
		myResponse = myResponse + "? i'm not sure what you mean ...";

		logFile << myResponse << endl;
		return false;
	}

	users.setToStart();
	while (unMatched && users.hasData())
	{// work through the known users looking for a pattern match. Stop looking if we run out of
	 // users or we find a match.

		// tokenise the next pattern
		tokenize(users.string1(), inTemplate, " \t");

		components.clear();		// clear the @ components list
		userInputIndex = 0;	// point at the start of the user input
		isMatching = true;	// start trying to match this template

		templateIndex = 0;		// start at the begining of the template string

		while ((templateIndex < inTemplate.size()) && (userInputIndex < userInput.size()) && isMatching)
		{// process each component in turn on the template

			if ((templateIndex < inTemplate.size()) && (inTemplate[templateIndex].compare(0, 2, "@w") == 0))
			{// then we have an @w command - just store the next word in the userInput as a component

				if (userInputIndex < userInput.size())
				{// then there is a word we can use ... actually this is implied from the test in the while
				 // loop ... but it is a bit of defensive programming in case the code is changed.

					components.push_back(userInput[userInputIndex]);
					userInputIndex++;	// look at next user input word
				}
				else
				{// no word so no match ... try the next template
					isMatching = false;
				}
				templateIndex++;	// we processed that template word

			}
			else if ((templateIndex < inTemplate.size()) && (inTemplate[templateIndex].compare(0, 2, "@r") == 0))
			{// then we have an @r command - just move the rest of the user input onto the next component
			 // Q: What about the last space we added?

				aComponent.erase();
				while (userInputIndex < userInput.size())
				{// create the component from the individual remaining tokens separated by spaces

					// switch I to you, etc. This is to reflect the changes we make, e.g.
					// user: i am not happy with you
					// azile: you are not happy with me?
					// NOTE: this is really simplistic and does not work very well. Sometimes "you" should become
					//       "me", but also it could be replaced by "i", e.g.
					// user: you are stupid
					// azile: why am i am stupid?
					if (switchables.contains(userInput[userInputIndex]))
					{
						userInput[userInputIndex] = switchables.meaning();
					}
					// now write the word or swapped word into the component string
					aComponent = aComponent + userInput[userInputIndex] + ' ';
					userInputIndex++;
				}

				if (aComponent.size() > 0)
				{// then we had at least one word in the component so get rid of that last space

					aComponent.erase(aComponent.size() - 1);
					components.push_back(aComponent);	// put the entire string in the component

					// we seem to have completed ok so log that and leave
					unMatched = false;
					isMatching = false;
				}
				else
				{// there were no words so let's be pedantic and say we need to keep looking at users
					isMatching = false;
				}

				templateIndex++;	// we processed that template word

			}
			else if (inTemplate[templateIndex].compare(0, 2, "@n") == 0)
			{// then we have an @n command - just move the rest of the user input onto the next component
			 // until we find a token in the input string matching the next template word

				templateIndex++;			// look at next word

				if (templateIndex < inTemplate.size())
				{// then the template is ok and there is a next word to try to match

					aComponent.erase();			// create an empty component
					while ((userInputIndex < userInput.size()) && (inTemplate[templateIndex] != lowercase(userInput[userInputIndex])))
					{// push the rest of the words into the component until we find the matching word

						aComponent = aComponent + userInput[userInputIndex] + ' ';
						userInputIndex++;
					}

					if (userInputIndex < userInput.size())
					{// then we did find a matching word so package the component and move on
						if (aComponent.size() > 0)
						{// then we had at least one word in the component so get rid of that last space

							aComponent.erase(aComponent.size() - 1);
						}

						components.push_back(aComponent);	// put the entire string in the component
						userInputIndex++;	// move over the word we have matched
						templateIndex++;	// look at the next part of the input template
					}
					else
					{// no match so that template word was never matched
						isMatching = false;
					}
				}
				else
				{// error in the template file ... what should we do with errors like this?
					cout << "Azile: Oh dear! One of the users in my users.txt file is faulty ..." << endl;
					cout << "Azile: " << users.string1() << " is missing a word after one of the @n parameters" << endl;
					cout << "Azile: Could you be a dear and edit it for me? ... thanks ..." << endl;
					// get the next pattern
					isMatching = false;;
				}
			}
			else
			{// we are just matching the word

				if ((userInputIndex < userInput.size()) && (templateIndex < inTemplate.size()) && (inTemplate[templateIndex] == lowercase(userInput[userInputIndex])))
				{// then we have a match so move on to the next word
					userInputIndex++;
					templateIndex++;
				}
				else
				{// no match so try the next template
					isMatching = false;
				}
			}

		}// end of processing one template


		if ((userInputIndex < userInput.size()) || (templateIndex < inTemplate.size()))
		{// then we didn't match - so check the next pattern
			users.next();
		}
		else
		{// we did - so get out
			unMatched = false;
		}

	}// end of processing all templates

	

}

void showLexValues( vector<string>& tokens )
{// Display the information about the words in the LEX dictionary
vector<string>::iterator vi;
string searchWord;
string meaning;

	for ( vi=tokens.begin(); vi!=tokens.end(); vi++ )
	{// process each token in the vector

		searchWord = lowercase( *vi );			// get the word and force it to lowercase
		if ( lexWords.contains( searchWord ) )
		{
			meaning = lexWords.meaning();
			cout << "  LEX meaning of \"" << searchWord << "\": " << meaning;
			cout << " ; " << lexWords.partOfSpeech( meaning ) << endl;
		}
		else
		{
			cout << "No match for " << searchWord << endl;
		}
	}
}

