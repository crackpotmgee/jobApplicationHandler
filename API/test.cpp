#include <iostream>
#include "Utils/encrypt.h"

int main() {
    try {
        // Encrypt a string
        std::string plaintext = "Hello, World!";
        std::string encrypted = encrypt_string(plaintext);
        std::cout << "Encrypted: " << encrypted << std::endl;

        // Decrypt the string
        std::string decrypted = decrypt_string(encrypted);
        std::cout << "Decrypted: " << decrypted << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}