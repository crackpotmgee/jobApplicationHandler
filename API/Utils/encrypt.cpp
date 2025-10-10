#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

std::string base64_encode(const unsigned char* data, size_t len) {
    BIO* bio, * b64;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, len);
    BIO_flush(bio);
    char* bufferData = nullptr;
    long bufferLen = BIO_get_mem_data(bio, &bufferData);
    if (bufferLen <= 0 || bufferData == nullptr) {
        BIO_free_all(bio);
        throw std::runtime_error("Failed to obtain encoded data from BIO");
    }
    std::string encoded(bufferData, static_cast<size_t>(bufferLen));
    BIO_free_all(bio);
    return encoded;
}

std::string base64_decode(const std::string& encodedData) {
    BIO* encodedMem, * b64Filter;
    // create the BIO that represents encrypting or decrypting base 64 dependent on direction
    b64Filter = BIO_new(BIO_f_base64());
    if(!b64Filter){
        throw std::runtime_error("Failed to create base64 BIO");
    }
    // create mem buff from encoded data
    encodedMem = BIO_new_mem_buf(encodedData.data(), encodedData.length());
    if(!encodedMem){
        BIO_free_all(b64Filter);
        throw std::runtime_error("Failed to create memory buffer");
    }
    BIO_set_flags(b64Filter, BIO_FLAGS_BASE64_NO_NL);
    // append b64 to bio
    encodedMem = BIO_push(b64Filter, encodedMem);

    // create the decoded string
    std::string decoded;
    // ced length, also account for padding
    int decodedLen = (encodedData.length() * 3 / 4) - 1;
    decoded.resize(decodedLen);
    long bufferLen = BIO_read(encodedMem, decoded.data(), encodedData.length());
    if (bufferLen <= 0) {
        BIO_free_all(encodedMem);
        throw std::runtime_error("Failed to decode base64 data");
    }
    BIO_free_all(b64Filter);
    
    return decoded;
}

std::string encrypt_string(const std::string& plaintext) {
    const char* key_env = std::getenv("TOKEN_ENCRYPTION_KEY");
    if (!key_env) {
        throw std::runtime_error("Environment variable TOKEN_ENCRYPTION_KEY not set");
    }

    std::string key_str = key_env;
    if (key_str.size() < 32)
        throw std::runtime_error("TOKEN_ENCRYPTION_KEY must be at least 32 bytes for AES-256-GCM");

    const unsigned char* key = reinterpret_cast<const unsigned char*>(key_str.data());

    // Generate random 12-byte IV
    unsigned char iv[12];
    if (!RAND_bytes(iv, sizeof(iv)))
        throw std::runtime_error("Failed to generate IV");

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        throw std::runtime_error("Failed to create EVP_CIPHER_CTX");

    std::vector<unsigned char> ciphertext(plaintext.size() + 16); // space for tag padding
    int len;

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr))
        throw std::runtime_error("EncryptInit failed");

    if (1 != EVP_EncryptInit_ex(ctx, nullptr, nullptr, key, iv))
        throw std::runtime_error("EncryptInit key/iv failed");

    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len,
                               reinterpret_cast<const unsigned char*>(plaintext.data()),
                               plaintext.size()))
        throw std::runtime_error("EncryptUpdate failed");

    int ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
        throw std::runtime_error("EncryptFinal failed");

    ciphertext_len += len;

    unsigned char tag[16];
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag))
        throw std::runtime_error("Get tag failed");

    EVP_CIPHER_CTX_free(ctx);

    // Combine IV + ciphertext + tag
    std::vector<unsigned char> out;
    out.insert(out.end(), iv, iv + sizeof(iv));
    out.insert(out.end(), ciphertext.begin(), ciphertext.begin() + ciphertext_len);
    out.insert(out.end(), tag, tag + sizeof(tag));

    return base64_encode(out.data(), out.size());
}

std::string decrypt_string(const std::string& b64_ciphertext) {
    const char* key_env = std::getenv("TOKEN_ENCRYPTION_KEY");
    if (!key_env) {
        throw std::runtime_error("Environment variable TOKEN_ENCRYPTION_KEY not set");
    }
    std::string key_str = key_env;
    if (key_str.size() < 32)
        throw std::runtime_error("TOKEN_ENCRYPTION_KEY must be at least 32 bytes for AES-256-GCM");

    std::string b64_ciphertext_copy(b64_ciphertext);
    //decode the cypher text
    std::string decoded_cypher = base64_decode(b64_ciphertext_copy);

    const unsigned char* key = reinterpret_cast<const unsigned char*>(key_str.data());

    // create new char to store the iv extracted from the ciphertext
    unsigned char iv[12];
    size_t len = sizeof(decoded_cypher);
    // create vector for the data
    std::vector<unsigned char> uDataVect(decoded_cypher.begin(), decoded_cypher.end()); 

    // get tag from the key
    unsigned char tag[16];
    std::memcpy(tag, uDataVect.data() + len - sizeof(tag), sizeof(tag));
    
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        throw std::runtime_error("Failed to create EVP_CIPHER_CTX");

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr))
        throw std::runtime_error("DecryptInit failed");

    if(1 != EVP_DecryptInit_ex(ctx, nullptr, nullptr, key, iv))
        throw std::runtime_error("DecryptInit key/iv failed");
    unsigned char* decryptedData;
    int outlen;
    if(1 != EVP_DecryptUpdate(ctx, decryptedData, &outlen, uDataVect.data() + sizeof(iv), len - sizeof(iv) - sizeof(tag)))
        throw std::runtime_error("DecryptUpdate failed");
    if(1 != EVP_DecryptFinal_ex(ctx, decryptedData + outlen, &outlen))
        throw std::runtime_error("DecryptFinal failed");

    EVP_CIPHER_CTX_free(ctx);
    std::string decryptedString(reinterpret_cast<char*>(decryptedData), outlen);
    return decryptedString;
}