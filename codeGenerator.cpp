#include <string>
#include <random>
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

// create function to hash with sha256