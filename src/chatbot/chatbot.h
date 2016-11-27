#ifndef CHATBOT_H_INCLUDED
#define CHATBOT_H_INCLUDED

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <ctime>

#include "helper.h"

using namespace std;

typedef vector<string> vstring;

typedef struct {
	char *input;
	char *responses[3];
}record;

class chatbot 
{
	public:
		void setKnowledge(record Base[]);
		void setResponse(string message);
		void setSizeOfKnowledge(int sizeofknowledge);
		string getResponse();
		vstring find_match(string input);

	private:
		string Apps;
		size_t nKnowledgeBaseSize;
		record *KnowledgeBase;
		helper Help;
		vstring responses;
		string response_single;
};



#endif 
