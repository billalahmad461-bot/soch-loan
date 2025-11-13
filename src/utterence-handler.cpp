#include <iostream>
#include <fstream>
#include <string>
#include "utterence-handler.h"
#include <algorithm> // for transform
using namespace std;

string userinput[MAX_UTTERANCES];
string responses[MAX_UTTERANCES];
int utterance_count = 0;

// Convert string to lowercase
string toLower(const string& str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Reading utterances and responses from file
void readUtterancesAndResponses(const string& filename)
{
    ifstream file(filename);  // Use the filename parameter properly
    if (!file)
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line) && utterance_count < MAX_UTTERANCES)
    {
        size_t delimiter_pos = line.find('#');
        if (delimiter_pos != string::npos)
        {
            userinput[utterance_count] = line.substr(0, delimiter_pos);
            responses[utterance_count] = line.substr(delimiter_pos + 1);
            utterance_count++;
        }
    }

    file.close();
}

// Get response for user input
string getResponse(const string& input)
{
    string user_input_lower = toLower(input);

    for (int i = 0; i < utterance_count; i++)
    {
        if (user_input_lower == toLower(userinput[i]))
            return responses[i];
    }

    return "I'm sorry, I don't understand your request.";
}
