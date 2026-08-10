#include <iostream>
#include "commands.h"
#include "codeGenerator.h"
#include "authFlow.h"
#include <string>
int main() {
    std::cout << "Enter Command: ";
    std::string command {};
    std::getline(std::cin >> std::ws, command);
    std:: cout << command << '\n';
    
    // initialAuth();
    get_current_playing();
    return 0;

}