// speech.h
// v4.0
// 2-may-2005
// The speech class and required includes.
// v2.0 Has the additional functions required for the << overloaded operator function.
// v3.0 Make voice a single external object
// v4.0 Piggyback onto stringstream

#ifndef SPEECH_H
#define SPEECH_H

// System header files
#include <sapi.h>

#include <iostream>
#include <string>
#include <sstream>
using std::string;
using std::ostream;
using std::ostringstream;


class Voice : public ostringstream
{
private:
	HRESULT hr;
	ISpVoice * pVoice;
	void speak( const string &s );

public:
	Voice();
	void speak();
	~Voice();
};

// We only need one voice object
extern Voice voice;

#endif
