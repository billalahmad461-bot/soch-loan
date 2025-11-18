#pragma once
#include<vector>
#include<string>
class UtterenceHandler {
private:
    std::vector<std::string> _input;
    std::vector<std::string> _response;
public:
    UtterenceHandler();
    UtterenceHandler(const std::string &file_name);
    std::string trim(const std::string &str);
    std::string toLower(const std::string &str);
    bool storeUserInputAndResponse(const std::string &file_name);
    bool generateResponse(const std::string &input);
};
