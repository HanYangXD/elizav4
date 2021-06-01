// you.cpp
// v1.2
// PWM
// 21-feb-2006
// NOTE:
// This "You" class could have a lot of work done on it.
// 

// Get rid of annoying STL warnings
#pragma warning(disable:4786)

// System header files
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//using namespace std;

// Project header files
#include "you.h"
#include <fstream>
#include <iostream>

// Class member functions
You::You():MAXBLANKS(3), MAXDONTKNOWS(4)
{
	mSpokeCount   = 0;
	mBlankCount   = 0;
	mTooDifficult = 0;
}

void You::name( string pName )
{
	//mName = pName;
	//pair<string, string> namePair;
	//namePair.first = "name";
	//namePair.second = pName;
	//mAttributes.load("users.txt");
	//mAttributes.add(namePair);
	//mAttributes.save("users.txt");


	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{
		
		if (strTemp.find("name,") != std::string::npos) {
			strTemp = "name," + pName;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");

	//ifstream patternt;
	//patternt.open("patterns.txt");
	//fileout.open("fileout.txt");
	string pattern = "";
	string response = "";
	//bool foundPattern = false;
	//while (getline(patternt, pattern, ','))
	//{
	//	cout << "first loop " << endl;
	//	getline(patternt, response);
	//	if (pattern.find("what is my name") != std::string::npos) {
	//		foundPattern = true;
	//		response = "\"your name is " + pName + "\"\n";
	//		fileout << pattern << "," << response << "\n";
	//		break;
	//	}
	//}
	//patternt.close();
	//if (!foundPattern) {
	//	patternt.open("patterns.txt");
	//	fileout << "\"what is my name\",\"your name is " << pName << "\"" << "\n";
	//	while (getline(patternt, pattern, ','))
	//	{
	//		cout << "2nd loop" << endl;
	//		getline(patternt, response);
	//		fileout << pattern << "," << response << "\n";
	//	}
	//}
	//patternt.close();
	//fileout.close();
	//remove("patterns.txt");
	//rename("fileout.txt", "patterns.txt");
	
	//ifstream patternt;
	//patternt.open("patterns.txt");
	//fileout.open("fileout.txt");
	//
	//fileout << "\"what is my name\",\"your name is " + pName + "\"\n";
	//fileout << patternt.rdbuf();
	////patternt.open("patterns.txt");
	//
	//patternt.close();
	//fileout.close();

	//std::remove("patterns.txt");
	//std::rename("fileout.txt", "patterns.txt");

	
}

string You::name()
{

	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("name,") != std::string::npos) {
			filein.close();
			return strTemp.substr(5);
		}
	}
	
}

void You::age(string age) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp1;
	while (filein >> strTemp1)
	{
		if (strTemp1.find("age,") != std::string::npos) {
			strTemp1 = "age," + age;
			//found = true;
		}
		strTemp1 += "\n";
		fileout << strTemp1;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}

string You::age() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("age,") != std::string::npos) {
			filein.close();
			return strTemp.substr(4);
		}
	}
}
void You::height(string height) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{

		if (strTemp.find("height,") != std::string::npos) {
			strTemp = "height," + height;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}
string You::height() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("height,") != std::string::npos) {
			filein.close();
			return strTemp.substr(7);
		}
	}
}
void You::weight(string weight) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{

		if (strTemp.find("weight,") != std::string::npos) {
			strTemp = "weight," + weight;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}
string You::weight() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("weight,") != std::string::npos) {
			filein.close();
			return strTemp.substr(7);
		}
	}
}

void You::like(string like) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{

		if (strTemp.find("love,") != std::string::npos) {
			strTemp = "love," + like;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}

string You::like() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("love,") != std::string::npos) {
			filein.close();
			return strTemp.substr(5);
		}
	}
}


void You::dislike(string dislike) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{

		if (strTemp.find("dislike,") != std::string::npos) {
			strTemp = "dislike," + dislike;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}

string You::dislike() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("dislike,") != std::string::npos) {
			filein.close();
			return strTemp.substr(8);
		}
	}
}

void You::hate(string hate) {
	ifstream filein("details.txt"); //File to read from
	ofstream fileout("fileout.txt"); //Temporary file

	string strTemp;
	while (filein >> strTemp)
	{

		if (strTemp.find("hate,") != std::string::npos) {
			strTemp = "hate," + hate;
			//found = true;
		}
		strTemp += "\n";
		fileout << strTemp;
		//if(found) break;
	}
	filein.close();
	fileout.close();
	remove("details.txt");
	rename("fileout.txt", "details.txt");
}

string You::hate() {
	ifstream filein("details.txt"); //File to read from
	string strTemp;
	while (filein >> strTemp)
	{
		if (strTemp.find("hate,") != std::string::npos) {
			filein.close();
			return strTemp.substr(5);
		}
	}
}

void You::noteYouSpoke()
{
	mBlankCount = 0;
	mSpokeCount++;
}

unsigned You::youSpoke()
{
	return mSpokeCount;
}

void You::noteYouBlank()
{
	mBlankCount++;
}

unsigned You::youBlank()
{
	return mBlankCount;
}

void You::noteTooDifficult()
{
	mTooDifficult++;
}

unsigned You::youTooDifficult()
{
	return mTooDifficult;
}

void You::clearTooDifficult()
{
	mTooDifficult = 0;
}

