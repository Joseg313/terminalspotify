cmake_minimum_required(VERSION 3.10)

project(terminalSpotify)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(cpr CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
set(SOURCES
    main.cpp
    commands.cpp
    codeGenerator.cpp
    authFlow.cpp
    winsock.cpp
    server.cpp
)
add_executable(terminalSpotify ${SOURCES})

target_link_libraries(terminalSpotify PRIVATE
    cpr::cpr
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)