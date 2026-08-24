#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <optional>
#include "authFlow.h"
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
    } else {
        throw std::runtime_error("Could not open auth.json");
    }

    if (!jsonData.contains(info)) {
        throw std::runtime_error("Key not found in auth.json: " + info);
    }
    return jsonData.at(info).get<std::string>();
}

std::string get_access_token() {
    std::string accessToken {get_info_from_authjson("access_token")};
    return accessToken;
}
std::string get_refresh_token() {
    std::string refreshToken {get_info_from_authjson("refresh_token")};
    return refreshToken;
}


bool get_current_playing() {
    std::string song {};
    cpr::Response r = cpr::Get(
        cpr::Url{"https://api.spotify.com/v1/me/player/currently-playing"},
        cpr::Header{{"Authorization", "Bearer " + get_access_token()}}   
    );
    if (r.status_code != 200 || r.text.empty()) {
        return false;
    }
    try {
        json jsonData = json::parse(r.text);
        if (!jsonData.contains("item") || jsonData["item"].is_null()){
            return false;
        }
        if (jsonData["item"].contains("album") &&
            jsonData["item"]["album"].contains("images")) {
            std::cout << jsonData["item"]["album"]["images"].dump() << std::endl;
        }
        bool isPlaying = jsonData.value("is_playing", false);
        return isPlaying;
    
        
    }
    catch (const json::exception& e) {
        std::cerr << "json parse error: " << e.what() << std::endl;
        return false;
    }

}

bool nextSong() {
    cpr::Response r = cpr::Post(
        cpr::Url{"https://api.spotify.com/v1/me/player/next"},
        cpr::Header{{"Authorization", "Bearer " + get_access_token()}}   
    );
    std::cout << r.status_code<<std::endl;
    if (r.status_code == 204) {
        return 0;
    } else {
        return 1;
    }
}