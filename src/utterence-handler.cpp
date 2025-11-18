#include "include\utterence-handler.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>


//file handling to trim spaces 


std::string UtterenceHandler::trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return " ";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);


}

// converting to lower case to make input != casesensitive

std::string UtterenceHandler::toLower(const std::string &str)
{
    std:: string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){return std::tolower(c);});

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

    while(std::getline(file,line))
    {
        if(line.empty()) continue;

        size_t pos = line.find('#');
        if(pos == std::string::npos) continue;


        std::string key = trim(line.substr(0,pos));
        std::string value = trim(line.substr(pos + 1));

        //coverting to lower case

        key = toLower(key);

        _input.push_back(key);
        _response.push_back(value);

    }

    file.close();
    return true;

}

bool UtterenceHandler::generateResponse(const std::string &input)
{
    std:: string cleared = trim(input);
    cleared = toLower(cleared);

    // searching for match

    for(size_t i = 0; i< _input.size(); i++)
    {
        if (_input[i] == "*")
        {
            std::cout << _response[i] << "\n";

            return true;

        }
    }

    std::cout<< "No response found.\n";

    return false;


}
