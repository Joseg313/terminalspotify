#include <iostream>
#include "commands.h"
#include "codeGenerator.h"
#include "authFlow.h"
#include <string>
#include <optional>
int main() {
    std::cout << "Enter Command: ";
    std::string command {};
    std::getline(std::cin >> std::ws, command);
    std:: cout << command << '\n';
    // initialAuth();
    // if (get_current_playing() == false) {
    //     getNewAccessToken();
    //     std::cout << get_current_playing() << std::endl;
    // }
    // std::cout << get_current_playing() << std::endl;   
    // if (nextSong() == false) {
    //     getNewAccessToken();
    //     nextSong();
    // }
    // getNewAccessToken();
    nextSong();
    // getNewAccessToken();
    // std::cout << get_current_playing() << std::endl;   
    
    return 0;

}