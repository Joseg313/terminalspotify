#include <iostream>
#include "commands.h"
#include <string>
int main() {
    std::cout << "Enter Command: ";
    std::string command {};
    std::getline(std::cin >> std::ws, command);
    std:: cout << command << '\n';
    // get acess token using POST
    std::cout << get_token() << '\n';
    // std::cout << song_name() << '\n';
    return 0;

}