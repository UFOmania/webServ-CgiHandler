#include <iostream>
#include "CgiHandler.hpp"

int main()
{
    CgiHandler cgi;
	cgi.reqBuffer = "body";


    std::string errMsg;
    if (!cgi.setCgiEnv(CGI_HTTP_ACCEPT, "/www",& errMsg))
        std::cout << errMsg << std::endl;
    if (!cgi.setCgiEnv(CGI_REQUEST_METHOD, "GET",& errMsg))
        std::cout << errMsg << std::endl;
    if (!cgi.setCgiEnv(CGI_SCRIPT_NAME, "login.php",& errMsg))
        std::cout << errMsg << std::endl;
    
    
    if (!cgi.checkCgiEnv(&errMsg))
	{
        std::cout << errMsg << std::endl;
	}

	
	if (!cgi.initCgi(&errMsg))
		std::cout << errMsg << std::endl;


	cgi.sendToCgi();

	while (cgi.reciveFromCgi() != 0)
		;
		
	cgi.putRes();

}