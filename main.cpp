#include <iostream>
#include "utterence-handler.h"
#include "loan-selection.h"
using namespace std;

int main()
{
    readUtterancesAndResponses("data/utterences.txt");
    readHomeloans("data/home.txt");

    cout << "Welcome to the Home Loan Chatbot! Type 'exit' to quit." << endl;

    string user_input;
    while (true)
    {
        cout << "You: ";
        getline(cin, user_input);
        if (user_input == "exit")
            break;

        string response = getResponse(user_input);
        cout << "Chatbot: " << response << endl;

        // Detect when the chatbot asks to select an area (based on utterence file)
        if (response.find("Please select area") != string::npos)
        {
            cout << "You: ";
            getline(cin, user_input);

            string areaResponse = getResponse(user_input);
            cout << "Chatbot: " << areaResponse << endl;

            // If input is valid numeric area, display loans
            if (user_input == "1" || user_input == "2" || user_input == "3" || user_input == "4")
            {
                int choice = stoi(user_input);
                string areas[MAX_HOME_LOANS];
                int areaCount = getAvailableAreas(areas, MAX_HOME_LOANS);

                if (choice >= 1 && choice <= areaCount)
                {
                    string selectedArea = areas[choice - 1];
                    displayHomeloansForArea(selectedArea);
                }
            }
        }
    }

    return 0;
}
