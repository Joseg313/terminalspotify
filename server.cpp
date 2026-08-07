#include "httplib.h"
#include <thread>
#include <future>

int codeServer() {
    httplib::Server svr;
    
    svr.Get("/callback", [](const auto &req, auto &res) {
        auto code = req.get_param_value("code");
        std::cout << "code: " << code << std::endl;
        res.set_content("Query: " + code, "text/plain");
        
    });

    // call svr.stop() from another thread to stop the server
    
    svr.listen("127.0.0.1", 8000);
   
    
    return 0;
}