#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> parse_urlencoded_form(const std::string& body);