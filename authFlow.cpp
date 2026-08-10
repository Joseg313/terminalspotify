#include <iostream>
#include <string>
#include <cstdlib>
#include <cpr/cpr.h>
#include <thread>
#include "commands.h"
#include "codeGenerator.h"
#include <cstdlib>
#include <string>
#include "winsock.h"
#include "server.h"
#include "httplib.h"
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;
void openUrl(const std::string& url) {
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + url + "\"";
    
#elif defined(__APPLE__)
    std::string cmd = "open \"" + url + "\"";
#else
    std::string cmd = "xdg-open \"" + url + "\"";
#endif
    std::system(cmd.c_str());
}






void initialAuth() {
    const std::string codeVerifier {generateRandomString(64)};
    const std::string codeChallenge {bas64sha256(codeVerifier)};
   
    std::string clientId = get_env_var("SPOTIFY_CLIENT_ID");

    const std::string responseType {"code"};
    const std::string redirectUri {"http://127.0.0.1:8000/callback"};
    const std::string scope {
        "user-read-playback-state "
        "user-modify-playback-state "
        "user-read-currently-playing "
        "playlist-read-private "
        "playlist-read-collaborative "
        "playlist-modify-private "
        "playlist-modify-public "
        "user-follow-modify "
        "user-follow-read "
        "user-read-playback-position "
        "user-top-read "
        "user-library-modify "
        "user-library-read "
        "user-read-email "
        "user-read-private"
    };
    const std::string codeChallengeMethod {"S256"};

    cpr::Response r = cpr::Get(
        cpr::Url{"https://accounts.spotify.com/authorize"},
        cpr::Parameters{
            {"response_type",responseType},
            {"client_id",clientId},
            {"scope",scope},
            {"code_challenge_method",codeChallengeMethod},
            {"code_challenge",codeChallenge},
            {"redirect_uri",redirectUri}
        }   
    );
   
    if (r.status_code == 200) {
        

        // open redirect link
        openUrl(static_cast<std::string>(r.url));
        std::cout << "If not automatically directed, visit this link: ";
        std::cout << r.url << std::endl; 
        
        // run ther server
        auto [status, code] = codeServer();
        
        if (status == 0) {
            // send a post with the code we just got
            cpr::Response r = cpr::Post(
                cpr::Url{"https://accounts.spotify.com/api/token"},
                cpr::Payload{
                    {"grant_type","authorization_code"},
                    {"code",code},
                    {"redirect_uri",redirectUri},
                    {"client_id",clientId},
                    {"code_verifier",codeVerifier}
                },
                cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}}   
            );
            if (r.status_code == 200){
                
                // parse the response
                json parsed = json::parse(r.text);
                std::fstream myFile;
                myFile.open("auth.json", std::ios::out);
                if (myFile.is_open()) {
                    myFile << parsed << std::endl;
                }
                myFile.close();
                
                

            } else {
                std::cout << "Error, Status code: " << r.status_code<<std::endl;
            }
            
        }
        else 
        {
            std::cout<< "idk something went wrong after the redirect" <<std::endl;
        }
        
    }
    else {
        std::cout << "Error, Status code: " << r.status_code << std::endl; 
    }
    
    

}




