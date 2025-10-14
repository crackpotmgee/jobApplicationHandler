#include <iostream>
#include "Utils/encrypt.h"

int main() {
    try {

        // Encrypt a string
        std::string plaintext = "Hello, World!";
        
        // encode data
        std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size());
        // decode data
        std::string decoded = base64_decode(encoded);
        std::cout << "Original: " << plaintext << std::endl;
        std::cout << "Encoded: " << encoded << std::endl;
        std::cout << "Decoded: " << decoded << std::endl;
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