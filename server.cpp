#include "httplib.h"
#include <thread>
#include <future>
#include <string>

std::pair<int, std::string> codeServer() {
    httplib::Server svr;
    std::string code{};
    svr.Get("/callback", [&code,&svr](const auto &req, auto &res) {
        code = req.get_param_value("code");
        res.set_content("Successful! You can close this tab and return to the terminal", "text/plain");
        svr.stop();
        
    });

    // call svr.stop() from another thread to stop the server
    
    svr.listen("127.0.0.1", 8000);
   
    // std::cout << "code again:" << code << std::endl;
    return {0, code};
}