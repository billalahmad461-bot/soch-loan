#include "include\utterence-handler.h"
#include "include\display.h"  //add this include for the display class
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>


//file handling to trim spaces 


std::string UtterenceHandler::trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);


}

// converting to lower case to make input != casesensitive

std::string UtterenceHandler::toLower(const std::string &str)
{
    std:: string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
    {return std::tolower(c);
    });

    return result;

}



UtterenceHandler::UtterenceHandler() {}  // default constructor

//parametrized constructor

UtterenceHandler::UtterenceHandler(const std::string &file_name)
{
    storeUserInputAndResponse("utterences.txt");
}

bool UtterenceHandler::storeUserInputAndResponse(const std::string &file_name)
{
    std::ifstream file("utterences.txt");
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file!! "<<"utterences.txt"<<"\n";
        return false; 
    }

    _input.clear();
    _response.clear();

    std::string line;

      while(std::getline(file, line))
    {
        // Trim the line first to handle spaces at beginning/end
        std::string trimmedLine = trim(line);
        if(trimmedLine.empty()) continue;

        size_t pos = trimmedLine.find('#');
        if(pos == std::string::npos) continue;

        std::string key = trim(trimmedLine.substr(0, pos));
        std::string value = trim(trimmedLine.substr(pos + 1));

        // Converting to lower case for case-insensitive matching
        key = toLower(key);

        _input.push_back(key);
        _response.push_back(value);
    }

    file.close();
    return true;

}

bool UtterenceHandler::generateResponse(const std::string &input)
{
    // Properly handle multiple spaces by trimming and normalizing
    std::string cleanedInput = trim(input);
    cleanedInput = toLower(cleanedInput);

    // Search for exact match first
    for(size_t i = 0; i < _input.size(); i++)
    {
        if (_input[i] == cleanedInput)
        {
            // Check if this response should call Display class methods
            std::string response = _response[i];
            
            // For responses starting with *, call greetingResponse
            if (!response.empty() && response[0] == '*') {
                Display display;
                display.greetingResponse(response);
            }
            // Add other conditions here based on your UML diagram
            // For example, you can check the response content and call appropriate Display methods
            else if (response.find("home loan") != std::string::npos) {
                // This would call homeLoans method from LoanSelection via Display
                // You'll need to implement this based on your architecture
                return true;
            }
            else {
                // For simple responses, use greetingResponse
                Display display;
                display.greetingResponse(response);
            }
            return true;
        }
    }

    // If no exact match found, look for generic response (where input = "*")
    for(size_t i = 0; i < _input.size(); i++)
    {
        if (_input[i] == "*")
        {
            std::string genericResponse = _response[i];
            Display display;
            display.greetingResponse(genericResponse);
            return true;
        }
    }

    // Fallback: if even the "*" entry is not found in file
    Display display;
    display.greetingResponse("Hi! I'll be happy to help. Please press A if you want to apply for loan. Press X to exit");
    return false;
    
}