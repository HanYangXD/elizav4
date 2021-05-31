// speech.cpp
// v4.0
// 2-may-2005
// The speech class and required includes.
// v2.0 Has the additional functions required for the << overloaded operator function.
// v3.0 Make voice a global object - because we only need one of them
// v4.0 Piggyback onto stringstream and clear out unwanted code

// System header files
#include <sapi.h>

// Project header files
#include "speech.h"

#include <iostream>
#include <string>
#include <cassert>
using std::string;
using std::cerr;
using std::endl;
using std::cout;

Voice::Voice()
{
	pVoice = NULL;
	this->str("");

    if (FAILED(::CoInitialize(NULL)))
	{// then failed to initialise COM
        return;
	}

	// Create a voice object
	// CLSID_SpVoice = class ID for the SAPI SpVoice object 
	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if( !SUCCEEDED( hr ) )
    {
		cerr << "SAPI ERROR: unable to create a voice object" << endl;
	}
}

Voice::~Voice()
{
    pVoice->Release();
    pVoice = NULL;

	::CoUninitialize();
}


void Voice::speak( const string & s )
{
wchar_t * words;
size_t size;
errno_t errNumber;

	// malloc enough space for the converted string
	words = (wchar_t *)malloc((s.size()+1)*sizeof(wchar_t));
	assert( words!=NULL);

	errNumber = mbstowcs_s( &size, words,(s.size()+1), s.c_str(), s.size()  );
	//cout << "Error number = " << errNumber << endl;
	hr = pVoice->Speak(words, SPF_IS_XML , NULL );

	// release space
	delete[] words;
}

void Voice::speak()
{
	speak( this->str() );
	this->str("");			// clear the buffer
}

// We just need one voice object
Voice voice;