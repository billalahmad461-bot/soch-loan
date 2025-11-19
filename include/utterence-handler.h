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
std::string generateResponse(const std::string &input);
std::string getResponse(const std::string &key) const;
std::string replacePlaceholder(const std::string &text, const std::string &placeholder, const std::string &value) const;
};
