// useful.h
// v1.0
// pwm
// 21-feb-2006

#ifndef USEFUL_H
#define USEFUL_H

// project header files
void readLine( istream & in, string & s );
string lowercase( string & ps );
string uppercase( string & ps );
string spacePunctuation( string & strIn, string & ignore );
string spacePunctuation( string & strIn, char * ignore );
string spacePunctuation( string & strIn );
string removePunctuation( string & strIn, string & ignore );
string removePunctuation( string & strIn, char * ignore );
string removePunctuation( string & strIn );
string trimSpace( string & ps );
bool isString( string & str, const string strArray[], unsigned size );
unsigned convertString( string & str, const string strArray[], unsigned size );

void tokenize(const string& str, vector<string>& tokens, const string& delimiters);
void stringTokenize(const string& str, vector<string>& tokens );
void printTokens( vector<string>& tokens );
void printTokens( vector<string>& tokens, char * separator );
bool replace(std::string& str, const std::string& from, const std::string& to);

#endif
