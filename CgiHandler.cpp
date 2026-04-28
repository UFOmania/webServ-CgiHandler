#include "CgiHandler.hpp"


CgiHandler::~CgiHandler(){}
CgiHandler::CgiHandler(){ 
    std::string keys[] = { //optimize
        "REQUEST_METHOD",
        "QUERY_STRING",
        "SCRIPT_NAME",
        "CONTENT_LENGTH"
        "CONTENT_TYPE",
        "GATEWAY_INTERFACE",
        "SERVER_PROTOCOL",
        "SERVER_SOFTWARE",
        "SERVER_NAME",
        "SERVER_PORT",
        "REMOTE_ADDR",
        "HTTP_ACCEPT",
        "HTTP_AUTHORIZATION",
        "HTTP_CONNECTION",
        "HTTP_CONTENT_ENCODING",
        "HTTP_CONTENT_LENGTH",
        "HTTP_CONTENT_TYPE",
        "HTTP_DATE",
        "HTTP_FROM",
        "HTTP_IF_MODIFIED_SINCE",
        "HTTP_PRAGMA",
        "HTTP_REFERER",
        "HTTP_USER_AGENT"

    };

    for (size_t i = 0; i < sizeof(keys) / sizeof(std::string) ; ++i)
    {
        _env[keys[i]];

        _env[keys[i]].mandatory = false; //all false for debugging
    }
    _env[CGI_REQUEST_METHOD].mandatory = true;
    _env[CGI_SCRIPT_NAME].mandatory = true;
}

void CgiHandler::setErrMsg(std::string * errMsg, std::string msg)
{
    if (errMsg)
        *errMsg = msg;
}

int CgiHandler::setCgiEnv(std::string key, std::string val, std::string * errMsg = NULL)
{
    if (_env.find(key) == _env.end())
    {
        setErrMsg(errMsg, "Cgi Error: you are trying to set Unknow env key '" + key + "'");
        return 0;
    }

    _env[key].value = val;
    return 1;
}

int CgiHandler::checkCgiEnv(std::string * errMsg = NULL)
{
    for(std::map < std::string, envValue >::iterator it = _env.begin(); it != _env.end(); ++it)
    {
        if (it->second.mandatory == true && it->second.value.empty())
        {
            setErrMsg(errMsg, "Cgi Error: the ENV_VAR '" + it->first + "' is empty");
            return 0; 
        }
    }
    return 1;
}

int CgiHandler::createPipe(int pipe_in[2], int pipe_out[2], std::string * errMsg)
{
    if(pipe(pipe_in) == -1)
    {
        setErrMsg(errMsg, "Cgi Error: Failed at making a pipe");
        return 0;
    }
    if(pipe(pipe_out) == -1)
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        setErrMsg(errMsg, "Cgi Error: Failed at making a pipe");
        return 0;
    }
    return 1;
}

int CgiHandler::doFork(int pipe_in[2], int pipe_out[2], std::string * errMsg)
{
    int pid = fork();
    if (pid == -1)
    {
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
      
        setErrMsg(errMsg, "Cgi Error: failed at fork");
        return 0;
    }
    return 1;
}


int CgiHandler::handleChild(int pipe_in[2], int pipe_out[2], std::string * errMsg)
{
    close(pipe_in[1]);
    close(pipe_out[0]);

    //no savety check
    dup2(pipe_in[0], STDIN_FILENO);
    dup2(pipe_out[1], STDOUT_FILENO);

    close(pipe_in[0]);
    close(pipe_out[1]);

    
    for(std::map<std::string, envValue>::iterator it = _env.begin(); it != _env.end(); ++it)
        setenv(it->first.c_str(), it->second.value.c_str(), 0);

    char * args[] = {(char *)"/usr/bin/python3",(char *)"-u" , (char *)"test.py", NULL};
    if (execv(args[0], args) == -1)
    {
        setErrMsg(errMsg, "Cgi Error: failed at execv");
        return 0;
    }
}

void CgiHandler::handleParent(int pipe_in[2], int pipe_out[2])
{
    close(pipe_in[0]);
    close(pipe_out[1]);

    toCgi = pipe_in[1];
    fromCgi = pipe_out[0];
}


int CgiHandler::initCgi(std::string * errMsg)
{
    int pipe_in[2];
    int pipe_out[2];

    
    if (!createPipe(pipe_in, pipe_out, errMsg))
        return 0;
  
    int pid = doFork(pipe_in, pipe_out, errMsg);

    switch (pid)
    {
        case 0:
            if (!handleChild(pipe_in, pipe_out, errMsg))
                return 0;
            break;
        default:
            handleParent(pipe_in, pipe_out);
            break;
    }
    return 1;
}

int CgiHandler::sendToCgi(std::string data)
{
    
}