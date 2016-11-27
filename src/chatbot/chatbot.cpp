#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <ctime>

#include "chatbot.h"

using namespace std;


void chatbot::setKnowledge(record Base[]) {
	memcpy(&KnowledgeBase, &Base, sizeof(Base));
};

void chatbot::setSizeOfKnowledge(int sizeofknowledge) {
	nKnowledgeBaseSize = sizeofknowledge;
};

vstring chatbot::find_match (string input) 
{
	vstring result;
	for(int i = 0; i < nKnowledgeBaseSize; ++i) 
	{
		string keyWord = KnowledgeBase[i].input;
		if( input.find(keyWord) != string::npos ) 
		{
			Help.copy(KnowledgeBase[i].responses, result);
			return result;
		}
	}
	return result;
};

string chatbot::getResponse() {
	return response_single;
};

void chatbot::setResponse (string message) {
	Help.preprocess_input(message);
	responses = find_match(message);
	int nSelection = rand() % responses.size();
	string res = responses[nSelection];
	response_single = res;
};










