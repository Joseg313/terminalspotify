#include <iostream>
#include <string>
#include <cstdlib>
#include <cpr/cpr.h>
#include "commands.h"
#include "codeGenerator.h"
#include <cstdlib>
#include <string>

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
    std::string codeVerifier = generateRandomString(64);
    std::string codeChallenge = bas64sha256(codeVerifier);
    std::cout << "code challenge " << codeChallenge << std::endl;
    std::string clientId = get_env_var("SPOTIFY_CLIENT_ID");
    std::cout << "client id "<<clientId <<std::endl;
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
        openUrl(static_cast<std::string>(r.url));
        std::cout << "If not automatically directed, visit this link: ";
        std::cout << r.url << std::endl; 
    }
    else {
        std::cout << "Error, Status code: " << r.status_code << std::endl; 
    }
    


}




