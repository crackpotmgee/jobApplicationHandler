#pragma once
#include <string>

// Base64 encoding/decoding
std::string base64_encode(const unsigned char* data, size_t len);
std::string base64_decode(const std::string& encodedData);

// AES-256-GCM encryption/decryption using TOKEN_ENCRYPTION_KEY from environment
std::string encrypt_string(const std::string& plaintext);
std::string decrypt_string(const std::string& b64_ciphertext);
