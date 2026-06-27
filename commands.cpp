#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <fstream>

std::string get_env_var(std::string key) {
    std::string line {};
    std::ifstream env_file("../.env");
    if (!env_file.is_open()) {
        std::cerr << "could not open env file \n";
    }
    std::string value {};
    value ="idk";
    while (getline (env_file, line)) {
        // find an equal sign in the line
        int index = line.find('=');
        // see if all the text before the equal sign matches key
        if (index != std::string::npos) {
            // if all text before equal sign mateches return the text after equal sign
            
            if (key == line.substr(0,index)) {
                value = line.substr(index+1, line.size()-index-1);
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


std::string get_token() {
    // get the client_id and client_secret from .env
    std::string client_id = {get_env_var("SPOTIFY_CLIENT_ID")};
    
    std::string client_secret = {get_env_var("SPOTIFY_CLIENT_SECRET")};
    std::cout << client_id << std::endl;
    std::cout << client_secret << std::endl;

    // return "you good fam";
    
    
    
    // use POST
    cpr::Response r = cpr::Post(
        cpr::Url{"https://accounts.spotify.com/api/token"},
        cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
        cpr::Payload{
            {"grant_type", "client_credentials"},
            {"client_id", client_id},
            {"client_secret", client_secret}
        }
    );

    return r.text;
}


std::string song_name() {
    
    std::string song {"mobamba"};
    // cpr::Response r = cpr::Get(cpr::Url{"https://api.spotify.com/v1/me/player/currently-playing"});
    // return r.text;
    return song;

}

