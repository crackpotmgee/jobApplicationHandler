#include <uriparser/Uri.h>
#include <unordered_map>
#include <string>
#include <stdexcept>

std::unordered_map<std::string, std::string> parse_urlencoded_form(const std::string& body) {
    std::unordered_map<std::string, std::string> result;

    UriQueryListA* queryList = nullptr;
    int itemCount = 0;

    // uriparser expects pointers to the start and end of the string
    if (uriDissectQueryMallocA(&queryList, &itemCount,
                               body.c_str(), body.c_str() + body.size()) != URI_SUCCESS) {
        throw std::runtime_error("Failed to parse URL-encoded body");
    }

    // Iterate through the linked list of key-value pairs
    for (UriQueryListA* item = queryList; item; item = item->next) {
        std::string key = item->key ? item->key : "";
        std::string value = item->value ? item->value : "";
        result[key] = value;
    }

    uriFreeQueryListA(queryList);

    return result;
}