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
    if (!((get_current_playing()).has_value())) {
        get_current_playing();
    }
        
    
    return 0;

}