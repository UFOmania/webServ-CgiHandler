#include <iostream>
#include "CgiHandler.hpp"

int main()
{
    CgiHandler cgi;

    std::string errMsg;
    if (!cgi.setCgiEnv(CGI_HTTP_ACCEPT, "/www",& errMsg))
        std::cout << errMsg << std::endl;
    if (!cgi.setCgiEnv(CGI_REQUEST_METHOD, "GET",& errMsg))
        std::cout << errMsg << std::endl;
    if (!cgi.setCgiEnv(CGI_SCRIPT_NAME, "login.php",& errMsg))
        std::cout << errMsg << std::endl;
    
    
    if (!cgi.checkCgiEnv(&errMsg))
        std::cout << errMsg << std::endl;

    cgi.initCgi();

    std::cout << "end\n";
}