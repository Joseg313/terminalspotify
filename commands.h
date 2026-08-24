#pragma once
#include <string>
#include <iostream>
#include <cpr/cpr.h>
#include <optional>
std::string get_env_var(std::string key);
std::string get_info_from_authjson(std::string info);
std::string get_access_token();
std::string get_refresh_token();
bool get_current_playing();
bool nextSong();