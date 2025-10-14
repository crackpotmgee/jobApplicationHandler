#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split_by_delimiter(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        // Extract the substring from 'start' to 'end'
        tokens.push_back(str.substr(start, end - start)); 
        
        // Move 'start' past the delimiter
        start = end + delimiter.length(); 
        
        // Find the next delimiter starting from the new 'start' position
        end = str.find(delimiter, start);
    }

    // Add the final token (the part after the last delimiter)
    tokens.push_back(str.substr(start, end - start)); 

    return tokens;
}