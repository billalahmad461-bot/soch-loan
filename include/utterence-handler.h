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
    bool storeUserInputAndResponse(const std::string &file_name);
    bool displayResponse(const std::string &input);
};
