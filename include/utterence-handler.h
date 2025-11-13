#ifndef UTTERENCE_HANDLER_H
#define UTTERENCE_HANDLER_H

#include <string>
using namespace std;

// Maximum number of utterances
const int MAX_UTTERANCES = 50;

extern string userinput[MAX_UTTERANCES];
extern string responses[MAX_UTTERANCES];
extern int utterance_count;

void readUtterancesAndResponses(const string& filename);
string getResponse(const string& input);

#endif
