#include <string>
#include <random>
#include <openssl/sha.h>
#include <openssl/evp.h>
std::string generateRandomString ( int length ) {
    std::string randString {""};
    const std::string possible {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    constexpr int possibleLen {62};
    // random gen source code found from: https://en.cppreference.com/cpp/numeric/random/uniform_int_distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,possibleLen-1);
    
    for (int i = length; i > 0; i--) {
        // add a random element from possible to randString
        randString += possible[distrib(gen)];
    }
    return randString;
}

std::string bas64sha256 (const std::string& plainString) {
    // hash the raw string
    unsigned char digest [SHA256_DIGEST_LENGTH];
    size_t digestLen = 0;
    
    if (!EVP_Q_digest(NULL, "SHA256", NULL,
                       plainString.data(), plainString.size(),
                       digest, &digestLen)) {
        throw std::runtime_error("SHA256 digest failed");
    }

    // base64 encode the digest
}
