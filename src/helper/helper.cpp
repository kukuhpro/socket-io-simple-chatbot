#include <string>
#include <vector>
#include <cstdio>
#include <iostream>

#include "helper.h"

using namespace std;

void helper::preprocess_input ( string &str ) 
{
	cleanString(str);
	UpperCase(str);
};

void helper::copy (char *array[], vstring &v) 
{
	for(int i = 0; i < 3; ++i) 
	{
		if(array[i] != NULL) 
		{
			v.push_back(array[i]);
		} 
		else 
		{
			break;
		}
	}
};

void helper::UpperCase ( string &str ) 
{
	int len = str.length();
	for( int i = 0; i < len; i++ ) 
	{
		if ( str[i] >= 'a' && str[i] <= 'z' ) 
		{
			str[i] -= 'a' - 'A';
		}
	}
};

bool helper::isPunc (char c) 
{
	return delim.find(c) != string::npos;
};

void helper::cleanString ( string &str ) 
{
	int len = str.length();
	string temp = "";

	char prevChar = 0;

	for(int i = 0; i < len; ++i) 
	{
		if(str[i] == ' ' && prevChar == ' ') 
		{
			continue;
		}

		else if(!isPunc(str[i])) 
		{
			temp += str[i];
		}

		prevChar = str[i];
	}
	str = temp;
};