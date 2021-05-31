// useful.h
// v1.0
// pwm
// 21-feb-2006

#ifndef YOU_H
#define YOU_H

#include <string>
using namespace std;

#include "dictionary.h"

// Class You
// What should I remember about the person I am talking to?
// Maybe I could store their details in the dictionary using keywords such as:
// "name", "john smith"
// "gender", "male"
// etc. rather than have a separate named variable for each attribute (i.e. delete the
// mName variable).
//const unsigned MAXBLANKS	= 3;
//const unsigned MAXDONTKNOWS = 4;

class You
{
private:
	string mName;
	Dictionary mAttributes;		// perhaps this could be used
	unsigned mSpokeCount;
	unsigned mBlankCount;
	unsigned mTooDifficult;

public:
	const unsigned MAXBLANKS;
	const unsigned MAXDONTKNOWS;
	You();
	void name( string pName );
	string name();
	void age(string age);
	string age();
	void height(string height);
	string height();
	void weight(string weight);
	string weight();
	void like(string like);
	string like();
	void dislike(string dislike);
	string dislike();
	void hate(string hate);
	string hate();
	
	void noteYouSpoke();
	unsigned youSpoke();
	
	void noteYouBlank();
	unsigned youBlank();
	
	void noteTooDifficult();
	unsigned youTooDifficult();
	void clearTooDifficult();

};

#endif
