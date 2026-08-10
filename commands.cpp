#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
std::string get_env_var(std::string key) {
    std::string line {};
    std::ifstream env_file(".env");
    if (!env_file.is_open()) {
        std::cerr << "could not open env file \n";
    }
    std::string value {};
    value = "idk";
    while (getline (env_file, line)) {
        // find an equal sign in the line
        int index = line.find('=');
        // see if all the text before the equal sign matches key
        if (index != std::string::npos) {
            // if all text before equal sign mateches return the text after equal sign
            
            if (key == line.substr(0,index)) {
                value = line.substr(index+2, line.size()-key.size()-3);
                return value;
            } else {
                
                value = "inner";
            }
        } else {
            value = "outer";
        }
        
    }
    env_file.close();
    
    return value;
}


std::string get_info_from_authjson(std::string info) {
    std::ifstream readFile("auth.json");
    json jsonData;
    if (readFile.is_open()) { 
        readFile>>jsonData;
    }
    readFile.close();
    return jsonData[info];
}

std::string get_access_token() {
    std::string accessToken {get_info_from_authjson("access_token")};
    return accessToken;
}
std::string get_refresh_token() {
    std::string refreshToken {get_info_from_authjson("refresh_token")};
    return refreshToken;
}


std::string get_current_playing() {
    std::string song {};
    // curl --request GET \
    // --url https://api.spotify.com/v1/me/player/currently-playing \
    // --header 'Authorization: Bearer 1POdFZRZbvb...qqillRxMr2z'
    cpr::Response r = cpr::Get(
        cpr::Url{"https://api.spotify.com/v1/me/player/currently-playing"},
        cpr::Header{{"Authorization", "Bearer " + get_access_token()}}   
    );
    song = r.text;
    std::cout << song <<std::endl;
    return song;

}