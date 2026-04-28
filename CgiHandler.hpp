#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <string>
#include <map>
#include <set>
#include <unistd.h>
#include <stdlib.h>

#define CGI_REQUEST_METHOD "REQUEST_METHOD"
#define CGI_QUERY_STRING "QUERY_STRING"
#define CGI_SCRIPT_NAME "SCRIPT_NAME"
#define CGI_CONTENT_LENGTH "CONTENT_LENGTH"
#define CGI_CONTENT_TYPE "CONTENT_TYPE"
#define CGI_GATEWAY_INTERFACE "GATEWAY_INTERFACE"
#define CGI_SERVER_PROTOCOL "SERVER_PROTOCOL"
#define CGI_SERVER_SOFTWARE "SERVER_SOFTWARE"
#define CGI_SERVER_NAME "SERVER_NAME"
#define CGI_SERVER_PORT "SERVER_PORT"
#define CGI_REMOTE_ADDR "REMOTE_ADDR"
#define CGI_HTTP_ACCEPT "HTTP_ACCEPT"
#define CGI_HTTP_AUTHORIZATION "HTTP_AUTHORIZATION"
#define CGI_HTTP_CONNECTION "HTTP_CONNECTION"
#define CGI_HTTP_CONTENT_ENCODING "HTTP_CONTENT_ENCODING"
#define CGI_HTTP_CONTENT_LENGTH "HTTP_CONTENT_LENGTH"
#define CGI_HTTP_CONTENT_TYPE "HTTP_CONTENT_TYPE"
#define CGI_HTTP_DATE "HTTP_DATE"
#define CGI_HTTP_FROM "HTTP_FROM"
#define CGI_HTTP_IF_MODIFIED_SINCE "HTTP_IF_MODIFIED_SINCE"
#define CGI_HTTP_PRAGMA "HTTP_PRAGMA"
#define CGI_HTTP_REFERER "HTTP_REFERER"
#define CGI_HTTP_USER_AGENT "HTTP_USER_AGENT"


class CgiHandler
{
    typedef struct 
    {
        std::string value;
        bool        mandatory;
    }   envValue;

    private:
        int toCgi;
        int fromCgi;
        std::map<std::string, envValue> _env;
        void setErrMsg(std::string * errMsg, std::string msg);
        int createPipe(int pipe_in[2], int pipe_out[2], std::string * errMsg);
        int doFork(int pipe_in[2], int pipe_out[2], std::string * errMsg);
        int handleChild(int pipe_in[2], int pipe_out[2], std::string * errMsg);
        void handleParent(int pipe_in[2], int pipe_out[2]);
        

    public:

        ~CgiHandler();
        CgiHandler();
        int setCgiEnv(std::string key, std::string val, std::string * msg);
        int checkCgiEnv(std::string * msg);
        int initCgi(std::string * msg = NULL);
        int sendToCgi(std::string data);
    
};


#endif