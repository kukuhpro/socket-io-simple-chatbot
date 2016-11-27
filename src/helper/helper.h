#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

typedef vector<string> vstring;

class helper {
	public:
		void copy( char *array[], vstring &v );
		void preprocess_input( string &str );
		void UpperCase( string &str );
		void cleanString( string &str );
		bool isPunc(char c);
		
	private:
		string delim;
};

#endif